//
// Created by ROG on 23/06/2025.
//

#ifndef COOKIE_HANDLER_H
#define COOKIE_HANDLER_H

#include "jwt.h"

class CookieAuthorizationHandler final
    : public oatpp::web::server::handler::AuthorizationHandler {
 public:
  explicit CookieAuthorizationHandler(const std::shared_ptr<Jwt>& jwt,
                             std::string key = "accessToken");

  std::shared_ptr<AuthorizationObject> handleAuthorization(
      const oatpp::String& authorizationHeader) override;

  [[nodiscard]] std::shared_ptr<AuthorizationObject> authorize(
      const oatpp::String& token) const;

 private:
  std::shared_ptr<Jwt> jwt_;
  std::string key_;
};

#endif  // COOKIE_HANDLER_H
