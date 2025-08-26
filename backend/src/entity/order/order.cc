//
// Created by ROG on 26/06/2025.
//

#include "order.h"

#include <oatpp/macro/component.hpp>
#include <oatpp/web/server/interceptor/AllowCorsGlobal.hpp>

#include "repo/server_repo.h"
#include "repo/transaction_repo.h"

Order::Order(std::string link, const int quantity_ordered,
             const BillTotal& bill_total, const int client_id,
             const int server_id)
    : link_(std::move(link)),
      quantity_ordered_(quantity_ordered),
      bill_total_(bill_total),
      created_at_(bac_lib::type::Date::GetCurrentDate()),
      client_id_(client_id),
      server_id_(server_id) {}

void Order::ValidateQuantity() const {
  if (server_->IsSatisfiedQuantity(quantity_executed_)) {
    throw std::invalid_argument("quantity exceeds limit");
  }
}

void Order::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getString();
  link_ = streamOCCI_.getString();
  quantity_ordered_ = streamOCCI_.getNumber();
  quantity_executed_ = streamOCCI_.getNumber();
  bill_total_.readSQL(streamOCCI_);
  state_ = static_cast<State>(static_cast<int>(streamOCCI_.getNumber()));
  created_at_ = streamOCCI_.getDate();
  client_id_ = streamOCCI_.getNumber();
  server_id_ = streamOCCI_.getNumber();
  transaction_id_ = streamOCCI_.getNumber();

  bill_total_.SetSubTotal(quantity_ordered_);
}

void Order::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setString(id_);
  streamOCCI_.setString(link_);
  streamOCCI_.setNumber(quantity_ordered_);
  streamOCCI_.setNumber(quantity_executed_);
  bill_total_.writeSQL(streamOCCI_);
  streamOCCI_.setNumber(static_cast<int>(state_));
  streamOCCI_.setDate(created_at_);
  streamOCCI_.setNumber(client_id_);
  streamOCCI_.setNumber(server_id_);
  streamOCCI_.setNumber(transaction_id_);
}

const Order::TypeId& Order::GetId() const& noexcept { return id_; }

Order::TypeId&& Order::GetId() && noexcept { return std::move(id_); }