//
// Created by ROG on 22/06/2025.
//

#include <occi.h>

#include "mapping/mapping_pobject.h"

using namespace oracle::occi;

namespace global {
auto env = [] {
  const auto env = Environment::createEnvironment(
      static_cast<Environment::Mode>(Environment::THREADED_MUTEXED | Environment::OBJECT));
#if (OCCI_MAJOR_VERSION > 9)
  env->setCacheSortedFlush(true);  // benefit of performance, if available
#endif
  MappingSchema(env);
  return env;
}();

auto conn = env->createConnection("system", "0", "localhost:1521/ORACLE");
}  // namespace global