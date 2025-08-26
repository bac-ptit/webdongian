//
// Created by ROG on 25/06/2025.
//

#include "transaction.h"

Transaction::Transaction(const double amount, const Type type,
                         const Status status,
                         const bac_lib::type::Date& created_at,
                         const bac_lib::type::Date& approved_at,
                         const PaymentMethod payment_method,
                         const std::string& idempotency_key,
                         const int client_id)
    : amount_(amount),
      type_(type),
      status_(status),
      created_at_(created_at),
      approved_at_(approved_at),
      payment_method_(payment_method),
      idempotency_key_(idempotency_key),
      client_id_(client_id) {}

void Transaction::readSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  id_ = streamOCCI_.getString();
  amount_ = streamOCCI_.getNumber();
  currency_ = streamOCCI_.getString();
  type_ = static_cast<Type>(static_cast<int>(streamOCCI_.getNumber()));
  status_ = static_cast<Status>(static_cast<int>(streamOCCI_.getNumber()));
  created_at_ = streamOCCI_.getDate();
  approved_at_ = streamOCCI_.getDate();
  payment_method_ =
      static_cast<PaymentMethod>(static_cast<int>(streamOCCI_.getNumber()));
  idempotency_key_ = streamOCCI_.getString();
  client_id_ = streamOCCI_.getNumber(); // Assuming client_id is also in the stream
}

void Transaction::writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept {
  streamOCCI_.setString(id_);
  streamOCCI_.setNumber(amount_);
  streamOCCI_.setString(currency_);
  streamOCCI_.setNumber(static_cast<int>(type_));
  streamOCCI_.setNumber(static_cast<int>(status_));
  streamOCCI_.setDate(created_at_);
  streamOCCI_.setDate(approved_at_);
  streamOCCI_.setNumber(static_cast<int>(payment_method_));
  streamOCCI_.setString(idempotency_key_);
  client_id_ = streamOCCI_.getNumber();
}