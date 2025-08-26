//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_ENTITY_BOOKING_SERVICE_H
#define BACKEND_ENTITY_BOOKING_SERVICE_H
#include "../../../include/bac_lib/orcl/base_pobject.h"
#include "config/database.h"
#include "service.h"

class Booking final : public bac_lib::orcl::BasePObject<Booking> {
 public:
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  static constexpr auto kSchema = config::database::kSchema;
  static constexpr auto kTableName = "TABLE_BOOKING";
  static constexpr auto kTypename = "TYPE_BOOKING";
  static constexpr auto kPrimaryKey = "id_";  // id is auto-incremented

  explicit Booking(std::string service_name);

  void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

 private:

  friend class BookingRepo;
  friend class BookingDto;

  int id_{};
  std::string name_;
  std::vector<std::unique_ptr<Service>> services_;
};

#endif  // BACKEND_ENTITY_BOOKING_SERVICE_H
