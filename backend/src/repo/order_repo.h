//
// Created by ROG on 26/06/2025.
//

#ifndef BACKEND_REPO_ORDER_REPO_H
#define BACKEND_REPO_ORDER_REPO_H
#include <oatpp/macro/component.hpp>

#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/order/order.h"
#include "server_repo.h"
#include "transaction_repo.h"

class OrderRepo final : public bac_lib::orcl::OracleQuery<Order> {
 public:
  using OracleQuery::OracleQuery;

  std::vector<std::unique_ptr<Order>> FindAllWithClientId(
      int client_id, int offset = 0,
      int limit = std::numeric_limits<int>::max()) const;

  void CreateOrder(Order& order);

  void QueryRelation(Order* order) const;

private:

  OATPP_COMPONENT(std::shared_ptr<ServerRepo>, server_repo_);
  OATPP_COMPONENT(std::shared_ptr<TransactionRepo>, transaction_repo_);
};

#endif  // BACKEND_REPO_ORDER_REPO_H
