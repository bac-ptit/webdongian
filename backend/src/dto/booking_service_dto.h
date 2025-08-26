//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_DTO_BOOKING_SERVICE_DTO_H
#define BACKEND_DTO_BOOKING_SERVICE_DTO_H

#include "client_dto.h"
#include "entity/service_booking/booking.h"
#include "entity/service_booking/service.h"
#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"
#include "server_dto.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ServiceDto final : public oatpp::DTO {
  DTO_INIT(ServiceDto, oatpp::DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(Vector<oatpp::Object<ServerResponseDto>>, servers);

  static Wrapper Create(const Service* booking_element) {
    const auto arr =
        oatpp::Vector<oatpp::Object<ServerResponseDto>>::createShared();

    for (const auto& server : booking_element->servers_) {
      arr->emplace_back(ServerResponseDto::Create(server.get()));
    }

    auto result = createShared();
    result->id = booking_element->id_;
    result->name = booking_element->name_;
    result->servers = arr;
    return result;
  }
};

class BookingDto final : public oatpp::DTO {
  DTO_INIT(BookingDto, oatpp::DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(Vector<oatpp::Object<ServiceDto>>, services);

  static Wrapper Create(const Booking* booking_service) {
    const auto elements =
        oatpp::Vector<oatpp::Object<ServiceDto>>::createShared();
    elements->reserve(booking_service->services_.size());
    for (const auto& element : booking_service->services_) {
      elements->emplace_back(ServiceDto::Create(element.get()));
    }

    auto result = createShared();
    result->id = booking_service->id_;
    result->name = booking_service->name_;
    result->services  = elements;

    return result;
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif  // BACKEND_DTO_BOOKING_SERVICE_DTO_H
