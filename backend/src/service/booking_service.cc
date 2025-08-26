//
// Created by ROG on 22/06/2025.
//

#include "booking_service.h"

#include "dto/booking_service_dto.h"

oatpp::Vector<oatpp::Object<BookingDto>> BookingService::FindAll() const {
  const auto arr = booking_repo_->FindAllWithRelation();
  auto result = oatpp::Vector<oatpp::Object<BookingDto>>::createShared();
  result->reserve(arr.size());

  for (const auto& booking_service : arr) {
    result->emplace_back(BookingDto::Create(booking_service.get()));
  }
  return result;
}