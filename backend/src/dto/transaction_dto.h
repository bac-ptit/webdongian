//
// Created by ROG on 25/06/2025.
//

#ifndef TRANSACTION_DTO_H
#define TRANSACTION_DTO_H
#include <oatpp/codegen/dto/base_define.hpp>
#include <oatpp/codegen/dto/enum_define.hpp>

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
#include "entity/transaction/transaction.h"

class Transaction;
ENUM(TransactionType, v_uint8, VALUE(kTopUp, 0, "Top Up"),
     VALUE(kWithdrawal, 1, "Withdrawal"), VALUE(kPurchase, 2, "Purchase"));

ENUM(TransactionStatus, v_uint8, VALUE(kInitiated, 0, "Initiated"),
     VALUE(kPending, 1, "Pending"), VALUE(kProcessing, 2, "Processing"),
     VALUE(kFailed, 3, "Failed"), VALUE(kRefunded, 4, "Refunded"),
     VALUE(kSuccess, 5, "Success"));

ENUM(PaymentMethod, v_uint8, VALUE(kBankTransfer, 0, "Bank Transfer"),
     VALUE(kCreditCard, 1, "Credit Card"), VALUE(kMomo, 2, "Momo"),
     VALUE(kZaloPay, 3, "Zalo Pay"));

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

class TransactionDtoBase : public oatpp::DTO {
  DTO_INIT(TransactionDtoBase, DTO);

  DTO_FIELD(String, amount);
  DTO_FIELD(String, currency, "VND");
  DTO_FIELD(Enum<TransactionType>, type);
  DTO_FIELD(Enum<TransactionStatus>, status);
  DTO_FIELD(Enum<PaymentMethod>, paymentMethod);
};

class TransactionResponseDto final : public TransactionDtoBase {
  DTO_INIT(TransactionResponseDto, TransactionDtoBase);

  DTO_FIELD(String, id);
  DTO_FIELD(String, createdAt);
  DTO_FIELD(String, approvedAt);

  static Wrapper Create(Transaction* transaction) {
    auto result = createShared();
    result->id = transaction->id_;
    result->amount = bac_lib::tool::FormatCurrencyVND(transaction->amount_);
    result->currency = transaction->currency_;
    result->type = static_cast<TransactionType>(transaction->type_);
    result->status = static_cast<TransactionStatus>(transaction->status_);
    result->paymentMethod = static_cast<PaymentMethod>(transaction->payment_method_);
    result->createdAt = transaction->created_at_.ToString();
    result->approvedAt = transaction->approved_at_.ToString();
    return result;
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif  // TRANSACTION_DTO_H
