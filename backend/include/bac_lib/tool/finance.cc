//
// Created by rog on 10/02/2025.
//

#include "finance.h"

#include <unicode/currunit.h>
#include <unicode/ucurr.h>

bool bac_lib::tool::finance::IsValidCurrency(std::string_view currency_code) {
    UErrorCode status = U_ZERO_ERROR;
    icu::CurrencyUnit currency(currency_code, status);
    return U_SUCCESS(status);
}
