//
// Created by ROG on 26/06/2025.
//

#ifndef ORDER_DTO_H
#define ORDER_DTO_H

#include <format>
#include <oatpp/codegen/dto/base_define.hpp>

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
#include "entity/order/order.h"
#include "modul/bill_total.h"

class BillTotalResponseDto final : public oatpp::DTO {
  DTO_INIT(BillTotalResponseDto, oatpp::DTO)

  DTO_FIELD(String, subTotal);
  DTO_FIELD(String, discountRate);
  DTO_FIELD(String, discountAmountInOrder);
  DTO_FIELD(String, taxRate);
  DTO_FIELD(String, discountAmountFromRate);
  DTO_FIELD(String, taxAmount);
  DTO_FIELD(String, totalDiscountAmount);
  DTO_FIELD(String, totalPayable);

  static Wrapper Create(const BillTotal& bill_total) {
    auto result = createShared();
    result->subTotal = std::format("{:.3f}", bill_total.GetSubTotal());
    result->discountRate =
        std::format("{:.1f}", bill_total.GetDiscountRate() * 100);
    result->discountAmountInOrder =
        std::format("{:.3f}", bill_total.GetDiscountAmountInOrder());
    result->taxRate = std::format("{:.3f}", bill_total.GetTaxRate());
    result->discountAmountFromRate =
        std::format("{:.3f}", bill_total.CalculateDiscountAmountFromRate());
    result->taxAmount = std::format("{:.3f}", bill_total.CalculateTaxAmount());
    result->totalDiscountAmount =
        std::format("{:.3f}", bill_total.CalculateTotalDiscountAmount());
    result->totalPayable =
        std::format("{:.3f}", bill_total.CalculateTotalPayable());
    return result;
  }
};

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

ENUM(OrderState, v_int8, VALUE(kInitial, 0, "Initial"),
     VALUE(kPending, 1, "Pending"), VALUE(kProcessing, 2, "Processing"),
     VALUE(kError, 3, "Error"), VALUE(kSuccess, 4, "Success"));

class OrderBaseDto : public oatpp::DTO {
  DTO_INIT(OrderBaseDto, oatpp::DTO)

  DTO_FIELD(String, link);
  DTO_FIELD(Int32, quantityOrdered);
  DTO_FIELD(Float64, amount);
};

class OrderResponseDto final : public OrderBaseDto {
  DTO_INIT(OrderResponseDto, OrderBaseDto)

  DTO_FIELD(String, id);
  DTO_FIELD(String, createdAt);
  DTO_FIELD(Int32, quantityExecuted);
  DTO_FIELD(Enum<OrderState>, state);
  DTO_FIELD(Object<BillTotalResponseDto>, billTotal);

  static Wrapper Create(Order* order) {
    auto result = createShared();

    result->id = std::move(order->id_);
    result->link = std::move(order->link_);
    result->quantityOrdered = order->quantity_ordered_;
    result->amount = order->bill_total_.CalculateTotalPayable();
    result->state = static_cast<OrderState>(static_cast<int>(order->state_));
    result->createdAt = order->created_at_.ToString();
    result->quantityExecuted = order->quantity_executed_;
    result->billTotal = BillTotalResponseDto::Create(order->bill_total_);
    return result;
  }
};

class OrderRequestDto final : public OrderBaseDto {
  DTO_INIT(OrderRequestDto, OrderBaseDto)

  DTO_FIELD(Int32, serverId);

  Order Create(const int client_id, const Server* server) const {
    return Order{std::move(*link.get()), quantityOrdered,
                 BillTotal{quantityOrdered, server->GetPricePerUnit()},
                 client_id, serverId};
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif  // ORDER_DTO_H
