#ifndef BACKEND_SERVER_DTO_H
#define BACKEND_SERVER_DTO_H

#include <oatpp/codegen/dto/base_define.hpp>

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
#include "entity/server/server.h"

ENUM(ServerState, v_int8, VALUE(kActive, 0, "Active"),
     VALUE(kInactive, 1, "Inactive"), VALUE(kMaintenance, 2, "Maintenance"),
     VALUE(kDeath, 3, "Death"));

class ServerResponseDto final : public oatpp::DTO {
  DTO_INIT(ServerResponseDto, DTO);

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(String, host);
  DTO_FIELD(Int32, numberOfDayInEffect);
  DTO_FIELD(Int32, minQuantity);
  DTO_FIELD(Int32, maxQuantity, "maxQuantity");
  DTO_FIELD(Enum<ServerState>, state);
  DTO_FIELD(String, priceForInteraction);

  DTO_FIELD_INFO(maxQuantity) {
    info->description = "Maximum quantity of the server";
    info->required = false;
  }

 public:
  static Wrapper Create(Server* server) {
    auto dto = createShared();
    dto->id = server->id_;
    dto->name = std::move(server->name_);
    dto->host = std::move(server->host_);
    dto->numberOfDayInEffect = server->number_of_day_in_effect_;
    dto->minQuantity = server->min_quantity_;
    if (server->HasMaximumQuantity()) {
      dto->maxQuantity = server->max_quantity_;
    }
    dto->state = static_cast<ServerState>(server->state_);
    dto->priceForInteraction =
        bac_lib::tool::FormatCurrencyVND(server->price_for_unit_);
    return dto;
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif  // BACKEND_SERVER_DTO_H