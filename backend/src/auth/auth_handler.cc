//
// Created by rog on 02/03/2025.
//

#include "auth_handler.h"
AuthHandler::AuthHandler(const std::shared_ptr<Jwt>& jwt)
    : BearerAuthorizationHandler("API"), jwt_(jwt) {}

std::shared_ptr<oatpp::web::server::handler::AuthorizationHandler::AuthorizationObject>
AuthHandler::authorize(const oatpp::String& token) {
    return jwt_->ReadAndVerifyToken(token);
}