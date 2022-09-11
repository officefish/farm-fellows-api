#include "./AuthInterceptor.hpp"

AuthInterceptor::AuthInterceptor(const std::shared_ptr<JWT>& jwt)
  : m_authHandler(jwt)
{
  authEndpoints.route("POST", "members/join", false);
  authEndpoints.route("POST", "members/comeback", false);
  
  authEndpoints.route("GET", "/", false);
  
  authEndpoints.route("GET", "swagger/*", false);
  authEndpoints.route("GET", "api-docs/oas-3.0.0.json", false);
}

std::shared_ptr<AuthInterceptor::OutgoingResponse> AuthInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request) {

  auto r = authEndpoints.getRoute(request->getStartingLine().method, request->getStartingLine().path);
  if(r && !r.getEndpoint()) {
    return nullptr; // Continue without Authorization
  }

  auto authHeader = request->getHeader(oatpp::web::protocol::http::Header::AUTHORIZATION);

  auto authObject = std::static_pointer_cast<JWT::Payload>(m_authHandler.handleAuthorization(authHeader));
  if(authObject) {

    request->putBundleData("memberId", authObject->memberId);

    // update auth datetime object with current datetime request.
    m_datetimeService.updateLastVisitDatetime(authObject->memberId);
    
    return nullptr; // Continue - token is valid.
  }

  throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401, "Unauthorized", {});

}