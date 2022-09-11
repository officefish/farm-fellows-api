#ifndef FARM_FELLOWS_CONNECTION_COMPONENT_HPP
#define FARM_FELLOWS_CONNECTION_COMPONENT_HPP

#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/interceptor/AllowCorsGlobal.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "./error/ErrorHandler.hpp"
#include "interceptor/AuthInterceptor.hpp"

/**
 *  Class which creates very basic components for HTTP connection
 *  HOST, PORT constants declared in CMakeLists.txt
 */
class ConnectionComponent {
public:

    /**
    *  Create ConnectionProvider component which listens on the port
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({SERVER_HOST, SERVER_PORT, oatpp::network::Address::IP_4});
    }());
  
    /**
    *  Create Router component
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
        *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());
  
    /**
        *  Create ConnectionHandler component which uses Router component to route requests
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        
        OATPP_COMPONENT(std::shared_ptr<JWT>, jwt); // get JWT component
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper); // get ObjectMapper component

        auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
        connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));

        connectionHandler->addRequestInterceptor(std::make_shared<oatpp::web::server::interceptor::AllowOptionsGlobal>());
        connectionHandler->addRequestInterceptor(std::make_shared<AuthInterceptor>(jwt));

        connectionHandler->addResponseInterceptor(std::make_shared<oatpp::web::server::interceptor::AllowCorsGlobal>());
        
        return connectionHandler;
    }());

};

#endif /*FARM_FELLOWS_CONNECTION_COMPONENT_HPP */