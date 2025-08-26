//
// Created by ROG on 22/06/2025.
//

#include "client_service.h"

#include <oatpp/web/protocol/http/Http.hpp>

#include "dto/client_dto.h"
#include "repo/client_repo.h"
oatpp::Object<ClientResponse> ClientService::GetProfile(int id) const {
  const auto client = client_repo_->FindByPrimaryKeyWithRelation(id);
  OATPP_ASSERT_HTTP(client, Status::CODE_404, "Client not found");
  return ClientResponse::Create(client.get());
}