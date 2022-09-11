#ifndef FARM_FELLOWS_AUTH_HANDLER_HPP
#define FARM_FELLOWS_AUTH_HANDLER_HPP

#include "./JWT.hpp"

class AuthHandler : public oatpp::web::server::handler::BearerAuthorizationHandler {
private:
  std::shared_ptr<JWT> m_jwt;
public:

  AuthHandler(const std::shared_ptr<JWT>& jwt);

  std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& token) override;

};

#endif //FARM_FELLOWS_AUTH_HANDLER_HPP

