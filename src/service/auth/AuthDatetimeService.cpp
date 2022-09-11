#include "./AuthDatetimeService.hpp"

bool AuthDatetimeService::createAuthDatetime(const oatpp::String& memberId)
{
    auto dbResult = m_database->createAuthDatetime(memberId);
  
    if(!dbResult->isSuccess()) {
        OATPP_LOGE("AuthDatetimeService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
    }
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized");

    return true;
}
  
bool AuthDatetimeService::updateSigninDatetime(const oatpp::String& memberId)
{
    auto dbResult = m_database->updateSigninDatetime(memberId);

    if(!dbResult->isSuccess()) {
        OATPP_LOGE("AuthDatetimeService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
    }
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized");

    return true;
}
  
bool AuthDatetimeService::updateLastVisitDatetime(const oatpp::String& memberId)
{
    auto dbResult = m_database->updateLastVisitDatetime(memberId);

    if(!dbResult->isSuccess()) {
        OATPP_LOGE("AuthDatetimeService", "DB-Error: '%s'", dbResult->getErrorMessage()->c_str());
    }
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_401, "Unauthorized");

    return true;
}

