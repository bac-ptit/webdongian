//
// Created by ROG on 26/06/2025.
//

#include "order_service.h"
oatpp::Vector<oatpp::Object<OrderResponseDto>> OrderService::FindByClientId(
    const int client_id, const int offset, const int limit) const {
  auto arr = order_repo_->FindAllWithClientId(client_id, offset, limit);

  auto result = oatpp::Vector<oatpp::Object<OrderResponseDto>>::createShared();
  result->reserve(arr.size());
  std::ranges::transform(arr, std::back_inserter(*result),
                         [](const std::unique_ptr<Order>& order) {
                           return OrderResponseDto::Create(order.get());
                         });

  return result;
}

oatpp::Object<OrderResponseDto> OrderService::CreateOrder(
    const oatpp::Object<OrderRequestDto>& dto, const int client_id) const {
  const auto server = server_repo_->FindByPrimaryKey(*dto->serverId);
  auto order = dto->Create(client_id, server.get());
  order_repo_->CreateOrder(order);
  return OrderResponseDto::Create(&order);
}