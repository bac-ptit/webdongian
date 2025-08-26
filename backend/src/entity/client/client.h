//
// Created by ROG on 6/22/2025.
//

#ifndef BACKEND_CLIENT_H
#define BACKEND_CLIENT_H
#include "../../../include/bac_lib/orcl/base_pobject.h"
#include "config/database.h"
#include "entity/order/order.h"
#include "entity/transaction/transaction.h"

class Client final : public bac_lib::orcl::BasePObject<Client> {
 public:
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  using TypeId = int;

  static constexpr auto kSchema = config::database::kSchema;
  static constexpr auto kTableName = "TABLE_CLIENT";
  static constexpr auto kTypename = "TYPE_CLIENT";
  static constexpr auto kPrimaryKey = "id_";  // id is auto increased

  Client(std::string phone_number, std::string email, double balance,
         bac_lib::type::Date register_date, std::string password);

  static void CheckPassword(std::string_view password);
  void ChangePassword(std::string new_password);

  void ChangeBalance(double amount);

  void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  [[nodiscard]] int GetId() const;

 private:
  friend class ClientRepo;
  friend class ClientResponse;

  TypeId id_{};
  std::string phone_number_;
  std::string email_;
  double balance_;
  bac_lib::type::Date register_date_;
  std::string password_;

  // relation

  std::vector<std::unique_ptr<Transaction>> transactions_;
  std::vector<std::unique_ptr<Order>> orders_;
};

#endif  // BACKEND_CLIENT_H