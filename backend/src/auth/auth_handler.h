//
// Created by rog on 02/03/2025.
//

#ifndef AUTH_HANDLER_H
#define AUTH_HANDLER_H

#include "jwt.h"

class AuthHandler final : public oatpp::web::server::handler::BearerAuthorizationHandler{
public:
    explicit AuthHandler(const std::shared_ptr<Jwt>& jwt);

    std::shared_ptr<AuthorizationObject> authorize(const oatpp::String&
    token) override;


   private:
    std::shared_ptr<Jwt> jwt_;
};

#endif  // AUTH_HANDLER_H
