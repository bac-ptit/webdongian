//
// Created by ROG on 22/06/2025.
//

#ifndef DATABASE_COMPONENT_H
#define DATABASE_COMPONENT_H
#include <oatpp/macro/component.hpp>

#include "global/global.h"
#include "repo/booking_repo.h"
#include "repo/client_repo.h"
#include "repo/order_repo.h"
#include "repo/server_repo.h"
#include "repo/service_repo.h"
#include "repo/transaction_repo.h"

class DatabaseComponent {
  OATPP_CREATE_COMPONENT(std::shared_ptr<ServerRepo>, server_repo)([] {
    return std::make_shared<ServerRepo>(global::env, global::conn);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<ServiceRepo>, service_repo)
  ([] { return std::make_shared<ServiceRepo>(global::env, global::conn); }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<TransactionRepo>, transaction_repo)
  ([] {
    return std::make_shared<TransactionRepo>(global::env, global::conn);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<OrderRepo>, order_repo)([] {
    return std::make_shared<OrderRepo>(global::env, global::conn);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<BookingRepo>, booking_repo)
  ([] { return std::make_shared<BookingRepo>(global::env, global::conn); }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<ClientRepo>, client_repo)
  ([] { return std::make_shared<ClientRepo>(global::env, global::conn); }());
};

#endif  // DATABASE_COMPONENT_H
