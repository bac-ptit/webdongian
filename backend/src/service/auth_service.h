//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_SERVICE_AUTH_SERVICE_H
#define BACKEND_SERVICE_AUTH_SERVICE_H
#include <oatpp/Types.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

#include "repo/client_repo.h"

class ClientForLogining;
class AuthDto;
class Jwt;
class ClientReqeustForRegistering;
class AuthService {
  using Status = oatpp::web::protocol::http::Status;
 public:
  // [[nodiscard]] oatpp::Object<AuthDto> Register(
  //     const oatpp::Object<ClientReqeustForRegistering>& dto) const;
  //
  // [[nodiscard]] oatpp::Object<AuthDto> Login(const
  // oatpp::Object<ClientForLoginning>& dto) const;

  oatpp::String Register(
      const oatpp::Object<ClientReqeustForRegistering>& dto) const;

  oatpp::String Login(
      const oatpp::Object<ClientForLogining>& dto) const;

 private:
  OATPP_COMPONENT(std::shared_ptr<ClientRepo>, db_);
  OATPP_COMPONENT(std::shared_ptr<Jwt>, jwt_);
};

#endif  // BACKEND_SERVICE_AUTH_SERVICE_H
