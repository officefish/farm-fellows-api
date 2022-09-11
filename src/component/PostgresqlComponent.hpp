#ifndef FARM_FELLOWS_POSTGRESQL_COMPONENT_HPP
#define FARM_FELLOWS_POSTGRESQL_COMPONENT_HPP

#include "db/postgresql/member/MemberDb.hpp"
#include "db/postgresql/auth/AuthDatetimeDb.hpp"
//#include "db/StoryDb.hpp"

class PostgresqlComponent {
private:
    typedef std::shared_ptr<oatpp::postgresql::Executor> Executor;
    typedef std::shared_ptr<oatpp::postgresql::ConnectionPool> ConnectionPool;
    typedef farmfellows::sql::postgresql::MemberDb MemberDb;
    typedef farmfellows::sql::postgresql::AuthDatetimeDb AuthDatetimeDb;

public:

  OATPP_CREATE_COMPONENT(ConnectionPool, connectionPool)([] {
    oatpp::String connStr = POSTGRESQL_DATABASE_LIBPQ_CONNECTION;

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(connStr);

    /* Create database-specific ConnectionPool */
    return oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                           10 /* max-connections */,
                                                           std::chrono::seconds(5) /* connection TTL */);
  }());

  OATPP_CREATE_COMPONENT(Executor, postgresqlExecutor)([] {

    /* get connection pool component */
    OATPP_COMPONENT(ConnectionPool, connectionPool);

    /* Create database-specific Executor */
    return std::make_shared<oatpp::postgresql::Executor>(connectionPool);

  }());

  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<MemberDb>, memberDb)([] {

    /* get DB executor component */
    OATPP_COMPONENT(Executor, postgresqlExecutor);

    /* Create MyClient database client */
    return std::make_shared<MemberDb>(postgresqlExecutor);

  }());

  /**
   * Create auth satabase database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<AuthDatetimeDb>, authDatetimeDb)([] {

    /* get DB executor component */
    OATPP_COMPONENT(Executor, postgresqlExecutor);

    /* Create MyClient database client */
    return std::make_shared<AuthDatetimeDb>(postgresqlExecutor);

  }());

  /**
   * Create database client
   */
  //OATPP_CREATE_COMPONENT(std::shared_ptr<StoryDb>, storyDb)([] {

    /* get DB executor component */
    //OATPP_COMPONENT(Executor, postgresqlExecutor);

    /* Create MyClient database client */
    //return std::make_shared<StoryDb>(postgresqlExecutor);

  //}());

};

#endif //FARM_FELLOWS_POSTGRESQL_COMPONENT_HPP