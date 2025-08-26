//
// Created by rog on 29/03/2025.
//

#include "date.h"

#include <format>

static oracle::occi::Environment* env = oracle::occi::Environment::createEnvironment();
namespace bac_lib::type {

Date::Date(std::chrono::sys_time<std::chrono::seconds> time) : time_(time) {}

Date::Date(const std::string& str, const char* format)
    : time_([&str, &format] {
          std::istringstream iss{str};
          std::chrono::sys_time<std::chrono::seconds> result;
          iss >> parse(format, result);
          if (!iss.fail()) {
              throw std::invalid_argument("Invalid date format");
          }
          return result;
      }()) {}

Date::Date(const oracle::occi::Date& occi_date)
    : time_([&occi_date] -> std::optional<std::chrono::sys_time<std::chrono::seconds>> {
          if (occi_date.isNull()) {
              return std::nullopt;
          }
          int year;
          uint32_t month, day, hour, minute, second;
          occi_date.getDate(year, month, day, hour, minute, second);

          const std::chrono::year_month_day ymd{std::chrono::year{year}, std::chrono::month{month},
                                                std::chrono::day{day}};
          const std::chrono::sys_days sd = (ymd);
          return std::chrono::sys_time{sd.time_since_epoch() +
                                       std::chrono::seconds{hour * 3600 + minute * 60 + second}};
      }()) {}

Date::Date(int year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
    : time_([&year, &month, &day, &hour, &minute, &second] {
          const std::chrono::year_month_day ymd{std::chrono::year{year}, std::chrono::month{month},
                                                std::chrono::day{day}};
          const std::chrono::sys_days sd = (ymd);
          return std::chrono::sys_time{sd.time_since_epoch() +
                                       std::chrono::seconds{hour * 3600 + minute * 60 + second}};
      }()) {}

Date::Date(const std::chrono::system_clock::time_point now)
    : time_(std::chrono::floor<std::chrono::seconds>(now)) {}

Date::operator std::string() const {
    return ToString();
}

Date::operator oracle::occi::Date() const {
    return ToOracleDate();
}

Date::operator bool() const { return time_.has_value(); }

Date Date::GetCurrentDate() {
  return Date(std::chrono::system_clock::now());
}

bool Date::IsNull() const {
    return time_.has_value();
}

void Date::PlusSeconds(const uint32_t second) {
    time_.value() += std::chrono::seconds{second};
}

void Date::PlusMinutes(const uint32_t minute) {
    time_.value() += std::chrono::minutes{minute};
}

void Date::PlusHours(const uint32_t hour) {
    time_.value() += std::chrono::hours{hour};
}

void Date::PlusDays(const uint32_t day) {
    time_.value() += std::chrono::days{day};
}

void Date::PlusWeeks(const uint32_t week) {
    time_.value() += std::chrono::weeks{week};
}

void Date::PlusMonths(const uint32_t month) {
    time_.value() += std::chrono::months{month};
}

void Date::PlusYears(const int year) {
    time_.value() += std::chrono::years{year};
}

void Date::PlusDate(const uint32_t year, const uint32_t month, const uint32_t day,
                    const uint32_t hour, const uint32_t minute, const uint32_t second) {
    time_.value() += std::chrono::years{year} + std::chrono::months{month} +
                     std::chrono::days{day} + std::chrono::hours{hour} +
                     std::chrono::minutes{minute} + std::chrono::seconds{second};
}

void Date::SubtractSeconds(const uint32_t second) {
    time_.value() -= std::chrono::seconds{second};
}

void Date::SubtractMinutes(const uint32_t minute) {
    time_.value() -= std::chrono::minutes{minute};
}

void Date::SubtractHours(const uint32_t hour) {
    time_.value() -= std::chrono::hours{hour};
}

void Date::SubtractDays(const uint32_t day) {
    time_.value() -= std::chrono::days{day};
}

void Date::SubtractWeeks(const uint32_t week) {
    time_.value() -= std::chrono::weeks{week};
}

void Date::SubtractMonths(const uint32_t month) {
    time_.value() -= std::chrono::months{month};
}

void Date::SubtractYears(const int year) {
    time_.value() -= std::chrono::years{year};
}

void Date::SubtractDate(const uint32_t year, const uint32_t month, const uint32_t day,
                        const uint32_t hour, const uint32_t minute, const uint32_t second) {
    time_.value() -=
        (std::chrono::years{year} + std::chrono::months{month} + std::chrono::days{day} +
         std::chrono::hours{hour} + std::chrono::minutes{minute} + std::chrono::seconds{second});
}

std::chrono::duration<long> Date::BetweenTime(const Date& other) const {
    const auto diff = time_.value() - other.time_.value();
    return diff;
}

oracle::occi::Date Date::ToOracleDate() const {
    const auto days_part = std::chrono::floor<std::chrono::days>(time_.value());
    const auto time_part = *time_ - days_part;

    const std::chrono::year_month_day ymd{days_part};
    const std::chrono::hh_mm_ss hms{time_part};

    const auto year = static_cast<int>(ymd.year());
    const auto month = static_cast<uint32_t>(ymd.month());
    const auto day = static_cast<uint32_t>(ymd.day());
    const auto hour = hms.hours().count();
    const auto minute = (hms.minutes().count());
    const auto second = (hms.seconds().count());

    return oracle::occi::Date(env, year, month, day, hour, minute, second);
}

std::string Date::ToString() const {
    return std::format("{:%Y-%m-%d %H:%M:%S}", time_.value());
}

}  // namespace bac_lib::type
