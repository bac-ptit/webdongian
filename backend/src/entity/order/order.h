//
// Created by ROG on 26/06/2025.
//

#ifndef BACKEND_ENTITY_ORDER_ORDER_H
#define BACKEND_ENTITY_ORDER_ORDER_H
#include <utility>

#include "../../../include/bac_lib/orcl/base_pobject.h"
#include "entity/server/server.h"
#include "entity/transaction/transaction.h"
#include "modul/bill_total.h"

class Order final : public bac_lib::orcl::BasePObject<Order> {
 public:
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  using TypeId = std::string;

  enum class State { kInitial, kPending, kProcessing, kError, kSuccess };

  static constexpr auto kSchema = config::database::kSchema;
  static constexpr auto kTableName = "TABLE_ORDER";
  static constexpr auto kTypename = "TYPE_ORDER";
  static constexpr auto kPrimaryKey = "id_";  // this is automatically generated

  Order(std::string link, int quantity_ordered, const BillTotal& bill_total,
        int client_id, int server_id);

  void ValidateQuantity() const;

  void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  const TypeId& GetId() const& noexcept;
  TypeId&& GetId() && noexcept;

 private:
  friend class OrderRepo;
  friend class OrderResponseDto;

  TypeId id_;
  std::string link_;
  int quantity_ordered_;
  int quantity_executed_{0};
  BillTotal bill_total_;  // this is a value object, not an entity
  State state_ = State::kInitial;
  bac_lib::type::Date created_at_;

  /* relation */
  int client_id_;         // many-to-one
  int server_id_;         // many-to-one
  int transaction_id_{};  // one-to-one

  std::unique_ptr<Server> server_;  // this is a many-to-one relationship,
                                    // but in the database, it is stored as
                                    // server_id
  std::unique_ptr<Transaction>
      transaction_;  // This is a one-to-one relationship, but in the database,
                     // it is stored as transaction_id
};

#endif  // BACKEND_ENTITY_ORDER_ORDER_H
