//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_CONTROLLER_CLIENT_CONTROLLER_H
#define BACKEND_CONTROLLER_CLIENT_CONTROLLER_H

#include <oatpp/web/client/ApiClient.hpp>

#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen
#include "service/client_service.h"

class ClientController final : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  explicit ClientController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
      : ApiController(apiContentMappers, "/api/client") {}

  ENDPOINT("GET", "/profile", GetProfile, BUNDLE(String, user_id, "userId")) {
    const auto client = client_service_->GetProfile(std::stoi(user_id));
    return createDtoResponse(Status::CODE_200, client);
  }

 private:
  OATPP_COMPONENT(std::shared_ptr<ClientService>, client_service_);
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen

#endif  // BACKEND_CONTROLLER_CLIENT_CONTROLLER_H
