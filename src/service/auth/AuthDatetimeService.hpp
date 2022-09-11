#ifndef FARM_FELLOWS_AUTH_DATETIME_SERVICE_HPP
#define FARM_FELLOWS_AUTH_DATETIME_SERVICE_HPP

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include "db/postgresql/auth/AuthDatetimeDb.hpp"

class AuthDatetimeService {
private:
  typedef farmfellows::sql::postgresql::AuthDatetimeDb AuthDatetimeDb;
  typedef oatpp::web::protocol::http::Status Status;

private:
  OATPP_COMPONENT(std::shared_ptr<AuthDatetimeDb>, m_database); // Inject database component
  
public:
  bool createAuthDatetime(const oatpp::String& memberId);
  bool updateSigninDatetime(const oatpp::String& memberId);
  bool updateLastVisitDatetime(const oatpp::String& memberId);
};

#endif //FARM_FELLOWS_AUTH_DATETIME_SERVICE_HPP