#ifndef FARM_FELLOWS_SQL_POSTGRESQL_AUTH_DATETIME_DB_HPP
#define FARM_FELLOWS_SQL_POSTGRESQL_AUTH_DATETIME_DB_HPP

#include "oatpp-postgresql/orm.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

namespace farmfellows::sql::postgresql {

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen
  
/**
* AuthDatetimeDb client definitions.
*/
class AuthDatetimeDb : public oatpp::orm::DbClient {

public:

  AuthDatetimeDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
  : oatpp::orm::DbClient(executor)
  {
    oatpp::orm::SchemaMigration migration(executor, "auth_datetime_service");
    migration.addFile(1 /* start from version 1 */, POSTGRESQL_DATABASE_MIGRATIONS "/AuthService/001_auth_datetime_init.sql");

    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = migration.getSchemaVersion();
    OATPP_LOGD("Postgresql AuthDatetimeDb", "Migration - OK. Version=%d.", version);
  }

  QUERY (createAuthDatetime,
    "INSERT INTO auth_datetime (id, memberId, signupDatetime) " 
    "VALUES (uuid_generate_v4()"
    ",       :memberId"
    ",       now()) "
    "RETURNING id;",
    PREPARE(true), // prepared statement!
    PARAM(oatpp::String, memberId))

  QUERY(updateSigninDatetime,
    "UPDATE auth_datetime "
    "SET "
    " signinDatetime = now() "
    "WHERE "
    " memberId=:memberId "
    "RETURNING signinDatetime;",
    PREPARE(true), // prepared statement!
    PARAM(oatpp::String, memberId))

  QUERY(updateLastVisitDatetime,
    "UPDATE auth_datetime "
    "SET "
    " lastVisitDatetime = now() "
    "WHERE "
    " memberId=:memberId "
    "RETURNING lastVisitDatetime;",
    PREPARE(true), // prepared statement!
    PARAM(oatpp::String, memberId))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}

#endif // FARM_FELLOWS_SQL_POSTGRESQL_AUTH_DATETIME_DB_HPP   