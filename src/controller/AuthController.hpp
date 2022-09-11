#ifndef FARM_FELLOWS_AUTH_CONTROLLER_HPP
#define FARM_FELLOWS_AUTH_CONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "service/auth/AuthService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class AuthController : public oatpp::web::server::api::ApiController {
public:
  AuthController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  AuthService m_memberService; // Create user service.
public:

  static std::shared_ptr<AuthController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<AuthController>(objectMapper);
  }

  ENDPOINT_INFO(signUp) {
    info->summary = "Join to community";
    info->addTag("Auth");

    info->addConsumes<Object<SignUpDto>> ("application/json");

    info->addResponse<Object<AuthDto>> (Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "members/join", signUp,
        BODY_DTO(Object<SignUpDto>, dto))
  {
    return createDtoResponse(Status::CODE_200, m_memberService.signUp(dto));
  }

  ENDPOINT_INFO(signIn) {
    info->summary = "Comeback to community";
    info->addTag("Auth");

    info->addConsumes <Object<SignInDto>> ("application/json");

    info->addResponse <Object<AuthDto>> (Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "members/comeback", signIn,
        BODY_DTO(Object<SignInDto>, dto))      
  {
    return createDtoResponse(Status::CODE_200, m_memberService.signIn(dto));
  }

  ENDPOINT_INFO(deleteMember) {
    info->summary = "Delete member";
    info->addTag("Auth");

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("DELETE", "members", deleteMember,
           BUNDLE(String, memberId))
  {
    return createDtoResponse(Status::CODE_200, m_memberService.deleteMemberById(memberId));
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif //FARM_FELLOWS_AUTH_CONTROLLER_HPP