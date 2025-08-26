//
// Created by ROG on 22/06/2025.
//

#ifndef SERVICE_COMPONENT_H
#define SERVICE_COMPONENT_H
#include <oatpp/macro/component.hpp>

#include "service/auth_service.h"
#include "service/booking_service.h"
#include "service/client_service.h"
#include "service/order_service.h"

class ServiceComponent {
  OATPP_CREATE_COMPONENT(std::shared_ptr<AuthService>, auth_service)
  ([] { return std::make_shared<AuthService>(); }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<BookingService>, booking_service)
  ([] { return std::make_shared<BookingService>(); }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<ClientService>, client_service)
  ([] { return std::make_shared<ClientService>(); }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<OrderService>, order_service)
  ([] { return std::make_shared<OrderService>(); }());
};

#endif  // SERVICE_COMPONENT_H
