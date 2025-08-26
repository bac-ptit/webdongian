//
// Created by ROG on 26/06/2025.
//

#ifndef BACKEND_SERVICE_ORDER_SERVICE_H
#define BACKEND_SERVICE_ORDER_SERVICE_H
#include <oatpp/Types.hpp>
#include <oatpp/macro/component.hpp>

#include "repo/order_repo.h"
#include "dto/order_dto.h"

class OrderService {
 public:
  oatpp::Vector<oatpp::Object<OrderResponseDto>> FindByClientId(int client_id, int offset, int limit) const;

  oatpp::Object<OrderResponseDto> CreateOrder(const oatpp::Object<OrderRequestDto>& dto, int client_id) const;
 private:
  OATPP_COMPONENT(std::shared_ptr<OrderRepo>, order_repo_);
  OATPP_COMPONENT(std::shared_ptr<ServerRepo>, server_repo_);
};

#endif  // BACKEND_SERVICE_ORDER_SERVICE_H
