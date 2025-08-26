//
// Created by ROG on 22/06/2025.
//

#include "service.h"

#include <oatpp/macro/component.hpp>

#include "repo/server_repo.h"

Service::Service(std::string name, const int booking_id)
    : name_(std::move(name)), booking_id_(booking_id) {}

void Service::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getNumber();
  name_ = streamOCCI_.getString();
  booking_id_ = streamOCCI_.getNumber();
}

void Service::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(id_);
  streamOCCI_.setString(name_);
  streamOCCI_.setNumber(booking_id_);
}
int Service::GetId() const noexcept {
  return id_;
}