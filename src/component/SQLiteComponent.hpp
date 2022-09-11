#ifndef FARM_FELLOWS_SQLITE_COMPONENT_HPP
#define FARM_FELLOWS_SQLITE_COMPONENT_HPP

//#include "../db/sqlite/UserDb.hpp"

//class SQLiteComponent {
//private:
//  typedef std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>> ConnectionProvider;
//public:
    
  /**
   * Create database connection provider component
   */
  //OATPP_CREATE_COMPONENT(ConnectionProvider, sqliteConnectionProvider)([] {

    /* Create database-specific ConnectionProvider */
    //auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(SQLITE_DATABASE_FILE);

    /* Create database-specific ConnectionPool */
    //return oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
    //                                                   10 /* max-connections */,
    //                                                   std::chrono::seconds(5) /* connection TTL */);

  //}());

  /**
   * Create database client
   */
  //OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {

    /* Get database ConnectionProvider component */
    //OATPP_COMPONENT(ConnectionProvider, sqliteConnectionProvider);

    /* Create database-specific Executor */
    //auto executor = std::make_shared<oatpp::sqlite::Executor>(sqliteConnectionProvider);

    /* Create MyClient database client */
    //return std::make_shared<UserDb>(executor);

  //}());

//};

#endif //FARM_FELLOWS_SQLITE_COMPONENT_HPP