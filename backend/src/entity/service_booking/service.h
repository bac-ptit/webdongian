//
// Created by ROG on 22/06/2025.
//

#ifndef BACKEND_ENTITY_SERVICE_BOOKING_SERVICE_H
#define BACKEND_ENTITY_SERVICE_BOOKING_SERVICE_H
#include "../../../include/bac_lib/orcl/base_pobject.h"
#include "config/database.h"
#include "entity/server/server.h"

class ServiceRepo;
class ServiceDto;
class Service : public bac_lib::orcl::BasePObject<Service> {
 public:
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  static constexpr auto kSchema = config::database::kSchema;
  static constexpr auto kTableName = "TABLE_SERVICE";
  static constexpr auto kTypename = "TYPE_SERVICE";
  static constexpr auto kPrimaryKey = "id_";  // id is auto-incremented

  Service(std::string name,
                 int booking_id);

  void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  int GetId() const noexcept;


 private:

  friend ServiceDto;
  friend ServiceRepo;

  int id_{};
  std::string name_;
  int booking_id_;
  std::vector<std::unique_ptr<Server>> servers_;
};

#endif  // BACKEND_ENTITY_SERVICE_BOOKING_SERVICE_H
