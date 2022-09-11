#ifndef FARM_FELLOWS_MEMBERS_PAGE_DTO_HPP
#define FARM_FELLOWS_MEMBERS_PAGE_DTO_HPP

#include "dto/member/MemberDto.hpp"
#include "dto/request/PageDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MembersMinimumPageDto : public PageDto<oatpp::Object<MemberMinimumDto>> {

  DTO_INIT(MembersMinimumPageDto, PageDto<oatpp::Object<MemberMinimumDto>>)

}; 

class MembersPageDto : public PageDto<oatpp::Object<MemberDto>> {

  DTO_INIT(MembersPageDto, PageDto<oatpp::Object<MemberDto>>)

};

class MembersMaximumPageDto : public PageDto<oatpp::Object<MemberMaximumDto>> {

  DTO_INIT(MembersMaximumPageDto, PageDto<oatpp::Object<MemberMaximumDto>>)

};

#include OATPP_CODEGEN_END(DTO)

#endif //FARM_FELLOWS_MEMBERS_PAGE_DTO_HPP

