#ifndef FARM_FELLOWS_APP_COMPONENT_HPP
#define FARM_FELLOWS_APP_COMPONENT_HPP

#include "./ConnectionComponent.hpp"
#include "./SwaggerComponent.hpp"
//#include "./SQLiteComponent.hpp"
#include "./PostgresqlComponent.hpp"
#include "./JwtComponent.hpp"
#include "./UuidComponent.hpp"

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
public:

    /** 
     * SQLite database component
    */
    //SQLiteComponent sqlite;

    /*
    * Uuid generator component;
    */
    UuidComponent uuidComponent;

    /**
     * Postgresql database component
     */
    PostgresqlComponent postgresql;

    /**
    *  Swagger component
    */
    SwaggerComponent swagger;

    /*
    * JWT Component
    */
    JwtComponent jwt;

    /*
    *   Connection component contains: ConnectionProvider, HTTPRouter and HttpConnectionHandler
    */
    ConnectionComponent connection;    

};

#endif /* FARM_FELLOWS_APP_COMPONENT_HPP */