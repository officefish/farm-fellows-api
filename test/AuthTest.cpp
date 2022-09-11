#include "./AuthTest.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "component/AppComponent.hpp"
#include "controller/AuthController.hpp"

//#include "controller/StoryController.hpp"

#include <thread>

namespace {

#include OATPP_CODEGEN_BEGIN(ApiClient)

class Client : public oatpp::web::client::ApiClient {
public:

  API_CLIENT_INIT(Client)

  API_CALL("POST", "members/comeback", signin, BODY_DTO(oatpp::Object<SignInDto>, dto))
  //API_CALL("GET", "stories/offset/{offset}/limit/{limit}", getStoreis, AUTHORIZATION(String, authString, "Bearer"), PATH(Int32, offset), PATH(Int32, limit))

};

#include OATPP_CODEGEN_END(ApiClient)

void runTestClient() {

  auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared(
    {SERVER_HOST, SERVER_PORT}
  );

  auto executor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
  auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
  auto client = Client::createShared(executor, mapper);

  oatpp::Object<AuthDto> auth;

  {
    auto signin = SignInDto::createShared();
    signin->memberName = "admin";
    signin->password = "admin";

    auto response = client->signin(signin);

    OATPP_ASSERT(response->getStatusCode() == 200)
    auth = response->readBodyToDto<oatpp::Object<AuthDto>>(mapper);

    OATPP_ASSERT(auth)
    OATPP_ASSERT(auth->token)

    OATPP_LOGD("TEST", "token='%s'", auth->token->c_str())
  }

}

}

void AuthTest::onRun() {

  AppComponent components;

  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
  OATPP_COMPONENT(std::shared_ptr<oatpp::postgresql::ConnectionPool>, dbConnectionPool);

  router->addController(AuthController::createShared());

  oatpp::network::Server server(connectionProvider, connectionHandler);

  std::thread serverThread([&server]{
    server.run();
  });

  runTestClient();

  server.stop();
  connectionProvider->stop();
  connectionHandler->stop();
  dbConnectionPool->stop();

  serverThread.join();

}