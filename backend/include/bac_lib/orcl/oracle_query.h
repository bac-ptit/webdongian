#pragma once
#include <occi.h>

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "../tool/tool.h"

namespace bac_lib::orcl {
/**
 * Concept to ensure T is derived from oracle::occi::PObject and implements
 * required methods.
 */
template <typename T>
concept object_base =
    requires(T t, oracle::occi::Connection* conn, std::string& tableName,
             void* ctxOCCI_, std::string& typeName, std::string& tableSchema,
             std::string& typeSchema, size_t size, void* objOCCI_) {
      requires std::is_base_of_v<oracle::occi::PObject, T>;
      { T::kSchema } -> std::convertible_to<std::string>;
      { T::kTableName } -> std::convertible_to<std::string>;
      { T::kTypename } -> std::convertible_to<std::string>;
      { T::kPrimaryKey } -> std::convertible_to<const char*>;
      { T::ReadSQL(ctxOCCI_) } -> std::same_as<void*>;
      { T::WriteSQL(ctxOCCI_, objOCCI_) } -> std::same_as<void>;
      { T::operator new(size, conn, tableName) } -> std::same_as<void*>;
    };

/**
 * Concept to ensure T is either an arithmetic type or controller std::string.
 */
template <typename T>
concept DateType = std::is_arithmetic_v<std::decay_t<T>> ||
                   std::is_same_v<std::decay_t<T>, oracle::occi::Number> ||
                   std::is_convertible_v<std::decay_t<T>, std::string> ||
                   std::is_base_of_v<oracle::occi::PObject, std::decay_t<T>>;

template <typename T>
concept NotCompositeKey = T::kPrimaryKey != nullptr;

/**
 * Class to handle Oracle database queries for objects derived from
 * oracle::occi::PObject.
 *
 * @tparam OracleObject The type of the Oracle object.
 * \note Functions involving "primary key" do not support composite primary
 * keys. They only support classes with a single primary key.
 */
template <object_base OracleObject>
// ReSharper disable once CppClassCanBeFinal
class OracleQuery {
 public:
  using Environment = oracle::occi::Environment;
  using Connection = oracle::occi::Connection;
  using Statement = oracle::occi::Statement;
  using ResultSet = oracle::occi::ResultSet;
  using SQLException = oracle::occi::SQLException;
  template <typename T>
  using Ref = oracle::occi::Ref<T>;

 private:
  static constexpr auto kMaxBufferSize = 10 * 1024 * 1024;  // 10MB
 public:
  OracleQuery(oracle::occi::Environment* env, oracle::occi::Connection* conn)
      : env_(env), conn_(conn), stmt_([&] {
          auto stmt = conn_->createStatement();
          stmt->setPrefetchMemorySize(kMaxBufferSize);
          return stmt;
        }()) {}

  virtual ~OracleQuery() { conn_->terminateStatement(stmt_); }

  /**
   *Retrieves Oracle Object from database with condition
   * @param condition : where .....
   * @param args : the argument :1, :2, :3,...
   * @return A vector of unique pointers to Oracle objects.
   *  Note: the vector will never contain nullptr
   */
  [[nodiscard]] std::vector<std::unique_ptr<OracleObject>> FindWithCondition(
      std::string condition = "", auto&&... args) const {
    Statement* stmt = CreateStatement(
        tool::StrCat("SELECT VALUE(X) FROM ", OracleObject::kTableName, " X ") +
            std::move(condition),
        args...);
    ResultSet* rs = stmt->executeQuery();
    std::vector<std::unique_ptr<OracleObject>> result;
    while (rs->next()) {
      result.emplace_back(static_cast<OracleObject*>(rs->getObject(1)));
    }
    return result;
  }

  /**
   * \brief Retrieves an Oracle object from the database using the primary key.
   *
   * This function retrieves controller single Oracle object from the database
   * based on the provided primary key. If no object is found with the given
   * primary key, the function returns controller nullptr.
   *
   * \param primary_key The primary key of the Oracle object to be retrieved.
   * \return A unique pointer to the Oracle object if found, otherwise nullptr.
   */
  [[nodiscard]] std::unique_ptr<OracleObject> FindByPrimaryKey(
      const DateType auto& primary_key)
    requires NotCompositeKey<OracleObject>
  {
    auto temp = FindWithCondition(
        tool::StrCat("WHERE ", OracleObject::kPrimaryKey, " = :1"),
        std::forward<decltype(primary_key)>(primary_key));
    return temp.empty() ? nullptr : std::move(temp.front());
  }

