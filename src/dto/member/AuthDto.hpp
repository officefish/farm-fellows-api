#ifndef FARM_FELLOWS_AUTH_DTO_HPP
#define FARM_FELLOWS_AUTH_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AuthDto : public oatpp::DTO {  
  DTO_INIT(AuthDto, DTO)

  DTO_FIELD(String, token);
};

class SignInDto : public oatpp::DTO {
    DTO_INIT(SignInDto, DTO)

    DTO_FIELD(String, memberName, "membername");
    DTO_FIELD(String, password, "password");
};

class SignUpDto : public SignInDto {
    DTO_INIT(SignUpDto, SignInDto)

    DTO_FIELD(String, email, "email");
};

#include OATPP_CODEGEN_END(DTO)

#endif // FARM_FELLOWS_AUTH_DTO_HPP 