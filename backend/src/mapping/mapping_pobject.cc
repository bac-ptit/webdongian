//
// Created by ROG on 22/06/2025.
//

#include "./mapping_pobject.h"

#include <iostream>

#include "entity/client/client.h"
#include "entity/service_booking/booking.h"
#include "entity/service_booking/service.h"

static void RegisterReadSQLAndWriteSQL(const oracle::occi::Environment* env,
                                       const std::string& schema_and_type,
                                       void* (*read_func)(void*),
                                       void (*write_func)(void*, void*)) {
  env->getMap()->put(schema_and_type, read_func, write_func);
  std::cerr << "Registered: " << schema_and_type << std::endl;
}

using bac_lib::tool::StrCat;

void MappingSchema(const oracle::occi::Environment* env) {
  // Register the mapping schema for PObject
  RegisterReadSQLAndWriteSQL(env,
                             StrCat(Booking::kSchema, ".", Booking::kTypename),
                             &Booking::ReadSQL, &Booking::WriteSQL);
  RegisterReadSQLAndWriteSQL(

      env, StrCat(Client::kSchema, ".", Client::kTypename), &Client::ReadSQL,
      &Client::WriteSQL);
  RegisterReadSQLAndWriteSQL(env, StrCat(Order::kSchema, ".", Order::kTypename),
                             &Order::ReadSQL, &Order::WriteSQL);
  RegisterReadSQLAndWriteSQL(env,
                             StrCat(Service::kSchema, ".", Service::kTypename),
                             &Service::ReadSQL, &Service::WriteSQL);
  RegisterReadSQLAndWriteSQL(env,
                             StrCat(Server::kSchema, ".", Server::kTypename),
                             &Server::ReadSQL, &Server::WriteSQL);
  RegisterReadSQLAndWriteSQL(
      env, StrCat(Transaction::kSchema, ".", Transaction::kTypename),
      &Transaction::ReadSQL, &Transaction::WriteSQL);
}