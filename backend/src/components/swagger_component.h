//
// Created by rog on 02/03/2025.
//

#ifndef SWAGGER_COMPONENT_H
#define SWAGGER_COMPONENT_H

#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>
#include <oatpp/macro/component.hpp>

class SwaggerComponent {
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swagger_document_info)
    ([] {
        oatpp::swagger::DocumentInfo::Builder builder;

        builder.setTitle("bac")
            .setDescription("bac")
            .setVersion("1.0")
            .setContactName("bac")
            .setContactUrl("https://web.facebook.com/hoang.bac.902604/")
            .setLicenseName("Apache License, Version 2.0")
            .setLicenseUrl("https://www.apache.org/licenses/LICENSE-2.0")
            .addServer("http://localhost:8000", "server on localhost");
        return builder.build();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swagger_resource)
    ([] {
        return oatpp::swagger::Resources::loadResources(
            "/usr/local/include/oatpp-1.4.0/bin/oatpp-swagger/res");
    }());
};

#endif  // SWAGGER_COMPONENT_H
