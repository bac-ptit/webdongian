//
// Created by rog on 02/03/2025.
//

#ifndef JWT_H
#define JWT_H
#include <jwt-cpp/jwt.h>

#include <oatpp/web/server/handler/AuthorizationHandler.hpp>
class Jwt {
public:
    struct Payload final : oatpp::web::server::handler::AuthorizationObject {
        Payload() = default;
        explicit Payload(oatpp::String user_id) : user_id(std::move(user_id)) {}

        oatpp::String user_id;
        std::string role;
    };

    Jwt(std::string secret, std::string issuer);

    oatpp::String CreateToken(const std::shared_ptr<Payload>& payload) const;

    std::shared_ptr<Payload> ReadAndVerifyToken(const oatpp::String& token) const;

private:
    std::string secret_;
    std::string issuer_;
    jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> verifier_;
};

#endif  // JWT_H
