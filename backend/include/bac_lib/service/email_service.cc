//
// Created by rog on 24/03/2025.
//

#include "email_service.h"

using namespace mailio;

namespace bac_lib::service {
EmailService::EmailService(const std::string& username, const std::string& password,
                           const std::string& mail_name)
    : from_email_(string_t{mail_name, codec::CHARSET_ASCII, codec::codec_t::UTF8}, username) {
    conn_.authenticate(username, password, smtps::auth_method_t::START_TLS);
}

void EmailService::SendEmail(const std::string& to_email, const std::string& subject,
                             const std::string& content) {
    message msg;
    msg.from(from_email_);
    msg.add_recipient(mail_address{"", to_email});
    msg.subject(subject);
    msg.content(content);
    conn_.submit(msg);
}

void EmailService::SetMailName(const std::string& mail_name) {
    from_email_.name = {mail_name, codec::CHARSET_ASCII, codec::codec_t::UTF8};
}
}  // namespace bac_lib::service