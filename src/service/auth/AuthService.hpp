#ifndef FARM_FELLOWS_AUTH_SERVICE_HPP
#define FARM_FELLOWS_AUTH_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "auth/JWT.hpp"

//#include "component/UuidComponent.hpp"

#include "db/postgresql/member/MemberDb.hpp"

#include "dto/member/AuthDto.hpp"

#include "dto/request/StatusDto.hpp"
#include "dto/request/PageDto.hpp"

#include "./AuthDatetimeService.hpp"

class AuthService {
private:
  typedef farmfellows::sql::postgresql::MemberDb MemberDb;
  typedef oatpp::web::protocol::http::Status Status;

private:
  AuthDatetimeService m_datetimeService;

private:
  OATPP_COMPONENT(std::shared_ptr<MemberDb>, m_database); // Inject database component
  OATPP_COMPONENT(std::shared_ptr<JWT>, m_jwt); // Inject JWT component
  //OATPP_COMPONENT(std::shared_ptr<UUID_Generator>, m_uuid_generator); // Inject uuid generator component

public:
  oatpp::Object<AuthDto> signUp(const oatpp::Object<SignUpDto>& dto);
  oatpp::Object<AuthDto> signIn(const oatpp::Object<SignInDto>& dto);
  oatpp::Object<StatusDto> deleteMemberById(const oatpp::String& id);

};

#endif //FARM_FELLOWS_AUTH_SERVICE_HPP