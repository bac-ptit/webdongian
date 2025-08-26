//
// Created by rog on 29/03/2025.
//

#ifndef BAC_LIB_TYPE_DATE_H
#define BAC_LIB_TYPE_DATE_H
#include <occi.h>

#include <chrono>
#include <optional>
namespace bac_lib::type {
class Date {
 public:
  Date() = default;

  explicit Date(std::chrono::sys_time<std::chrono::seconds> time);

  explicit Date(const std::string& str, const char* format = "%F %T");

  // ReSharper disable once CppNonExplicitConvertingConstructor
  Date(const oracle::occi::Date& occi_date);

  explicit Date(int year, uint32_t month, uint32_t day, uint32_t hour,
                uint32_t minute, uint32_t second);

  // ReSharper disable once CppNonExplicitConvertingConstructor
  Date(const std::chrono::system_clock::time_point now);

  // ReSharper disable once CppNonExplicitConversionOperator
  operator std::string() const;

  // ReSharper disable once CppNonExplicitConversionOperator
  operator oracle::occi::Date() const;

  // ReSharper disable once CppNonExplicitConversionOperator
  operator bool() const;

  auto operator<=>(const Date&) const = default;

  auto operator<=>(
      const std::chrono::sys_time<std::chrono::seconds>& time) const {
    return time_.value() <=> time;
  }

  auto operator<=>(const std::chrono::system_clock::time_point& now) const {
    return time_.value() <=> now;
  };

  template <typename Rep, typename Period>
  Date operator+=(std::chrono::duration<Rep, Period> duration) {
    time_.value() += duration;
    return *this;
  }

  template <typename Rep, typename Period>
  Date operator-=(std::chrono::duration<Rep, Period> duration) {
    time_.value() -= duration;
    return *this;
  }

  static Date GetCurrentDate();

  bool IsNull() const;

  void PlusSeconds(uint32_t second);
  void PlusMinutes(uint32_t minute);
  void PlusHours(uint32_t hour);
  void PlusDays(uint32_t day);
  void PlusWeeks(uint32_t week);
  void PlusMonths(uint32_t month);
  void PlusYears(int year);
  void PlusDate(uint32_t year, uint32_t month = 0, uint32_t day = 0,
                uint32_t hour = 0, uint32_t minute = 0, uint32_t second = 0);

  void SubtractSeconds(uint32_t second);
  void SubtractMinutes(uint32_t minute);
  void SubtractHours(uint32_t hour);
  void SubtractDays(uint32_t day);
  void SubtractWeeks(uint32_t week);
  void SubtractMonths(uint32_t month);
  void SubtractYears(int year);
  void SubtractDate(uint32_t year, uint32_t month, uint32_t day, uint32_t hour,
                    uint32_t minute, uint32_t second);

  std::chrono::duration<long> BetweenTime(const Date& other) const;

  oracle::occi::Date ToOracleDate() const;
  std::string ToString() const;

 private:
  template <typename Rep, typename Period>
  friend Date operator+(const Date& date,
                        std::chrono::duration<Rep, Period> duration) {
    Date result{date};
    return result + duration;
  }

  template <typename Rep, typename Period>
  friend Date operator-(const Date& date,
                        std::chrono::duration<Rep, Period> duration) {
    Date result{date};
    return result - duration;
  }

  std::optional<std::chrono::sys_time<std::chrono::seconds>> time_;
};

}  // namespace bac_lib::type

#endif  // BAC_LIB_TYPE_DATE_H
