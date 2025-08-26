//
// Created by ROG on 22/06/2025.
//

#include "service_repo.h"
std::vector<std::unique_ptr<Service>> ServiceRepo::FindAllWithRelation(
    int booking_id) const {
  auto arr = FindWithCondition("WHERE booking_id_ = :1", booking_id);
  for (auto&& service: arr) {
    service->servers_ = server_repo_->FindAllWithRelation(service->GetId());
  }
  return arr;
}