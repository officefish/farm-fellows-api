#ifndef FARM_FELLOWS_TEMP_USER_DTO_HPP
#define FARM_FELLOWS_TEMP_USER_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

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

class UserMinimumDto : public oatpp::DTO {
    
    DTO_INIT(UserMinimumDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, username, "username");

};

class UserDto : public UserMinimumDto {
  
    DTO_INIT(UserDto, UserMinimumDto)

    DTO_FIELD(String, email, "email");
    DTO_FIELD(String, password, "password");
    DTO_FIELD(Enum<Role>::AsString, role, "role");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* FARM_FELLOWS_USER_DTO_HPP */