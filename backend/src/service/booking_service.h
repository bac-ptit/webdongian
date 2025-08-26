//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_SERVICE_BOOKING_SERVICE_S_H
#define BACKEND_SERVICE_BOOKING_SERVICE_S_H
#include <oatpp/Types.hpp>
#include <oatpp/macro/component.hpp>

#include "../../include/bac_lib/orcl/oracle_query.h"
#include "dto/booking_service_dto.h"
#include "repo/booking_repo.h"

class BookingService {
 public:
  oatpp::Vector<oatpp::Object<BookingDto>> FindAll() const;

 private:
  OATPP_COMPONENT(std::shared_ptr<BookingRepo>, booking_repo_);
};

#endif  // BACKEND_SERVICE_BOOKING_SERVICE_S_H
