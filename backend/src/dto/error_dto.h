//
// Created by rog on 02/03/2025.
//

#ifndef ERROR_DTO_H
#define ERROR_DTO_H

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ErrorDto final : public oatpp::DTO {
public:
    ErrorDto() = default;
    explicit ErrorDto(String error) : error(std::move(error)) {}

private:
    DTO_INIT(ErrorDto, DTO)
    DTO_FIELD(String, error);
};

#include OATPP_CODEGEN_END(DTO)

#endif  // ERROR_DTO_H
