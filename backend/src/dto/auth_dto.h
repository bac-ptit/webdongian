#ifndef BACKEND_AUTH_DTO_H
#define BACKEND_AUTH_DTO_H

#include "client_dto.h"
#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AuthDto final : public oatpp::DTO {
  DTO_INIT(AuthDto, oatpp::DTO)

  DTO_FIELD(String, token);

 public:
  static Wrapper Create(const String& token) {
    auto result = createShared();
    result->token = token;
    return result;
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif /* BACKEND_AUTH_DTO_H */
