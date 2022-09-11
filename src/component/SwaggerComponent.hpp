#ifndef FARM_FELLOWS_SWAGGER_COMPONENT_HPP
#define FARM_FELLOWS_SWAGGER_COMPONENT_HPP

#include <sstream>

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 *  Swagger ui is served at
 *  http://host:port/swagger/ui
 */
class SwaggerComponent {
public:
  
  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
    
    oatpp::swagger::DocumentInfo::Builder builder;

    std::stringstream server_url;
    server_url << "http://" << SERVER_HOST << ":" << SERVER_PORT;
    
    builder
    .setTitle("User entity service")
    .setDescription("CRUD API Farm Fellows project with swagger docs")
    .setVersion("0.0.1")
    .setContactName("Sergey Inozemcev")
    .setContactUrl("https://farm-fellows.io/contacts")
    
    .setLicenseName("Apache License, Version 2.0")
    .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")
    
    .addServer(server_url.str(), "server on localhost");
    
    return builder.build();
    
  }());
  
  
  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());
  
};

#endif /* FARM_FELLOWS_SWAGGER_COMPONENT_HPP */