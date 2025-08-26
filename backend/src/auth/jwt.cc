//
// Created by rog on 02/03/2025.
//

#include "jwt.h"
Jwt::Jwt(std::string secret, std::string issuer)
    : secret_(std::move(secret)),
      issuer_(std::move(issuer)),
      verifier_(
          jwt::verify().allow_algorithm(jwt::algorithm::hs512{secret_}).with_issuer(issuer_)) {}

oatpp::String Jwt::CreateToken(const std::shared_ptr<Payload>& payload) const {
    return jwt::create()
        .set_issuer(issuer_)
        .set_type("JWS")
        .set_payload_claim("user_id", jwt::claim(payload->user_id))
        .sign(jwt::algorithm::hs512{secret_});
}

std::shared_ptr<Jwt::Payload> Jwt::ReadAndVerifyToken(const oatpp::String& token) const {
    const auto decode = jwt::decode(token);
    verifier_.verify(decode);
    auto payload = std::make_shared<Payload>();
    payload->user_id = decode.get_payload_claim("user_id").as_string();
    return payload;
}