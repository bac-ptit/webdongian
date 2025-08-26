//
// Created by rog on 02/03/2025.
//

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <oatpp/web/mime/ContentMappers.hpp>
#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>
#include <oatpp/web/server/handler/ErrorHandler.hpp>

class ErrorHandler final : public oatpp::web::server::handler::DefaultErrorHandler {
    using OutgoingResponse = oatpp::web::protocol::http::outgoing::Response;
    using Status = oatpp::web::protocol::http::Status;
    using ResponseFactory = oatpp::web::protocol::http::outgoing::ResponseFactory;

public:
    explicit ErrorHandler(const std::shared_ptr<oatpp::web::mime::ContentMappers>& mapper);

    std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> renderError(
        const HttpServerErrorStacktrace& stacktrace) override;

private:
    std::shared_ptr<oatpp::web::mime::ContentMappers> mapper_;
};

#endif  // ERROR_HANDLER_H
