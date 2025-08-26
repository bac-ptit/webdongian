//
// Created by rog on 29/12/24.

#ifndef BAC_LIB_ORCL_BASEPOBJECT_HPP
#define BAC_LIB_ORCL_BASEPOBJECT_HPP

#include <occi.h>

#include <iostream>
#include <string>

#include "../tool/tool.h"

namespace bac_lib::orcl {

/**
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  using TypeId = ...

  static constexpr auto kSchema = "system";
  static constexpr auto kTableName = "";
  static constexpr auto kTypename = "";
  static constexpr auto kPrimaryKey = "id_";
 */

/**
 * \brief Base class for Oracle PObject with template for derived class.
 *
 * \tparam Derived The derived class inheriting from BasePObject.
 *
 * The Derived class must define the following static members:
 * - \c kSchema: The schema name.
 * - \c kTableName: The table name.
 * - \c kTypename: The type name.
 * - \c kPrimaryKey: The primary key.
 */
template <typename Derived>
class BasePObject : public oracle::occi::PObject {
public:
    using PObject::PObject;

    /**
     * \brief Default constructor.
     */
    BasePObject() = default;

    ~BasePObject() override = default;

    /**
     * \brief Overloaded new operator.
     *
     * \param size The size of the object to allocate.
     * \return Pointer to the allocated memory.
     */
    void* operator new(const size_t size) {
        return PObject::operator new(size);
    }

    /**
     * \brief Overloaded new operator with session and table parameters.
     *
     * \param size The size of the object to allocate.
     * \param sess The Oracle connection session.
     * \param table The table name.
     * \return Pointer to the allocated memory.
     */
    void* operator new(const size_t size, const oracle::occi::Connection* sess,
                       const OCCI_STD_NAMESPACE::string& table) {
        return PObject::operator new(
            size, sess, table, tool::StrCat(Derived::kSchema, ".", Derived::kTypename).c_str());
    }

    /**
     * \brief Overloaded new operator with context parameter.
     *
     * \param size The size of the object to allocate.
     * \param ctxOCCI_ The context for OCCI.
     * \return Pointer to the allocated memory.
     */
    void* operator new(const size_t size, void* ctxOCCI_) {
        return PObject::operator new(size, ctxOCCI_);
    }

    /**
     * \brief Gets the SQL type name.
     *
     * \param env The Oracle environment.
     * \param schemaName Pointer to the schema name.
     * \param schemaNameLen Length of the schema name.
     * \param typeName Pointer to the type name.
     * \param typeNameLen Length of the type name.
     */
    void getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
                        unsigned int& schemaNameLen, void** typeName,
                        unsigned int& typeNameLen) const override {
        PObject::getSQLTypeName(env, &ReadSQL, schemaName, schemaNameLen, typeName, typeNameLen);
    }

    /**
     * \brief Gets the SQL type name as a string.
     *
     * \return The SQL type name.
     */
    [[nodiscard]] std::string getSQLTypeName() const override {
        return Derived::kTypename;
    }

    /**
     * \brief Reads the SQL data.
     *
     * \param ctxOCCI_ The context for OCCI.
     * \return Pointer to the read object.
     */
    static void* ReadSQL(void* ctxOCCI_) {
        const auto objOCCI_ = new (ctxOCCI_) Derived(ctxOCCI_);
        oracle::occi::AnyData streamOCCI_(ctxOCCI_);
        try {
            if (streamOCCI_.isNull()) {
                objOCCI_->setNull();
            } else {
                objOCCI_->readSQL(streamOCCI_);
            }
        } catch (oracle::occi::SQLException& e) {
            delete objOCCI_;
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
        return objOCCI_;
    }

    /**
     * \brief Writes the SQL data.
     *
     * \param objOCCI_ The object to write.
     * \param ctxOCCI_ The context for OCCI.
     */
    static void WriteSQL(void* objOCCI_, void* ctxOCCI_) {
        auto objectOCCI_ = static_cast<BasePObject*>(objOCCI_);
        oracle::occi::AnyData streamOCCI_(ctxOCCI_);
        try {
            if (objectOCCI_->isNull()) {
                streamOCCI_.setNull();
            } else {
                objectOCCI_->writeSQL(streamOCCI_);
            }
        } catch (oracle::occi::SQLException& e) {
            e.setErrorCtx(ctxOCCI_);
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * \brief Reads the SQL data from the stream.
     *
     * \param streamOCCI_ The stream to read from.
     */
    void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override = 0;

    /**
     * \brief Writes the SQL data to the stream.
     *
     * \param streamOCCI_ The stream to write to.
     */
    void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override = 0;
};

}  // namespace bac_lib::orcl
#endif  // BAC_LIB_ORCL_BASEPOBJECT_HPP