#ifndef FARM_FELLOWS_SQL_POSTGRESQL_MEMBER_DB_HPP
#define FARM_FELLOWS_SQL_POSTGRESQL_MEMBER_DB_HPP

#include "oatpp-postgresql/orm.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "dto/member/MemberDto.hpp"

namespace farmfellows::sql::postgresql {

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen
   
/**
 * MemberDb client definitions.
 */
class MemberDb : public oatpp::orm::DbClient {

public:

  MemberDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor, "auth_service");
    migration.addFile(1 /* start from version 1 */, POSTGRESQL_DATABASE_MIGRATIONS "/AuthService/001_members_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = migration.getSchemaVersion();
    OATPP_LOGD("Postgresql MemberDb", "Migration - OK. Version=%d.", version);
  }

  QUERY(createMember,
      "INSERT INTO members (id, memberName, email, passwordHash, memberRole)" 
      "VALUES (uuid_generate_v4()"
      ",       :member.name"
      ",       :member.email"
      ",       crypt(:member.password, gen_salt('bf', 8))"   
      ",       :member.role) "
      "RETURNING id;",
      PREPARE(true), // prepared statement!
      PARAM(oatpp::Object<MemberDto>, member))

  QUERY(changeMemberPassword,
      "UPDATE members "
      "SET "
      " pswhash=crypt(:newPassword, gen_salt('bf', 8)) "
      "WHERE "
      " id=:id AND pswhash=crypt(:oldPassword, pswhash);",
      PREPARE(true), // prepared statement!
      PARAM(oatpp::String, memberId, "id"),
      PARAM(oatpp::String, oldPassword),
      PARAM(oatpp::String, newPassword))

  QUERY(authenticateMember,
      "SELECT id FROM members WHERE memberName=:memberName AND passwordHash=crypt(:password, passwordHash);",
      PREPARE(true), // prepared statement!
      PARAM(oatpp::String, memberName),
      PARAM(oatpp::String, password))

  QUERY(deleteMemberById,
      "DELETE FROM members WHERE id=:id;",
      PREPARE(true), // prepared statement!
      PARAM(oatpp::String, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

}

#endif //FARM_FELLOWS_SQL_POSTGRESQL_MEMBER_DB_HPP