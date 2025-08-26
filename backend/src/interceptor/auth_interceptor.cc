//
// Created by rog on 02/03/2025.
//

#include "auth_interceptor.h"
AuthInterceptor::AuthInterceptor(const std::shared_ptr<Jwt>& jwt)
    : auth_handler_(jwt) {
  auth_endpoints_.route("GET", "/swagger/*", false);
  auth_endpoints_.route("GET", "/api-docs/oas-3.0.0.json", false);
  auth_endpoints_.route("POST", "/api/auth/register", false);
  auth_endpoints_.route("POST", "/api/auth/logout", false);
  auth_endpoints_.route("POST", "/api/auth/login", false);
  auth_endpoints_.route("GET", "/api/booking/all", false);
  auth_endpoints_.route("GET", "/api/booking/all", false);
}

std::shared_ptr<
    oatpp::web::server::interceptor::RequestInterceptor::OutgoingResponse>
AuthInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request) {
  if (const auto r = auth_endpoints_.getRoute(request->getStartingLine().method,
                                              request->getStartingLine().path);
      r && !r.getEndpoint()) {
    return nullptr;  // Continue without Authorization
  }
  // const auto authHeader =
  //     request->getHeader(oatpp::web::protocol::http::Header::AUTHORIZATION);

  const auto authHeader = request->getHeader("Cookie");

  if (const auto authObject = std::static_pointer_cast<Jwt::Payload>(
          auth_handler_.handleAuthorization(authHeader))) {
    request->putBundleData("userId", authObject->user_id);
    return nullptr;  // Continue - token is valid.
  }

  throw oatpp::web::protocol::http::HttpError(
      oatpp::web::protocol::http::Status::CODE_401, "Unauthorized", {});
}