//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_REPO_BOOKING_ELEMENT_REPO_H
#define BACKEND_REPO_BOOKING_ELEMENT_REPO_H
#include <oatpp/macro/component.hpp>

#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/service_booking/service.h"
#include "server_repo.h"

class ServiceRepo final : public bac_lib::orcl::OracleQuery<Service> {
 public:
  using OracleQuery::OracleQuery;
  std::vector<std::unique_ptr<Service>> FindAllWithRelation(
      int booking_id) const;

 private:
  OATPP_COMPONENT(std::shared_ptr<ServerRepo>, server_repo_);
};

#endif  // BACKEND_REPO_BOOKING_ELEMENT_REPO_H
