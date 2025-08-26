//
// Created by ROG on 6/22/2025.
//

#ifndef BACKEND_REPO_CLIENT_REPO_H
#define BACKEND_REPO_CLIENT_REPO_H
#include <oatpp/macro/component.hpp>

#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/client/client.h"
#include "transaction_repo.h"
#include "order_repo.h"

class ClientRepo final : public bac_lib::orcl::OracleQuery<Client> {
 public:
  using OracleQuery::OracleQuery;

  void CreateClient(Client& client);

  std::optional<Client::TypeId> Login(
      const std::string& email_or_phone_number,
      const std::string& password) const;

  std::unique_ptr<Client> FindByPrimaryKeyWithRelation(int id);

 private:
  OATPP_COMPONENT(std::shared_ptr<TransactionRepo>, transaction_repo_);
  OATPP_COMPONENT(std::shared_ptr<OrderRepo>, order_repo_);
};

#endif  // BACKEND_REPO_CLIENT_REPO_H
