# Details

Date : 2025-06-26 17:00:16

Directory d:\\Programming\\web\\tuongtac\\backend

Total : 108 files,  3151 codes, 693 comments, 955 blanks, all 4799 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [.dockerignore](/.dockerignore) | Ignore | 1 | 0 | 0 | 1 |
| [CMakeLists.txt](/CMakeLists.txt) | CMake | 112 | 0 | 20 | 132 |
| [Dockerfile](/Dockerfile) | Docker | 9 | 0 | 8 | 17 |
| [README.md](/README.md) | Markdown | 37 | 0 | 16 | 53 |
| [azure-pipelines.yml](/azure-pipelines.yml) | YAML | 88 | 4 | 2 | 94 |
| [data\_sql/booking\_element.csv](/data_sql/booking_element.csv) | CSV | 11 | 0 | 1 | 12 |
| [data\_sql/booking\_service.csv](/data_sql/booking_service.csv) | CSV | 4 | 0 | 1 | 5 |
| [data\_sql/import\_booking\_service.log](/data_sql/import_booking_service.log) | Log | 41 | 0 | 17 | 58 |
| [data\_sql/import\_data.log](/data_sql/import_data.log) | Log | 42 | 0 | 17 | 59 |
| [data\_sql/load.log](/data_sql/load.log) | Log | 43 | 0 | 17 | 60 |
| [data\_sql/server.csv](/data_sql/server.csv) | CSV | 16 | 0 | 1 | 17 |
| [data\_sql/server.log](/data_sql/server.log) | Log | 46 | 0 | 16 | 62 |
| [import\_booking\_service.log](/import_booking_service.log) | Log | 6 | 0 | 4 | 10 |
| [include/bac\_lib/CMakeLists.txt](/include/bac_lib/CMakeLists.txt) | CMake | 33 | 0 | 9 | 42 |
| [include/bac\_lib/README.md](/include/bac_lib/README.md) | Markdown | 0 | 0 | 1 | 1 |
| [include/bac\_lib/orcl/base\_pobject.h](/include/bac_lib/orcl/base_pobject.h) | C++ | 67 | 85 | 19 | 171 |
| [include/bac\_lib/orcl/oracle\_query.h](/include/bac_lib/orcl/oracle_query.h) | C++ | 219 | 147 | 25 | 391 |
| [include/bac\_lib/service/email\_service.cc](/include/bac_lib/service/email_service.cc) | C++ | 21 | 3 | 5 | 29 |
| [include/bac\_lib/service/email\_service.h](/include/bac_lib/service/email_service.h) | C++ | 18 | 10 | 11 | 39 |
| [include/bac\_lib/tool/finance.cc](/include/bac_lib/tool/finance.cc) | C++ | 8 | 3 | 4 | 15 |
| [include/bac\_lib/tool/finance.h](/include/bac_lib/tool/finance.h) | C++ | 7 | 9 | 6 | 22 |
| [include/bac\_lib/tool/tool.cc](/include/bac_lib/tool/tool.cc) | C++ | 71 | 1 | 14 | 86 |
| [include/bac\_lib/tool/tool.h](/include/bac_lib/tool/tool.h) | C++ | 67 | 46 | 15 | 128 |
| [include/bac\_lib/type/date.cc](/include/bac_lib/type/date.cc) | C++ | 127 | 3 | 38 | 168 |
| [include/bac\_lib/type/date.h](/include/bac_lib/type/date.h) | C++ | 76 | 8 | 27 | 111 |
| [main.sql](/main.sql) | PL/SQL | 115 | 0 | 0 | 115 |
| [src/App.cpp](/src/App.cpp) | C++ | 44 | 16 | 16 | 76 |
| [src/AppComponent.hpp](/src/AppComponent.hpp) | C++ | 51 | 18 | 19 | 88 |
| [src/auth/auth\_handler.cc](/src/auth/auth_handler.cc) | C++ | 7 | 3 | 2 | 12 |
| [src/auth/auth\_handler.h](/src/auth/auth_handler.h) | C++ | 12 | 3 | 8 | 23 |
| [src/auth/cookie\_handler.cc](/src/auth/cookie_handler.cc) | C++ | 38 | 3 | 10 | 51 |
| [src/auth/cookie\_handler.h](/src/auth/cookie_handler.h) | C++ | 17 | 3 | 8 | 28 |
| [src/auth/jwt.cc](/src/auth/jwt.cc) | C++ | 20 | 3 | 3 | 26 |
| [src/auth/jwt.h](/src/auth/jwt.h) | C++ | 21 | 3 | 9 | 33 |
| [src/components/database\_component.h](/src/components/database_component.h) | C++ | 25 | 3 | 9 | 37 |
| [src/components/service\_component.h](/src/components/service_component.h) | C++ | 15 | 3 | 7 | 25 |
| [src/components/swagger\_component.h](/src/components/swagger_component.h) | C++ | 26 | 3 | 7 | 36 |
| [src/config/database.h](/src/config/database.h) | C++ | 8 | 3 | 5 | 16 |
| [src/config/frontend.h](/src/config/frontend.h) | C++ | 6 | 3 | 4 | 13 |
| [src/controller/MyController.cpp](/src/controller/MyController.cpp) | C++ | 1 | 1 | 1 | 3 |
| [src/controller/MyController.hpp](/src/controller/MyController.hpp) | C++ | 22 | 8 | 10 | 40 |
| [src/controller/auth\_controller.cc](/src/controller/auth_controller.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/controller/auth\_controller.h](/src/controller/auth_controller.h) | C++ | 38 | 8 | 13 | 59 |
| [src/controller/booking\_controller.cc](/src/controller/booking_controller.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/controller/booking\_controller.h](/src/controller/booking_controller.h) | C++ | 22 | 7 | 10 | 39 |
| [src/controller/client\_controller.cc](/src/controller/client_controller.cc) | C++ | 1 | 3 | 3 | 7 |
| [src/controller/client\_controller.h](/src/controller/client_controller.h) | C++ | 22 | 7 | 10 | 39 |
| [src/controller/order\_controller.cc](/src/controller/order_controller.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/controller/order\_controller.h](/src/controller/order_controller.h) | C++ | 17 | 11 | 9 | 37 |
| [src/dto/DTOs.hpp](/src/dto/DTOs.hpp) | C++ | 12 | 4 | 9 | 25 |
| [src/dto/auth\_dto.h](/src/dto/auth_dto.h) | C++ | 18 | 0 | 8 | 26 |
| [src/dto/booking\_service\_dto.h](/src/dto/booking_service_dto.h) | C++ | 48 | 3 | 16 | 67 |
| [src/dto/client\_dto.h](/src/dto/client_dto.h) | C++ | 58 | 3 | 16 | 77 |
| [src/dto/error\_dto.h](/src/dto/error_dto.h) | C++ | 15 | 7 | 8 | 30 |
| [src/dto/order\_dto.h](/src/dto/order_dto.h) | C++ | 68 | 7 | 18 | 93 |
| [src/dto/server\_dto.h](/src/dto/server_dto.h) | C++ | 43 | 0 | 10 | 53 |
| [src/dto/transaction\_dto.h](/src/dto/transaction_dto.h) | C++ | 46 | 7 | 15 | 68 |
| [src/entity/client/client.cc](/src/entity/client/client.cc) | C++ | 62 | 3 | 11 | 76 |
| [src/entity/client/client.h](/src/entity/client/client.h) | C++ | 37 | 4 | 14 | 55 |
| [src/entity/order/order.cc](/src/entity/order/order.cc) | C++ | 43 | 3 | 10 | 56 |
| [src/entity/order/order.h](/src/entity/order/order.h) | C++ | 40 | 7 | 13 | 60 |
| [src/entity/server/server.cc](/src/entity/server/server.cc) | C++ | 59 | 3 | 9 | 71 |
| [src/entity/server/server.h](/src/entity/server/server.h) | C++ | 42 | 3 | 14 | 59 |
| [src/entity/service\_booking/booking.cc](/src/entity/service_booking/booking.cc) | C++ | 15 | 3 | 7 | 25 |
| [src/entity/service\_booking/booking.h](/src/entity/service_booking/booking.h) | C++ | 25 | 3 | 10 | 38 |
| [src/entity/service\_booking/service.cc](/src/entity/service_booking/service.cc) | C++ | 17 | 3 | 7 | 27 |
| [src/entity/service\_booking/service.h](/src/entity/service_booking/service.h) | C++ | 29 | 3 | 10 | 42 |
| [src/entity/transaction/transaction.cc](/src/entity/transaction/transaction.cc) | C++ | 41 | 3 | 4 | 48 |
| [src/entity/transaction/transaction.h](/src/entity/transaction/transaction.h) | C++ | 55 | 3 | 16 | 74 |
| [src/error\_handler.cc](/src/error_handler.cc) | C++ | 26 | 8 | 9 | 43 |
| [src/error\_handler.h](/src/error_handler.h) | C++ | 17 | 3 | 7 | 27 |
| [src/global/global.cc](/src/global/global.cc) | C++ | 15 | 3 | 5 | 23 |
| [src/global/global.h](/src/global/global.h) | C++ | 8 | 3 | 5 | 16 |
| [src/interceptor/auth\_interceptor.cc](/src/interceptor/auth_interceptor.cc) | C++ | 28 | 5 | 5 | 38 |
| [src/interceptor/auth\_interceptor.h](/src/interceptor/auth_interceptor.h) | C++ | 17 | 4 | 6 | 27 |
| [src/interceptor/cor\_response\_intercepter.h](/src/interceptor/cor_response_intercepter.h) | C++ | 16 | 3 | 7 | 26 |
| [src/interceptor/response\_intercepter.cc](/src/interceptor/response_intercepter.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/mapping/mapping\_pobject.cc](/src/mapping/mapping_pobject.cc) | C++ | 30 | 4 | 5 | 39 |
| [src/mapping/mapping\_pobject.h](/src/mapping/mapping_pobject.h) | C++ | 5 | 3 | 5 | 13 |
| [src/modul/bill\_total.cc](/src/modul/bill_total.cc) | C++ | 66 | 3 | 15 | 84 |
| [src/modul/bill\_total.h](/src/modul/bill_total.h) | C++ | 33 | 13 | 15 | 61 |
| [src/repo/booking\_repo.cc](/src/repo/booking_repo.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/repo/booking\_repo.h](/src/repo/booking_repo.h) | C++ | 21 | 3 | 7 | 31 |
| [src/repo/client\_repo.cc](/src/repo/client_repo.cc) | C++ | 38 | 3 | 6 | 47 |
| [src/repo/client\_repo.h](/src/repo/client_repo.h) | C++ | 18 | 3 | 9 | 30 |
| [src/repo/order\_repo.cc](/src/repo/order_repo.cc) | C++ | 26 | 3 | 3 | 32 |
| [src/repo/order\_repo.h](/src/repo/order_repo.h) | C++ | 13 | 3 | 6 | 22 |
| [src/repo/server\_repo.cc](/src/repo/server_repo.cc) | C++ | 7 | 3 | 1 | 11 |
| [src/repo/server\_repo.h](/src/repo/server_repo.h) | C++ | 11 | 3 | 5 | 19 |
| [src/repo/service\_repo.cc](/src/repo/service_repo.cc) | C++ | 6 | 3 | 1 | 10 |
| [src/repo/service\_repo.h](/src/repo/service_repo.h) | C++ | 15 | 3 | 6 | 24 |
| [src/repo/transaction\_repo.cc](/src/repo/transaction_repo.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/repo/transaction\_repo.h](/src/repo/transaction_repo.h) | C++ | 18 | 3 | 5 | 26 |
| [src/service/auth\_service.cc](/src/service/auth_service.cc) | C++ | 26 | 16 | 9 | 51 |
| [src/service/auth\_service.h](/src/service/auth_service.h) | C++ | 22 | 8 | 8 | 38 |
| [src/service/booking\_service.cc](/src/service/booking_service.cc) | C++ | 11 | 3 | 4 | 18 |
| [src/service/booking\_service.h](/src/service/booking_service.h) | C++ | 14 | 3 | 6 | 23 |
| [src/service/client\_service.cc](/src/service/client_service.cc) | C++ | 9 | 3 | 3 | 15 |
| [src/service/client\_service.h](/src/service/client_service.h) | C++ | 16 | 3 | 5 | 24 |
| [src/service/order\_service.cc](/src/service/order_service.cc) | C++ | 1 | 3 | 2 | 6 |
| [src/service/order\_service.h](/src/service/order_service.h) | C++ | 13 | 3 | 5 | 21 |
| [temp.sql](/temp.sql) | PL/SQL | 0 | 0 | 1 | 1 |
| [test/MyControllerTest.cpp](/test/MyControllerTest.cpp) | C++ | 27 | 14 | 21 | 62 |
| [test/MyControllerTest.hpp](/test/MyControllerTest.hpp) | C++ | 9 | 0 | 6 | 15 |
| [test/app/MyApiTestClient.hpp](/test/app/MyApiTestClient.hpp) | C++ | 11 | 7 | 11 | 29 |
| [test/app/TestComponent.hpp](/test/app/TestComponent.hpp) | C++ | 37 | 21 | 19 | 77 |
| [test/tests.cpp](/test/tests.cpp) | C++ | 15 | 2 | 11 | 28 |
| [utility/install-oatpp-modules.sh](/utility/install-oatpp-modules.sh) | Shell Script | 29 | 4 | 17 | 50 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)