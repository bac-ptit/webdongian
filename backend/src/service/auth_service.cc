//
// Created by ROG on 22/06/2025.
//

#include "auth_service.h"

#include <memory>

#include "auth/jwt.h"
#include "dto/auth_dto.h"
#include "dto/client_dto.h"

// oatpp::Object<AuthDto> AuthService::Register(
//     const oatpp::Object<ClientReqeustForRegistering>& dto) const {
//   auto id = [&] {
//     auto client = dto->ToClient();
//     db_->CreateClient(client);
//     return id;
//   }();
//
//   const auto payload = std::make_shared<Jwt::Payload>(std::to_string(id));
//   const auto token = jwt_->CreateToken(payload);
//   return AuthDto::Create(token);
// }

oatpp::String AuthService::Register(
    const oatpp::Object<ClientReqeustForRegistering>& dto) const {
  const auto id = [&] {
    auto client = dto->ToClient();
    db_->CreateClient(client);
    return client.GetId();
  }();

  const auto payload = std::make_shared<Jwt::Payload>(std::to_string(id));
  const auto token = jwt_->CreateToken(payload);
  return token;
}

oatpp::String AuthService::Login(
    const oatpp::Object<ClientForLogining>& dto) const {
  const auto id = db_->Login(dto->username, dto->password);

  OATPP_ASSERT_HTTP(
      id, Status::CODE_401,
      "Invalid username or password");  // If client is nullptr, it means the
                                        // login failed.
  const auto payload = std::make_shared<Jwt::Payload>(std::to_string(*id));
  const auto token = jwt_->CreateToken(payload);

  return token;
}