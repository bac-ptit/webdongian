#pragma once

#include <fmt/core.h>

#include <random>
#include <string>
#include <utility>

#include "../type/Date.h"

namespace oatpp::web::protocol::http::incoming {
class Request;
}

namespace bac_lib::tool {
/**
 * \brief Formats the given string by modifying it in place.
 *
 * \param str The string to be formatted.
 */
void FormatTitle(std::string& str);

/**
 * \brief Returns a formatted copy of the given string.
 *
 * \param str The string to be formatted.
 * \return A formatted copy of the input string.
 */
std::string FormatTitleCopy(std::string_view str);

/**
 * \brief Validates the given URL.
 *
 * This function checks if the provided URL is valid and throws an error if the
 * validation fails.
 *
 * \param url The URL to be validated.
 */
void ValidateUrl(std::string_view url);

/**
 * \brief Validates the given locale.
 *
 * This function checks if the provided locale is valid and throws an error if
 * the validation fails.
 *
 * \param locale_name The locale to be validated.
 */
void ValidateLocale(std::string_view locale_name);

/**
 * \brief Validates the given phone number.
 *
 * This function checks if the provided phone number is valid and returns true
 * if the validation passes.
 *
 * \param phone_number The phone number to be validated.
 * \return true if the phone number is valid, false otherwise.
 */
bool ValidatePhoneNumber(std::string_view phone_number);

/**
 * \brief Concatenates multiple C-style strings at compile time.
 *
 * This function takes multiple C-style string arguments and concatenates them
 * into a single `std::string`. The concatenation is performed at compile time
 * if possible.
 *
 * \param args The C-style string arguments to be concatenated.
 * \return A `std::string` containing the concatenated result.
 */
constexpr std::string StrCat(auto&&... args)
  requires(std::is_same_v<std::decay_t<decltype(args)>, const char*> && ...)
{
  std::string result;
  (result.append(args), ...);
  return result;
}

void CheckValidEmail(const std::string& email);

template <typename Compare>
constexpr std::string_view ToSQLOperator(Compare) {
  if constexpr (std::is_same_v<Compare, std::less_equal<>>) {
    return "<=";
  } else if constexpr (std::is_same_v<Compare, std::less<>>) {
    return "<";
  } else if constexpr (std::is_same_v<Compare, std::greater_equal<>>) {
    return ">=";
  } else if constexpr (std::is_same_v<Compare, std::greater<>>) {
    return ">";
  } else if constexpr (std::is_same_v<Compare, std::equal_to<>>) {
    return "=";
  } else if constexpr (std::is_same_v<Compare, std::not_equal_to<>>) {
    return "!=";
  } else {
    static_assert([] { return false; }(), "Unsupported comparator");
    std::unreachable();
  }
}

template <typename T, typename Compare, typename U>
constexpr T Contract(T&& value, Compare comp, const U& operand)
  requires std::is_same_v<std::decay_t<T>, std::decay_t<U>> ||
           std::is_convertible_v<std::decay_t<T>, std::decay_t<U>>
{
  if (comp(value, operand)) {
    return std::forward<T>(value);  // trả về chính kiểu T
  }
  throw std::invalid_argument(
      std::format("Value {} does not satisfy with operator {} and operand {}",
                  value, ToSQLOperator(comp), operand));
}

template <typename T, typename U>
constexpr T Contract(T&& value, const U& min, const U& max)
requires std::is_same_v<std::decay_t<T>, std::decay_t<U>> ||
           std::is_convertible_v<std::decay_t<T>, std::decay_t<U>>
{
  if (min <= value && value <= max) {
    return std::forward<T>(value);
  }
  throw std::invalid_argument(std::format(
      "Value {} does not satisfy with range [{}, {}]", value, min, max));
}

std::string FormatCurrencyVND(double amount);
}  // namespace bac_lib::tool