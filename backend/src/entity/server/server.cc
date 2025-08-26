//
// Created by ROG on 24/06/2025.
//

#include "server.h"

#include <utility>

Server::Server(const int id, std::string name, std::string host,
               const bac_lib::type::Date created_at,
               const int number_of_day_in_effect, const int quantity,
               const double price_for_interaction, const State state,
               const int service_id)
    : id_(id),
      name_(std::move(name)),
      host_(std::move(host)),
      created_at_(created_at),
      number_of_day_in_effect_(number_of_day_in_effect),
      min_quantity_(quantity),
      price_for_unit_(price_for_interaction),
      state_(state),
      service_id_(service_id) {}

Server::Server(const int id, std::string name, std::string host,
               const bac_lib::type::Date& created_at,
               const int number_of_day_in_effect, const int min_quantity,
               const int max_quantity, const double price_for_interaction,
               const State state, const int service_id)
    : id_(id),
      name_(std::move(name)),
      host_(std::move(host)),
      created_at_(created_at),
      number_of_day_in_effect_(number_of_day_in_effect),
      min_quantity_(min_quantity),
      max_quantity_(max_quantity),
      price_for_unit_(price_for_interaction),
      state_(state),
      service_id_(service_id) {}

bool Server::HasMaximumQuantity() const noexcept {
  return max_quantity_ != std::numeric_limits<int>::max();
}

bool Server::IsSatisfiedQuantity(const int quantity) const noexcept {
  return min_quantity_ <= quantity && max_quantity_ >= quantity;
}

void Server::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getNumber();
  name_ = streamOCCI_.getString();
  host_ = streamOCCI_.getString();
  created_at_ = streamOCCI_.getDate();
  number_of_day_in_effect_ = streamOCCI_.getNumber();
  min_quantity_ = streamOCCI_.getNumber();
  max_quantity_ = streamOCCI_.getNumber();
  price_for_unit_ = streamOCCI_.getNumber();
  state_ = static_cast<State>(static_cast<int>(streamOCCI_.getNumber()));
  service_id_ = streamOCCI_.getNumber();
}

void Server::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(id_);
  streamOCCI_.setString(name_);
  streamOCCI_.setString(host_);
  streamOCCI_.setDate(created_at_);
  streamOCCI_.setNumber(number_of_day_in_effect_);
  streamOCCI_.setNumber(min_quantity_);
  streamOCCI_.setNumber(max_quantity_);
  streamOCCI_.setNumber(price_for_unit_);
  streamOCCI_.setNumber(static_cast<int>(state_));
  streamOCCI_.setNumber(service_id_);
}

int Server::GetId() const noexcept { return id_; }
double Server::GetPricePerUnit() const noexcept { return price_for_unit_; }
