cmake_minimum_required(VERSION 3.28)
project(bac_lib)

if (DEFINED ENV{ORACLE_HOME})
    set(ORACLE_HOME $ENV{ORACLE_HOME})
else ()
    message(FATAL_ERROR "ORACLE_HOME environment variable is not set")
endif ()

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE bac_source
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

if (NOT EXISTS "${ORACLE_HOME}/sdk/include")
    message(FATAL_ERROR "Oracle SDK include directory does not exist: ${ORACLE_HOME}/sdk/include")
endif ()

add_library(bac_lib STATIC ${bac_source})

target_include_directories(bac_lib PUBLIC "${ORACLE_HOME}/sdk/include")

find_package(mailio REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem date_time regex url locale)
find_package(ICU REQUIRED COMPONENTS uc i18n)
find_package(jwt-cpp REQUIRED)
find_package(absl REQUIRED)
find_package(fmt REQUIRED)


target_link_directories(bac_lib PUBLIC ${ORACLE_HOME})
target_link_libraries(bac_lib PUBLIC
        Boost::system Boost::filesystem Boost::date_time Boost::regex Boost::url Boost::locale
        ICU::uc ICU::i18n #international components for unicode
        occi clntsh ociei nnz #Oracle C++ Call Interface
        jwt-cpp::jwt-cpp
        mailio::mailio
        absl::strings
        fmt::fmt
)
