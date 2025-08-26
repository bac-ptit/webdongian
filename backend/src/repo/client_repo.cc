//
// Created by ROG on 6/22/2025.
//

#include "client_repo.h"

#include "order_repo.h"

void ClientRepo::CreateClient(Client& client) {
  static std::string sql = bac_lib::tool::StrCat(
      "INSERT INTO ", Client::kSchema, ".", Client::kTableName,
      " (phone_number_, email_, balance_, register_date_, "
      "password_) "
      "VALUES (:1, :2, :3, :4, :5"
      ") RETURNING id_ INTO :6");
  const auto stmt =
      CreateStatement(sql, client.phone_number_, client.email_, client.balance_,
                      client.register_date_.ToOracleDate(), client.password_);
  stmt->registerOutParam(6, oracle::occi::OCCIINT, sizeof(Client::id_));
  DefaultCommitHandler([&] { stmt->executeUpdate(); });
  const auto id = stmt->getInt(6);
  client.id_ = id;
}

std::optional<Client::TypeId> ClientRepo::Login(
    const std::string& email_or_phone_number,
    const std::string& password) const {
  static std::string sql = bac_lib::tool::StrCat(
      "SELECT ", Client::kPrimaryKey, " FROM ", Client::kSchema, ".",
      Client::kTableName,
      " WHERE (phone_number_ = :1 OR email_ = :2) and (password_ = :3)");

  const auto stmt = CreateStatement(sql, email_or_phone_number,
                                    email_or_phone_number, password);
  if (const auto rs = stmt->executeQuery(); rs->next()) {
    return rs->getInt(1);
  }
  return std::nullopt;
}

std::unique_ptr<Client> ClientRepo::FindByPrimaryKeyWithRelation(const int id) {
  auto result = FindByPrimaryKey(id);
  if (!result) {
    return nullptr;
  }
  result->transactions_ = transaction_repo_->FindWithClientId(id);
  result->orders_ = order_repo_->FindAllWithClientId(id);
  return result;
}
