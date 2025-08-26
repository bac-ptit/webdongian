//
// Created by ROG on 23/06/2025.
//

#ifndef RESPONSE_INTERCEPTER_H
#define RESPONSE_INTERCEPTER_H

#include "config/frontend.h"
#include "oatpp/web/server/interceptor/ResponseInterceptor.hpp"

class CORSInterceptor : public oatpp::web::server::interceptor::ResponseInterceptor {
public:
  std::shared_ptr<OutgoingResponse> intercept(const std::shared_ptr<IncomingRequest>& request,
                                              const std::shared_ptr<OutgoingResponse>& response) override {
    response->putHeader("Access-Control-Allow-Origin", frontend::api);
    response->putHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    response->putHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, Cookie");
    response->putHeader("Access-Control-Allow-Credentials", "true");
    return response;
  }
};



#endif //RESPONSE_INTERCEPTER_H
