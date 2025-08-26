//
// Created by ROG on 22/06/2025.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include <occi.h>

namespace global {
extern oracle::occi::Environment* env;
extern oracle::occi::Connection* conn;
}  // namespace global

#endif  // GLOBAL_H
