//
// Created by ROG on 26/06/2025.
//

#include "order_repo.h"

std::vector<std::unique_ptr<Order>> OrderRepo::FindAllWithClientId(
    int client_id, int offset, int limit) const {
  return FindWithCondition(
      " WHERE client_id_ = :1 ORDER BY created_at_ DESC OFFSET :2 ROWS FETCH "
      "NEXT :3 ROWS ONLY",
      client_id, offset, limit);
}

void OrderRepo::CreateOrder(Order& order) {
  static std::string sql = bac_lib::tool::StrCat(
      "INSERT INTO ", Order::kSchema, ".", Order::kTableName,
      " (link_, quantity_ordered_, quantity_executed_, discount_rate_, "
      "discount_amount_in_order_, tax_rate_, state_, created_at_, client_id_, "
      "server_id_, transaction_id_) "
      "VALUES (:1, :2, :3, :4, :5, :6, :7, :8, :9, :10, :11) RETURNING id_ "
      "INTO :12");

  const auto stmt = CreateStatement(
      sql, order.link_, order.quantity_ordered_, order.quantity_executed_,
      order.bill_total_.GetDiscountRate(),
      order.bill_total_.GetDiscountAmountInOrder(),
      order.bill_total_.GetTaxRate(), static_cast<int>(order.state_),
      order.created_at_.ToOracleDate(), order.client_id_,
      order.server_->GetId(), order.transaction_->GetId());
  stmt->registerOutParam(12, oracle::occi::OCCISTRING, 36);  // UUID length
  DefaultCommitHandler([&] { stmt->executeUpdate(); });
  order.id_ = stmt->getString(12);
}

void OrderRepo::QueryRelation(Order* order) const {
  order->server_ = server_repo_->FindWithOrderId(order->server_id_, 0, 20);
  order->transaction_ =
      transaction_repo_->FindWithOrderId(order->transaction_id_);
}
