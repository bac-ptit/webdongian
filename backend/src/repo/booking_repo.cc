//
// Created by ROG on 22/06/2025.
//

#include "booking_repo.h"

std::vector<std::unique_ptr<Booking>> BookingRepo::FindAllWithRelation() const {
  auto result = FindWithCondition();
  for (const auto& booking : result) {
    QueryRelation(booking.get());
  }
  return result;
}

void BookingRepo::QueryRelation(Booking* booking) const {
  booking->services_ = booking_element_repo_->FindAllWithRelation(booking->id_);
}