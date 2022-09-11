#ifndef FARM_FOLLOWS_USER_SERVICE_HPP
#define FARM_FOLLOWS_USER_SERVICE_HPP

/*
#include "./db/sqlite/UserDb.hpp"
#include "./dto/PageDto.hpp"
#include "./dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService {
private:
  typedef oatpp::web::protocol::http::Status Status;
  typedef const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& ResourceHandleConnection;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

    oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> getUserById(const oatpp::Int32& id, ResourceHandleConnection connection = nullptr);    
    oatpp::Object<UserMinimumDto> getUserMinimumById(const oatpp::Int32& id, ResourceHandleConnection connection = nullptr);

    oatpp::Object<PageDto<oatpp::Object<UserDto>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<PageDto<oatpp::Object<UserMinimumDto>>> getAllUsersMinimum(const oatpp::UInt32& offset, const oatpp::UInt32& limit);

    oatpp::Object<StatusDto> deleteUserById(const oatpp::Int32& id);

};
*/

#endif //FARM_FOLLOWS_USER_SERVICE_HPP