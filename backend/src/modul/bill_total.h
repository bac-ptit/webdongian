//
// Created by ROG on 26/06/2025.
//

#ifndef BACKEND_MODUL_AMOUNT_H
#define BACKEND_MODUL_AMOUNT_H

#include <occi.h>

#include <string>

namespace oracle::occi {}

/**
 * discount calculation rule, subtotal amount - discount amount in order then
 * calculate promotion
 */
class BillTotal {
  // All monetary values are rounded to the nearest thousand.

 public:
  BillTotal() = default;

  BillTotal(int quantity, double price_per_unit, double discount_rate = 0,
            double discount_amount_in_order = 0, double tax_rate = 0);

  void readSQL(const oracle::occi::AnyData& streamOCCI_) noexcept;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) const noexcept;

  double CalculateDiscountAmountFromRate() const;
  double CalculateTotalPayable() const;
  double CalculateTaxAmount() const;
  double CalculateTotalDiscountAmount() const;

  double GetDiscountRate() const noexcept;
  double GetDiscountAmountInOrder() const noexcept;
  double GetTaxRate() const noexcept;
  double GetSubTotal() const noexcept;

  /**
   *
   * @param quantity : then quantity of ther order, this is used to calculate
   */
  void SetSubTotal(int quantity);

 private:
  double discount_rate_{0};
  double discount_amount_in_order_{0};
  double tax_rate_{0};
  double price_per_unit_;

  // derived attribute
  double sub_total_{-1};
  mutable double discount_amount_from_rate{-1};
  mutable double tax_amount_{-1};
  mutable double total_discount_amount_{-1};
  mutable double total_payable_{-1};
};

#endif  // BACKEND_MODUL_AMOUNT_H
