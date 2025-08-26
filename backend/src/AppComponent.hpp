#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "auth/jwt.h"
#include "components/database_component.h"
#include "components/service_component.h"
#include "components/swagger_component.h"
#include "error_handler.h"
#include "interceptor/auth_interceptor.h"
#include "interceptor/cor_response_intercepter.h"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/interceptor/AllowCorsGlobal.hpp"

/**
 *  Class which creates and holds Application components and registers
 * components in oatpp::base::Environment Order of components initialization is
 * from top to bottom
 */
class AppComponent {
 public:
  OATPP_CREATE_COMPONENT(std::shared_ptr<Jwt>, jwt)([] {
    return std::make_shared<Jwt>("Ilovewife", "you");
  }());

  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(
      std::shared_ptr<oatpp::network::ServerConnectionProvider>,
      serverConnectionProvider)([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"0.0.0.0", 8000, oatpp::network::Address::IP_4});
  }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                         httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's
   * API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>,
                         apiContentMappers)([] {
    auto json = std::make_shared<oatpp::json::ObjectMapper>();
    json->serializerConfig().json.useBeautifier = true;

    auto mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
    mappers->putMapper(json);

    return mappers;
  }());

  /**
   *  Create ConnectionHandler component which uses Router component to route
   * requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                         serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                    router);  // get Router component
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>,
                    contentMappers);
    OATPP_COMPONENT(std::shared_ptr<Jwt>, jwt);

    auto result =
        oatpp::web::server::HttpConnectionHandler::createShared(router);
    result->setErrorHandler(std::make_shared<ErrorHandler>(contentMappers));

    result->addRequestInterceptor(
        std::make_shared<
            oatpp::web::server::interceptor::AllowOptionsGlobal>());
    result->addRequestInterceptor(std::make_shared<AuthInterceptor>(jwt));
    // result->addResponseInterceptor(
    //     std::make_shared<oatpp::web::server::interceptor::AllowCorsGlobal>());
    result->addResponseInterceptor(std::make_shared<CORSInterceptor>());
    return result;
  }());

  DatabaseComponent database_component;
  ServiceComponent service_component;
  SwaggerComponent swagger_component;
};

#endif /* AppComponent_hpp */
