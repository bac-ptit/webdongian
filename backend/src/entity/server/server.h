//
// Created by ROG on 24/06/2025.
//

#ifndef BACKEND_ENTITY_SERVER_H
#define BACKEND_ENTITY_SERVER_H
#include "../../../include/bac_lib/orcl/base_pobject.h"
#include "config/database.h"

class ServerResponseDto;
class Server final : public bac_lib::orcl::BasePObject<Server> {
 public:
  using BasePObject::BasePObject;
  using BasePObject::ReadSQL;
  using BasePObject::WriteSQL;

  enum class State { kActive, kInactive, kMaintenance, kDeath };

  static constexpr auto kSchema = config::database::kSchema;
  static constexpr auto kTableName = "TABLE_SERVER";
  static constexpr auto kTypename = "TYPE_SERVER";
  static constexpr auto kPrimaryKey = "id_";  // id is auto-incremented


  Server(int id, std::string name, std::string host,
         bac_lib::type::Date created_at, int number_of_day_in_effect,
         int quantity, double price_for_interaction, State state,
         int service_id);

  Server(int id, std::string name, std::string host,
         const bac_lib::type::Date& created_at, int number_of_day_in_effect,
         int min_quantity, int max_quantity, double price_for_interaction,
         State state, int service_id);

  [[nodiscard]] bool HasMaximumQuantity() const noexcept;

  bool IsSatisfiedQuantity(int quantity) const noexcept;

  void readSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;
  void writeSQL(oracle::occi::AnyData& streamOCCI_) noexcept override;

  [[nodiscard]] int GetId() const noexcept;

  [[nodiscard]] double GetPricePerUnit() const noexcept;

 private:
  friend ServerResponseDto;

  int id_{};
  std::string name_;
  std::string host_;
  bac_lib::type::Date created_at_;
  int number_of_day_in_effect_;
  int min_quantity_;
  int max_quantity_ = std::numeric_limits<int>::max();  // default is no limit
  double price_for_unit_;
  State state_{State::kMaintenance};
  int service_id_;
};

#endif  // BACKEND_ENTITY_SERVER_H
