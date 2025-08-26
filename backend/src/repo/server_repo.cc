//
// Created by ROG on 24/06/2025.
//

#include "server_repo.h"

std::vector<std::unique_ptr<Server>> ServerRepo::FindAllWithRelation(
    int service) const {
  auto arr = FindWithCondition(" WHERE service_id_ = :1", service);
  return arr;
}
std::unique_ptr<Server> ServerRepo::FindWithOrderId(int order_id, int offset,
                                                    int limit) const {
  auto arr = FindWithCondition(
      "WHERE order_id_ = :1 ORDER BY created_at_ DESC OFFSET :2 ROWS FETCH "
      "NEXT :3 ROWS ONLY",
      order_id, offset, limit);
  if (arr.empty()) {
    throw std::runtime_error("No server found for the given order ID");
  }
  return std::move(arr.front());
}