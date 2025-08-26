//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_REPO_BOOKING_SERVICE_REPO_H_
#define BACKEND_REPO_BOOKING_SERVICE_REPO_H_
#include <oatpp/macro/component.hpp>

#include "../../include/bac_lib/orcl/oracle_query.h"
#include "entity/service_booking/booking.h"
#include "service_repo.h"

class BookingRepo final : public bac_lib::orcl::OracleQuery<Booking> {
 public:
  using OracleQuery::OracleQuery;

  std::vector<std::unique_ptr<Booking>> FindAllWithRelation() const;

  void QueryRelation(Booking* booking) const;

 private:
  OATPP_COMPONENT(std::shared_ptr<ServiceRepo>, booking_element_repo_);
};

#endif  // BACKEND_REPO_BOOKING_SERVICE_REPO_H_