  /**
   * \brief Adds a new Oracle object to the database.
   *
   * This function adds a new Oracle object to the database. The object must be
   * of the same type as OracleObject.
   * \note The object does not need to be deleted manually.
   * \param obj The Oracle object to be added.
   */
  OracleObject* AddObj(auto&& obj)
    requires std::is_same_v<decltype(obj), OracleObject>
  {
    OracleObject* result;
    DefaultCommitHandler([&] {
      result = new (conn_, OracleObject::kTableName)
          OracleObject(std::forward<decltype(obj)>(obj));
    });
    return result;
  }

  /**
   * \brief Constructs an OracleObject with the provided arguments.
   *
   * This function constructs an OracleObject using the provided arguments.
   * The arguments must be compatible with the constructor of OracleObject.
   * \note The object does not need to be deleted manually.
   * \tparam Args The types of the arguments.
   */
  template <typename... Args>
    requires std::is_constructible_v<OracleObject, Args&&...>
  OracleObject* EmplaceObj(Args&&... args) {
    OracleObject* result;
    DefaultCommitHandler([&] {
      result = new (conn_, OracleObject::kTableName)
          OracleObject(std::forward<decltype(args)>(args)...);
    });
    return result;
  }

  /**
   * \brief Updates an existing Oracle object in the database.
   *
   * This function updates an existing Oracle object in the database based on
   * the provided primary key. The object is marked as modified and the changes
   * are committed to the database.
   *
   * \param primary_key The primary key of the Oracle object to be updated.
   * \param obj_ The new Oracle object data to update.
   * \throws std::exception if the update fails.
   */
  OracleObject* Update(auto&& primary_key, OracleObject&& obj_)
    requires NotCompositeKey<OracleObject>
  {
    static auto sql =
        tool::StrCat("SELECT REF(X) FROM ", OracleObject::kTableName,
                     " X WHERE ", OracleObject::kPrimaryKey, " = :1 ");
    Statement* stmt = CreateStatement(sql, primary_key);
    OracleObject* result;
    if (ResultSet* rs = stmt->executeQuery(); rs->next()) {
      DefaultCommitHandler([&] {
        Ref<OracleObject> ref = static_cast<Ref<OracleObject>>(rs->getRef(1));
        ref->markModified();  // this function is belong to PObject
        ref->Set(std::forward<OracleObject>(obj_));
        result = ref.ptr();
      });
    }
    return result;
  }

  /**
   * \brief Deletes an Oracle object from the database based on the primary key.
   *
   * This function deletes an Oracle object from the database using the provided
   * primary key.
   *
   * \param primary_key The primary key of the Oracle object to be deleted.
   * \throws std::exception if the deletion fails.
   */
  void DeleteByPrimaryKey(DateType auto&& primary_key)
    requires NotCompositeKey<OracleObject>
  {
    static auto sql =
        tool::StrCat("DELETE FROM ", OracleObject::kTableName, " WHERE ",
                     OracleObject::kPrimaryKey, " = :1");
    Statement* stmt = CreateStatement(sql, primary_key);
    stmt->executeUpdate();
  }

  /**
   * \brief Retrieves references to Oracle objects from the database with a
   * condition.
   *
   * This function retrieves references to Oracle objects from the database
   * based on the provided condition. The condition is specified as a SQL WHERE
   * clause, and the arguments are used to set the parameters in the SQL
   * statement.
   *
   * \param str The SQL WHERE clause to filter the Oracle objects.
   * \param args The arguments to set the parameters in the SQL statement.
   * \return A vector of references to Oracle objects that match the condition.
   */
  std::vector<Ref<OracleObject>> FindRefWithCondition(const std::string& str,
                                                      auto&&... args) {
    Statement* stmt = CreateStatement(
        tool::StrCat("SELECT REF(X) FROM ", OracleObject::kTableName, " X ") +
            str,
        args...);

    ResultSet* rs = stmt->executeQuery();
    std::vector<Ref<OracleObject>> result;
    while (rs->next()) {
      result.push_back(static_cast<Ref<OracleObject>>(rs->getRef(1)));
    }
    return result;
  }

  /**
   * \brief Retrieves a reference to an Oracle object from the database using
   * the primary key.
   *
   * This function retrieves a reference to a single Oracle object from the
   * database based on the provided primary key. If no object is found with the
   * given primary key, the function returns a nullptr.
   *
   * \param primary_key The primary key of the Oracle object to be retrieved.
   * \return A reference to the Oracle object if found, otherwise nullptr.
   */
  Ref<OracleObject> FindRefByPrimaryKey(const DateType auto& primary_key)
    requires NotCompositeKey<OracleObject>
  {
    auto temp = FindRefWithCondition(
        tool::StrCat("WHERE ", OracleObject::kPrimaryKey, " = :1"),
        primary_key);
    return temp.empty() ? nullptr : temp.front();
  }

