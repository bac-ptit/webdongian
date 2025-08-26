//
// Created by ROG on 26/06/2025.
//

#ifndef BACKEND_CONTROLLER_ORDER_CONTROLLER_H
#define BACKEND_CONTROLLER_ORDER_CONTROLLER_H

#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen
#include "service/order_service.h"

/**
 * Sample Api Controller.
 */
class OrderController final : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  explicit OrderController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
      : ApiController(apiContentMappers, "/api/order") {}

  ENDPOINT("GET", "/", FindOrderByClientId, QUERY(Int32, offset, "offset", 0),
           QUERY(Int32, limit, "limit", std::numeric_limits<Int32>::max()),
           BUNDLE(String, user_id, "userId")) {
    const auto result =
        order_service_->FindByClientId(std::stoi(user_id), offset, limit);
    return createDtoResponse(Status::CODE_200, result);
  }

  ENDPOINT("POST", "/create", CreateOrder, BUNDLE(String, user_id, "userId"),
           BODY_DTO(Object<OrderRequestDto>, dto)) {
    const auto result = order_service_->CreateOrder(dto, std::stoi(user_id));
    return createDtoResponse(Status::CODE_201, result);
  }

  // TODO Insert Your endpoints here !!!

 private:
  OATPP_COMPONENT(std::shared_ptr<OrderService>, order_service_);
};

#endif  // BACKEND_CONTROLLER_ORDER_CONTROLLER_H
