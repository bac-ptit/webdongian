//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_SERVICE_CLIENT_SERVICE_H
#define BACKEND_SERVICE_CLIENT_SERVICE_H
#include <oatpp/Types.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

class ClientReqeustForRegistering;
class ClientResponse;
class ClientRepo;
class ClientService {
  using Status = oatpp::web::protocol::http::Status;

 public:
  oatpp::Object<ClientResponse> GetProfile(int id) const;
 private:
  OATPP_COMPONENT(std::shared_ptr<ClientRepo>, client_repo_);
};

#endif  // BACKEND_SERVICE_CLIENT_SERVICE_H
