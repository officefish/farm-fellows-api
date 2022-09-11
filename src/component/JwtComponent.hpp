#ifndef FARM_FELLOWS_JWT_COMPONENT_HPP
#define FARM_FELLOWS_JWT_COMPONENT_HPP

#include "jwt-cpp/jwt.h"

class JwtComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<JWT>, jwt)([]{
        return std::make_shared<JWT>(JWT_SECRET, JWT_ISSUER);
    }());
};

#endif // FARM_FELLOWS_JWT_COMPONENT_HPP

