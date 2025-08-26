//
// Created by ROG on 23/06/2025.
//

#include "cookie_handler.h"

#include <utility>
CookieAuthorizationHandler::CookieAuthorizationHandler(
    const std::shared_ptr<Jwt>& jwt, std::string key)
    : AuthorizationHandler("Cookie", "API"), jwt_(jwt), key_(std::move(key)) {}
std::shared_ptr<
    oatpp::web::server::handler::AuthorizationHandler::AuthorizationObject>

CookieAuthorizationHandler::handleAuthorization(
    const oatpp::String& authorizationHeader) {
  static auto first_part = key_ + "=";
  static v_buff_size length = first_part.length();

  if (authorizationHeader && authorizationHeader->size() > length &&
      oatpp::utils::String::compare(authorizationHeader->data(), length, first_part.data(),
                                    length) == 0) {
    auto &temp = *authorizationHeader;

    auto it = std::find_if(temp.begin() + length, temp.end(), [](char c) {
      return c == ';' || c == ' ' || c == '\t';
    });

    auto token = oatpp::String(temp.data() + length, std::distance(temp.begin() + length, it));

    auto authResult = authorize(token);
    if (authResult) {
      return authResult;
    }

    Headers responseHeaders;
    addErrorResponseHeaders(responseHeaders);
    throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                    "Unauthorized", responseHeaders);
  }

  Headers responseHeaders;
  addErrorResponseHeaders(responseHeaders);
  throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                  "Authorization Required", responseHeaders);
}

std::shared_ptr<
    oatpp::web::server::handler::AuthorizationHandler::AuthorizationObject>
CookieAuthorizationHandler::authorize(const oatpp::String& token) const {
  return jwt_->ReadAndVerifyToken(token);
}