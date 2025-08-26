//
// Created by rog on 20/02/2025.
//

#include "error_handler.h"

#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>

#include "dto/error_dto.h"

ErrorHandler::ErrorHandler(
    const std::shared_ptr<oatpp::web::mime::ContentMappers>& mapper)
  : mapper_(mapper) {
}

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
ErrorHandler::renderError(
    const HttpServerErrorStacktrace& stacktrace) {
  // oatpp::data::stream::BufferOutputStream ss;
  // for (const auto& element : stacktrace.stack) {
  //   ss << element << '\n';
  // }

  // const auto error = ErrorDto::createShared(ss.toString());

  const auto error = ErrorDto::createShared(stacktrace.stack.front());
  std::vector<oatpp::String> accept;
  if (stacktrace.request) {
    accept = stacktrace.request->getHeaderValues("Accept");
  }

  auto mapper = mapper_->selectMapper(accept);
  if (!mapper) {
    mapper = mapper_->getDefaultMapper();
  }

  auto response = ResponseFactory::createResponse(
      stacktrace.status, error, mapper);
  for (const auto& [first, second] : stacktrace.headers.getAll()) {
    response->putHeader(first.toString(), second.toString());
  }
  return response;
}