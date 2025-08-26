//
// Created by ROG on 24/06/2025.
//

#ifndef BACKEND_REPO_SERVER_REPO_H
#define BACKEND_REPO_SERVER_REPO_H
#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/server/server.h"

class ServerRepo final : public bac_lib::orcl::OracleQuery<Server> {
 public:
  using OracleQuery::OracleQuery;

  std::vector<std::unique_ptr<Server>> FindAllWithRelation(int service) const;

  std::unique_ptr<Server> FindWithOrderId(
      int order_id, int offset = 0,
      int limit = std::numeric_limits<int>::max()) const;
};

#endif  // BACKEND_REPO_SERVER_REPO_H
