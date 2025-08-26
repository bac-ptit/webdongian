//
// Created by ROG on 22/06/2025.
//

#include "booking.h"

#include <oatpp/macro/component.hpp>

#include "repo/service_repo.h"

Booking::Booking(std::string service_name) : name_(std::move(service_name)) {}

void Booking::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getNumber();
  name_ = streamOCCI_.getString();
}

void Booking::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(id_);
  streamOCCI_.setString(name_);
}