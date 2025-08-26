//
// Created by ROG on 26/06/2025.
//

#include "bill_total.h"

#include <ranges>

#include "../../include/bac_lib/tool/tool.h"

using bac_lib::tool::Contract;

static double RoundWithThousand(const double value) {
  return std::round(value / 1000.0) * 1000.0;
}

BillTotal::BillTotal(int quantity, double price_per_unit, double discount_rate,
                     double discount_amount_in_order, double tax_rate)
    : discount_rate_(Contract(RoundWithThousand(discount_rate), 0, 1)),
      discount_amount_in_order_(Contract(
          RoundWithThousand(discount_amount_in_order), std::greater{}, 0)),
      tax_rate_(Contract(RoundWithThousand(tax_rate), std::greater_equal{}, 0)),
      price_per_unit_(RoundWithThousand(price_per_unit)),
      sub_total_(
          Contract(quantity, std::greater{}, 0) *
          Contract(RoundWithThousand(price_per_unit), std::greater{}, 0)) {}

void BillTotal::readSQL(const oracle::occi::AnyData& streamOCCI_) noexcept {
  price_per_unit_ = streamOCCI_.getNumber();
  discount_rate_ = streamOCCI_.getNumber();
  discount_amount_in_order_ = streamOCCI_.getNumber();
  tax_rate_ = streamOCCI_.getNumber();
}

void BillTotal::writeSQL(oracle::occi::AnyData& streamOCCI_) const noexcept {
  streamOCCI_.setNumber(price_per_unit_);
  streamOCCI_.setNumber(discount_rate_);
  streamOCCI_.setNumber(discount_amount_in_order_);
  streamOCCI_.setNumber(tax_rate_);
}

double BillTotal::CalculateDiscountAmountFromRate() const {
  if (discount_amount_from_rate == -1) {
    discount_amount_from_rate = RoundWithThousand(
        (sub_total_ - discount_amount_in_order_) * discount_rate_);
  }
  return discount_amount_from_rate;
}

double BillTotal::CalculateTotalDiscountAmount() const {
  if (total_discount_amount_ == -1) {
    total_discount_amount_ =
        CalculateDiscountAmountFromRate() + discount_amount_in_order_;
  }
  return total_discount_amount_;
}
double BillTotal::GetDiscountRate() const noexcept { return discount_rate_; }

double BillTotal::GetDiscountAmountInOrder() const noexcept {
  return discount_amount_in_order_;
}
double BillTotal::GetTaxRate() const noexcept { return tax_rate_; }
double BillTotal::GetSubTotal() const noexcept { return sub_total_; }

void BillTotal::SetSubTotal(int quantity) {
  sub_total_ = Contract(quantity, std::greater{}, 0) *
               Contract(price_per_unit_, std::greater{}, 0);
}

double BillTotal::CalculateTaxAmount() const {
  if (tax_amount_ == -1) {
    tax_amount_ = RoundWithThousand(CalculateTotalDiscountAmount() * tax_rate_);
  }
  return tax_amount_;
}

double BillTotal::CalculateTotalPayable() const {
  if (total_payable_ == -1) {
    total_payable_ =
        sub_total_ - CalculateTotalDiscountAmount() + CalculateTaxAmount();
  }
  return total_payable_;
}
