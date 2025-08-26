//
// Created by ROG on 6/22/2025.
//

#include "client.h"

#include <oatpp/macro/component.hpp>

#include "repo/order_repo.h"
#include "repo/transaction_repo.h"


Client::Client(std::string phone_number, std::string email,
               const double balance, const bac_lib::type::Date register_date,
               std::string password)
    : phone_number_(std::move(phone_number)),
      email_(std::move(email)),
      balance_(balance),
      register_date_(register_date),
      password_(std::move(password)) {
  bac_lib::tool::CheckValidEmail(email_);
  if (balance < 0) {
    throw std::invalid_argument("Invalid balance");
  }
}

void Client::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getNumber();
  phone_number_ = streamOCCI_.getString();
  email_ = streamOCCI_.getString();
  balance_ = streamOCCI_.getNumber();
  register_date_ = streamOCCI_.getDate();
  password_ = streamOCCI_.getString();
}

void Client::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setNumber(id_);
  streamOCCI_.setString(phone_number_);
  streamOCCI_.setString(email_);
  streamOCCI_.setNumber(balance_);
  streamOCCI_.setDate(register_date_);
  streamOCCI_.setString(password_);
}

int Client::GetId() const { return id_; }

void Client::CheckPassword(const std::string_view password) {
  if (password.empty()) {
    throw std::invalid_argument("Password cannot be empty");
  }
  if (password.length() < 6) {
    throw std::invalid_argument("Password is too short");
  }
  if (password.length() > 16) {
    throw std::invalid_argument("Password is too long");
  }
}

void Client::ChangePassword(std::string new_password) {
  if (password_ == new_password) {
    throw std::invalid_argument(
        "New password cannot be the same as the old one");
  }
  password_ = std::move(new_password);
}

void Client::ChangeBalance(const double amount) {
  if (balance_ + amount < 0) {
    throw std::invalid_argument("Insufficient balance");
  }
  balance_ += amount;
}