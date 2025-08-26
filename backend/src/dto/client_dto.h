//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_CLIENT_DTO_H
#define BACKEND_CLIENT_DTO_H

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"
#include "transaction_dto.h"
#include "order_dto.h"

#include OATPP_CODEGEN_BEGIN(DTO)
#include "entity/client/client.h"

class ClientForLogining : public oatpp::DTO {
  DTO_INIT(ClientForLogining, DTO)

  DTO_FIELD(String, username);
  DTO_FIELD(String, password);
};

class ClientReqeustForRegistering : public oatpp::DTO {
  DTO_INIT(ClientReqeustForRegistering, oatpp::DTO);

  DTO_FIELD(String, phoneNumber);
  DTO_FIELD(String, email);
  DTO_FIELD(String, password);

  [[nodiscard]] Client ToClient() const {
    return Client{*phoneNumber.get(), *email.get(), 0,
                  bac_lib::type::Date::GetCurrentDate(), *password.get()};
  }
};

class ClientResponse final : public oatpp::DTO {
  DTO_INIT(ClientResponse, DTO);

  static Wrapper Create(Client* client) {
    auto transactions = Vector<Object<TransactionResponseDto>>::createShared();
    transactions->reserve(client->transactions_.size());
    std::ranges::transform(
        client->transactions_, std::back_inserter(*transactions),
        [](const auto& transaction) {
          return TransactionResponseDto::Create(transaction.get());
        });

    auto orders = Vector<Object<OrderResponseDto>>::createShared();
    orders->reserve(client->orders_.size());
    std::ranges::transform(client->orders_, std::back_inserter(*orders),
                           [](const auto& order) {
                             return OrderResponseDto::Create(order.get());
                           });

    auto result = createShared();
    result->phoneNumber = std::move(client->phone_number_);
    result->email = std::move(client->email_);
    result->balance = std::format("{:.3f}đ", client->balance_);
    result->registerDate = client->register_date_.ToString();
    result->transactions = std::move(transactions);
    result->orders = std::move(orders);
    return result;
  }

 private:
  DTO_FIELD(String, phoneNumber);
  DTO_FIELD(String, email);
  DTO_FIELD(String, balance);
  DTO_FIELD(String, registerDate);
  DTO_FIELD(Vector<Object<TransactionResponseDto>>, transactions);
  DTO_FIELD(Vector<Object<OrderResponseDto>>, orders);
};

#include OATPP_CODEGEN_END(DTO)

#endif  // BACKEND_CLIENT_DTO_H
