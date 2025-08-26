//
// Created by rog on 24/03/2025.
//

#ifndef BAC_LIC_SERVICE_EMAIL_SERVICE_H
#define BAC_LIC_SERVICE_EMAIL_SERVICE_H

#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

namespace bac_lib::service {

class EmailService {
public:
    /**
     * \brief Constructs an EmailService object.
     *
     * \param username The email address used for authentication.
     * \param password The application-specific password for authentication.
     * \param mail_name display name of the email address.
     */
    EmailService(const std::string& username, const std::string& password,
                 const std::string& mail_name = {});

    void SendEmail(const std::string& to_email, const std::string& subject,
                   const std::string& content);

    void SetMailName(const std::string& mail_name);

private:
    mailio::smtps conn_{"smtp.gmail.com", 587};

    mailio::mail_address from_email_;
};

}  // namespace bac_lib::service

#endif  // BAC_LIC_SERVICE_EMAIL_SERVICE_H
