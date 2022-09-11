
#include <iostream>

#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"

#include "./component/AppComponent.hpp"
#include "./controller/StaticController.hpp"
//#include "./controller/UserController.hpp"
#include "./controller/AuthController.hpp"

void run() {
  
  AppComponent components; // Create scope Environment components

  /* Get router component */
  auto router = components.connection.httpRouter.getObject();

  /* Make Endpoints */
  oatpp::web::server::api::Endpoints docEndpoints;

  /* Add controllers */
  docEndpoints.append(router->addController(AuthController::createShared())->getEndpoints());
  //docEndpoints.append(router->addController(UserController::createShared())->getEndpoints());

  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
  router->addController(StaticController::createShared());

  /* Init server */
  oatpp::network::Server server(components.connection.serverConnectionProvider.getObject(),
                                components.connection.serverConnectionHandler.getObject());
  
  OATPP_LOGD("Server", "Running on port %s...", 
              components.connection.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
  
  /* Run server */
  server.run();

  /* stop sqlite connection pool */
  //components.sqlite.sqliteConnectionProvider.getObject()->stop();

}

/**
 *  main
 */
int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run();
  
  /* Print how many objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
  
  return 0;
}