  std::vector<std::unique_ptr<OracleObject>> ExecuteQueryObj(
      const std::string& sql, auto&&... args) {
    const auto stmt = CreateStatement(sql, args...);
    const auto rs = stmt->executeQuery();
    std::vector<std::unique_ptr<OracleObject>> result;
    while (rs->next()) {
      result.emplace_back(static_cast<OracleObject*>(rs->getObject(1)));
    }
    return result;
  }

  std::vector<Ref<OracleObject>> ExecuteQueryRef(const std::string& sql,
                                                 auto&&... args) {
    const auto stmt = CreateStatement(sql, args...);
    const auto rs = stmt->executeQuery();
    std::vector<Ref<OracleObject>> result;
    while (rs->next()) {
      result.push_back(static_cast<Ref<OracleObject>>(rs->getRef(1)));
    }
    return result;
  }

  /**
   * \brief Retrieves the next ID for an Oracle object.
   *
   * This function generates the next ID for an Oracle object based on the
   * provided prefix. It queries the database to find the maximum numeric
   * suffix for IDs that start with the given prefix and increments it by one.
   *
   * \param first_part_of_id The prefix of the ID.
   * \return The next ID as a string.
   *
   * \example
   * std::string next_id = oracleQuery.GetNextPrimaryKey("ABC-");
   * // If the current maximum ID is "ABC-123", the next_id will be "ABC-124".
   */
  std::string GetNextPrimaryKey(const std::string& first_part_of_id) {
    static std::string sql =
        tool::StrCat("SELECT :1 || NVL(MAX(TO_NUMBER(REGEXP_SUBSTR(",
                     OracleObject::kPrimaryKey,
                     ", '[0-9]+'))) + 1, 1) AS max_id"
                     " FROM ",
                     OracleObject::kTableName, " WHERE ",
                     OracleObject::kPrimaryKey, " LIKE :1 || '%'");
    if (const auto rs = CreateStatement(sql, first_part_of_id)->executeQuery();
        rs->next()) {
      return rs->getString(1);
    }
    return first_part_of_id + '0';
  }

  /**
   * \brief Handles the commit and rollback of a transaction.
   *
   * This function executes the provided function and commits the transaction if
   * successful. If an exception is thrown, it rolls back the transaction and
   * rethrows the exception.
   *
   * \param func The function to execute within the transaction.
   */
  void DefaultCommitHandler(auto func) {
    try {
      func();
      conn_->commit();
    } catch (...) {
      conn_->rollback();
      throw;
    }
  }

 protected:
  /**
   * \brief Sets the SQL statement and binds the provided arguments.
   *
   * This function sets the SQL statement for the current statement object and
   * binds the provided arguments to the statement parameters.
   *
   * \param sql The SQL statement to be set.
   * \param args The arguments to bind to the statement parameters.
   * \return A pointer to the Statement object with the SQL and parameters set.
   *
   * \note don't delete Statement*
   */
  Statement* CreateStatement(const std::string& sql,
                             const auto&... args) const {
    stmt_->setSQL(sql);
    std::size_t index = 0;
    (SetValueForStmt(++index, args), ...);
    return stmt_;
  }

  /**
   * Converts an object to controller string.
   *
   * @tparam T The type of the object.
   * @param obj The object to convert.
   * @return The string representation of the object.
   */
  static std::string ConvertToString(auto&& obj) {
    using T = std::decay_t<decltype(obj)>;
    if constexpr (std::is_arithmetic_v<T>) {
      return std::string(std::forward<T>(obj));
    } else {
      return obj;
    }
  }

  /**
   * \brief Sets the value of controller statement parameter based on the type
   * of the object.
   *
   * This function sets the value of controller parameter in the SQL statement.
   * The type of the object determines how the value is set. It supports
   * arithmetic types, strings, and objects derived from oracle::occi::PObject.
   *
   * \param index The index of the parameter in the SQL statement.
   * \param obj The object whose value is to be set in the SQL statement.
   * \throws std::invalid_argument if the type of the object is not supported.
   */
  void SetValueForStmt(long index, auto& obj) const {
    using T = std::decay_t<decltype(obj)>;
    if constexpr (std::is_arithmetic_v<T>) {
      stmt_->setNumber(index, obj);
    } else if constexpr (std::is_convertible_v<T, std::string>) {
      stmt_->setString(index, obj);
    } else if constexpr (std::is_base_of_v<oracle::occi::PObject, T>) {
      stmt_->setObject(index, &obj);
    } else if constexpr (std::is_same_v<oracle::occi::Date, T>) {
      stmt_->setDate(index, obj);
    } else {
      throw std::invalid_argument("invalid type");
    }
  }

 private:
  Environment* env_;
  Connection* conn_;
  mutable Statement* stmt_;
};
}  // namespace bac_lib::orcl