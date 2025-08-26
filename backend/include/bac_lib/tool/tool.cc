#include "tool.h"

#include <absl/strings/str_cat.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/locale.hpp>
#include <boost/url.hpp>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <regex>
#include <string>

void bac_lib::tool::FormatTitle(std::string& str) {
  boost::algorithm::trim(str);
  boost::algorithm::replace_all(str, "\\s+", "");
  auto unicode_string = icu::UnicodeString{str.c_str()};
  str.clear();
  unicode_string.toTitle(nullptr).toUTF8String(str);
}

std::string bac_lib::tool::FormatTitleCopy(std::string_view str) {
  constexpr auto trim_front = std::views::drop_while(::isspace);

  constexpr auto trim_back =
      std::views::reverse | trim_front | std::views::reverse;

  auto to_title_case = [](auto&& split_str) {
    std::string_view str_view(&*split_str.begin(),
                              std::ranges::distance(split_str));
    icu::UnicodeString unicode_word{str_view.data(),
                                    static_cast<int>(str_view.length())};
    unicode_word.toTitle(nullptr);
    std::string result;
    unicode_word.toUTF8String(result);
    return result;
  };

  return str | trim_front | trim_back | std::views::split(' ') |
         std::views::filter([](auto&& split_st) { return !split_st.empty(); }) |
         std::views::transform(to_title_case) | std::views::join_with(' ') |
         std::ranges::to<std::string>();
}

void bac_lib::tool::ValidateUrl(const std::string_view url) {
  if (const auto result = boost::urls::parse_uri(url); !result) {
    throw std::runtime_error(result.error().message());
  }
}

void bac_lib::tool::ValidateLocale(const std::string_view locale_name) {
  static boost::locale::generator gen;
  std::locale temp = gen(std::string{locale_name});
}

bool bac_lib::tool::ValidatePhoneNumber(const std::string_view phone_number) {
  // Xxxxxxxxxx or +XXxxxxxxxxx
  if (!(phone_number.length() == 10 ||
        (phone_number.length() == 12 && phone_number.front() == '+'))) {
    return false;
  }

  auto it = phone_number.begin();
  if (*it == '+') {
    ++it;
  }
  return std::all_of(it, phone_number.end(), isdigit);
}

void bac_lib::tool::CheckValidEmail(const std::string& email) {
  static std::regex pattern(
      "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
  if (const auto temp = std::regex_match(email, pattern); !temp) {
    throw std::invalid_argument("Invalid email format");
  }
}

std::string bac_lib::tool::FormatCurrencyVND(double amount) {
  static std::locale loc("vi_VN");
  return fmt::format(loc, "{:L}đ", amount);
}
