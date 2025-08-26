cmake_minimum_required(VERSION 3.20)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(include/bac_lib)


add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        src/dto/DTOs.hpp
        src/error_handler.cc
        src/error_handler.h
        src/dto/error_dto.h
        src/auth/jwt.h
        src/auth/jwt.cc
        src/auth/auth_handler.h
        src/auth/auth_handler.cc
        src/interceptor/auth_interceptor.h
        src/interceptor/auth_interceptor.cc
        src/components/swagger_component.h
        src/entity/client/client.cc
        src/entity/client/client.h
        src/repo/client_repo.cc
        src/repo/client_repo.h
        src/service/client_service.cc
        src/service/client_service.h
        src/service/auth_service.cc
        src/service/auth_service.h
        src/controller/auth_controller.cc
        src/controller/auth_controller.h
        src/controller/client_controller.cc
        src/controller/client_controller.h
        src/entity/service_booking/booking.cc
        src/entity/service_booking/booking.h
        src/entity/service_booking/service.cc
        src/entity/service_booking/service.h
        src/repo/booking_repo.cc
        src/repo/booking_repo.h
        src/repo/service_repo.cc
        src/repo/service_repo.h
        src/service/booking_service.cc
        src/service/booking_service.h
        src/controller/booking_controller.cc
        src/controller/booking_controller.h
        src/components/database_component.h
        src/global/global.h
        src/global/global.cc
        src/mapping/mapping_pobject.h
        src/mapping/mapping_pobject.cc
        src/components/service_component.h
        src/auth/cookie_handler.cc
        src/auth/cookie_handler.h
        src/config/frontend.h
        src/interceptor/response_intercepter.cc
        src/interceptor/cor_response_intercepter.h
        src/entity/server/server.cc
        src/entity/server/server.h
        src/repo/server_repo.cc
        src/repo/server_repo.h
        src/dto/server_dto.h
        src/entity/transaction/transaction.cc
        src/entity/transaction/transaction.h
        src/repo/transaction_repo.cc
        src/repo/transaction_repo.h
        src/dto/transaction_dto.h
        src/entity/order/order.cc
        src/entity/order/order.h
        src/modul/bill_total.cc
        src/modul/bill_total.h
        src/repo/order_repo.cc
        src/repo/order_repo.h
        src/controller/order_controller.cc
        src/controller/order_controller.h
        src/service/order_service.cc
        src/service/order_service.h
        src/dto/order_dto.h
)

## link libs


find_package(oatpp 1.4.0 REQUIRED)
find_package(oatpp-swagger 1.4.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
        bac_lib

)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp
        src/config/database.h
        src/dto/client_dto.h
        src/dto/booking_service_dto.h)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        test/MyControllerTest.cpp
        test/MyControllerTest.hpp
)


target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 23
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
