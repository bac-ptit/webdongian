//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_CONTROLLER_AUTH_CONTROLLER_H
#define BACKEND_CONTROLLER_AUTH_CONTROLLER_H

#include <oatpp/web/client/ApiClient.hpp>

#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen
#include "dto/client_dto.h"
#include "service/auth_service.h"

class AuthService;
class AuthController final : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  explicit AuthController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
      : ApiController(apiContentMappers, "/api/auth") {}

  ENDPOINT("POST", "/register", Register,
           BODY_DTO(Object<ClientReqeustForRegistering>, dto)) {
    const auto token = auth_service_->Register(dto);
    auto result = createResponse(Status::CODE_200);
    // result->putHeader("Set-Cookie", "accessToken=" + token + "; HttpOnly; SameSite=Lax; Path=/");
    return result;
  }

  ENDPOINT("POST", "/logout", Logout) {
    const auto result = createResponse(Status::CODE_200);
    result->putHeader("Set-Cookie", "accessToken=; HttpOnly; Path=/; SameSite=Lax; Max-Age=0");
    return result;
  }

  ENDPOINT("POST", "/login", Login, BODY_DTO(Object<ClientForLogining>, dto)) {
    const auto token = auth_service_->Login(dto);
    auto result = createResponse(Status::CODE_200);
    result->putHeader("Set-Cookie",
      "accessToken=" + token + "; HttpOnly; Path=/; SameSite=Lax");

    return result;
  }

 private:
  OATPP_COMPONENT(std::shared_ptr<AuthService>, auth_service_);
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen

#endif  // BACKEND_CONTROLLER_AUTH_CONTROLLER_H
