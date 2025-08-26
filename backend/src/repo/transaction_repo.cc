//
// Created by ROG on 25/06/2025.
//

#include "transaction_repo.h"
std::vector<std::unique_ptr<Transaction>> TransactionRepo::FindWithClientId(
    int client_id, int offset, int limit) const {
  return FindWithCondition(
      "WHERE client_id_ = :1 ORDER BY created_at_ DESC "
      "OFFSET :2 ROWS "
      "FETCH NEXT :3 ROWS ONLY",
      client_id, offset, 100);
}

std::unique_ptr<Transaction> TransactionRepo::FindWithOrderId(int order_id) const {
  auto arr = FindWithCondition("WHERE order_id_ = :1", order_id);
  if (arr.empty()) {
    throw std::invalid_argument("No transaction found for the given order ID");
  }
  return std::move(arr.front());
}