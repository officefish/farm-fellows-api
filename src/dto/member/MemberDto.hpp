#ifndef FARM_FOLLOWS_MEMBER_DTO_HPP
#define FARM_FOLLOWS_MEMBER_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "./datetime/AuthDatetimeDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
    VALUE(GUEST, 0, "ROLE_GUEST"),
    VALUE(ADMIN, 1, "ROLE_ADMIN"),
    VALUE(FOLLOWER, 2, "ROLE_FOLLOWER"),
    VALUE(FOLLOWER_ADMIN, 3, "ROLE_FOLLOWER_ADMIN"),
    VALUE(FARMER, 4, "ROLE_FARMER"),
    VALUE(FARMER_ADMIN, 5, "ROLE_FARMER_ADMIN"),
    VALUE(FARMER_FOLLOWER, 6, "ROLE_FARMER_FOLLOWER"),
    VALUE(FARMER_FOLLOWER_ADMIN, 7, "ROLE_FARMER_FOLLOWER_ADMIN")
)

class MemberMinimumDto : public oatpp::DTO {
  DTO_INIT(MemberMinimumDto, DTO)

  DTO_FIELD(String, id);
  DTO_FIELD(String, memberName, "name");
};

class MemberDto : public MemberMinimumDto {

  DTO_INIT(MemberDto, MemberMinimumDto)

  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");
  DTO_FIELD(Enum<Role>::AsNumber, memberRole, "role");

};

class MemberMaximumDto : public MemberDto {
  DTO_INIT(MemberMaximumDto, MemberDto)

  DTO_FIELD(oatpp::Object<AuthDatetimeDTO>, authDatetime, "authdatetime");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* FARM_FOLLOWS_MEMBER_DTO_HPP */