//
// Created by rog on 10/02/2025.
//

#ifndef BAC_LIB_TOOL_FINANCE_H
#define BAC_LIB_TOOL_FINANCE_H
#include <string_view>

namespace bac_lib::tool::finance {

/**
 * \brief Checks if the given currency code is valid.
 *
 * \param currency_code The currency code to validate.
 * \return true if the currency code is valid, false otherwise.
 */
bool IsValidCurrency(std::string_view currency_code);

}  // namespace bac_lib::tool::finance

#endif  // BAC_LIB_TOOL_FINANCE_H
