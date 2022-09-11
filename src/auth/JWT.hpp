#ifndef FARM_FELLOWS_JWT_HPP
#define FARM_FELLOWS_JWT_HPP

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/core/Types.hpp"

#include "jwt-cpp/jwt.h"
#include "jwt-cpp/traits/kazuho-picojson/traits.h"

class JWT {
public:

  struct Payload : public oatpp::web::server::handler::AuthorizationObject {

    oatpp::String memberId;

  };

private:
  oatpp::String m_secret;
  oatpp::String m_issuer;
  jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> m_verifier;
public:

  JWT(const oatpp::String& secret,
      const oatpp::String& issuer);

  oatpp::String createToken(const std::shared_ptr<Payload>& payload);

  std::shared_ptr<Payload> readAndVerifyToken(const oatpp::String& token);

};

#endif //FARM_FELLOWS_JWT_HPP

