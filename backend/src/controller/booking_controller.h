//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_CONTROLLER_BOOKING_SERVICE_CONTROLLER_H
#define BACKEND_CONTROLLER_BOOKING_SERVICE_CONTROLLER_H

#include <oatpp/web/client/ApiClient.hpp>

#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen
#include "service/booking_service.h"

class BookingController final
    : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  explicit BookingController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
      : ApiController(apiContentMappers, "/api/booking") {}

  ENDPOINT("GET", "/all", FindAll) {
    const auto result = booking_service_s_->FindAll();
    return createDtoResponse(Status::CODE_200, result);
  }

 private:
  OATPP_COMPONENT(std::shared_ptr<BookingService>, booking_service_s_);

};

#endif  // BACKEND_CONTROLLER_BOOKING_SERVICE_CONTROLLER_H
