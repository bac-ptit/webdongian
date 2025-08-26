//
// Created by ROG on 25/06/2025.
//

#ifndef BACKEND_REPO_TRANSACTION_REPO_H
#define BACKEND_REPO_TRANSACTION_REPO_H
#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/transaction/transaction.h"

class TransactionRepo final : public bac_lib::orcl::OracleQuery<Transaction> {
 public:
  using OracleQuery::OracleQuery;

  std::vector<std::unique_ptr<Transaction>> FindWithClientId(
      int client_id, int offset = 0,
      int limit = std::numeric_limits<int>::max()) const;

  std::unique_ptr<Transaction> FindWithOrderId(int order_id) const;
};

#endif  // BACKEND_REPO_TRANSACTION_REPO_H
