#ifndef FARM_FOLLOWS_AUTH_DATETIME_DTO_HPP
#define FARM_FOLLOWS_AUTH_DATETIME_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AuthDatetimeDTO : public oatpp::DTO
{
    DTO_INIT(AuthDatetimeDTO, DTO)

    DTO_FIELD(String, memberId, "memberId");
    DTO_FIELD(String, signupDateTime, "signupdatetime");
    DTO_FIELD(String, signinDateTime, "signindatetime");
    DTO_FIELD(String, lastRequestDateTime, "lastvisitdatetime");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* FARM_FOLLOWS_AUTH_DATETIME_DTO_HPP */