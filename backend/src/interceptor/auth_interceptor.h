//
// Created by rog on 02/03/2025.
//

#ifndef AUTH_INTERCEPTOR_H
#define AUTH_INTERCEPTOR_H
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/interceptor/RequestInterceptor.hpp>

#include "auth/auth_handler.h"
#include "auth/cookie_handler.h"
#include "auth/jwt.h"

class AuthInterceptor final : public oatpp::web::server::interceptor::RequestInterceptor {
public:
    explicit AuthInterceptor(const std::shared_ptr<Jwt>& jwt);
    std::shared_ptr<OutgoingResponse> intercept(
        const std::shared_ptr<IncomingRequest>& request) override;

private:
    // AuthHandler auth_handler_;
  CookieAuthorizationHandler auth_handler_;
    oatpp::web::server::HttpRouterTemplate<bool> auth_endpoints_;
};

#endif  // AUTH_INTERCEPTOR_H
