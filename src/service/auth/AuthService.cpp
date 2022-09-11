#include "./AuthService.hpp"

oatpp::Object<AuthDto> AuthService::signUp(const oatpp::Object<SignUpDto>& dto) {

  //std::string memberUUID = m_uuid_generator->basic_uuid_random_generator_str();

  auto member = MemberDto::createShared();
  member->memberName = dto->memberName;
  member->email = dto->email;
  member->password = dto->password;
  //member->id = memberUUID:
  member->memberRole = 0;

  auto dbResult = m_database->createMember(member);
  
  if(!dbResult->isSuccess()) {
    OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
  }
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Vector<oatpp::String>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_401, "Unauthorized")

  auto newMemberId = result[0][0];

  auto payload = std::make_shared<JWT::Payload>();
  payload->memberId = newMemberId;

  m_datetimeService.createAuthDatetime(newMemberId);

  auto auth = AuthDto::createShared();
  auth->token = m_jwt->createToken(payload);

  return auth;

}

oatpp::Object<AuthDto> AuthService::signIn(const oatpp::Object<SignInDto>& dto) {

  auto dbResult = m_database->authenticateMember(dto->memberName, dto->password);
  if(!dbResult->isSuccess()) {
    OATPP_LOGE("AuthService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
  }
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized")

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Vector<oatpp::String>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_401, "Unauthorized")

  auto memberId = result[0][0];

  auto payload = std::make_shared<JWT::Payload>();
  payload->memberId = memberId;

  m_datetimeService.updateSigninDatetime(memberId);

  auto auth = AuthDto::createShared();
  auth->token = m_jwt->createToken(payload);

  return auth;

}

oatpp::Object<StatusDto> AuthService::deleteMemberById(const oatpp::String& memberId) {
  auto dbResult = m_database->deleteMemberById(memberId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "Member was successfully deleted";
  return status;
}