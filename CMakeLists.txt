cmake_minimum_required(VERSION 3.1)
project(farm-fellows)

set(CMAKE_CXX_STANDARD 17)

add_library(farm-fellows-lib
    src/auth/AuthHandler.cpp
    src/auth/AuthHandler.hpp
    src/auth/JWT.cpp
    src/auth/JWT.hpp
    src/db/postgresql/auth/AuthDatetimeDb.hpp
    src/db/postgresql/member/MemberDb.hpp
    src/dto/request/StatusDto.hpp
    src/dto/request/PageDto.hpp
    src/dto/member/datetime/AuthDatetimeDto.hpp
    src/dto/member/AuthDto.hpp
    src/dto/member/MemberDto.hpp
    src/dto/member/MembersPageDto.hpp
    src/service/auth/AuthService.hpp
    src/service/auth/AuthService.cpp
    src/service/auth/AuthDatetimeService.hpp
    src/service/auth/AuthDatetimeService.cpp
    src/service/UserService.hpp
    src/service/UserService.cpp
    src/controller/AuthController.hpp
    src/controller/StaticController.hpp
    src/controller/UserController.hpp
    src/interceptor/AuthInterceptor.hpp
    src/interceptor/AuthInterceptor.cpp
    src/component/error/ErrorHandler.hpp
    src/component/error/ErrorHandler.cpp
    src/component/JwtComponent.hpp
    src/component/UuidComponent.hpp
    src/component/SQLiteComponent.hpp
    src/component/PostgresqlComponent.hpp
    src/component/ConnectionComponent.hpp
    src/component/SwaggerComponent.hpp
    src/component/AppComponent.hpp)

## include directories

target_include_directories(farm-fellows-lib PUBLIC src)

## OpenSSl

find_package(OpenSSL 1.1 REQUIRED)

## Oat++

find_package(oatpp            1.3.0 REQUIRED)
find_package(oatpp-swagger    1.3.0 REQUIRED)
find_package(oatpp-sqlite     1.3.0 REQUIRED)
find_package(oatpp-openssl    1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)

if(oatpp_FOUND)
  message(STATUS "Found oatpp version: ${oatpp_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp")
endif()

if(oatpp-swagger_FOUND)
  message(STATUS "Found oatpp-swagger version: ${oatpp-swagger_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp-swagger")
endif()

if(oatpp-sqlite_FOUND)
  message(STATUS "Found oatpp-sqlite version: ${oatpp-sqlite_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp-sqlite")
endif()

if(oatpp-openssl_FOUND)
  message(STATUS "Found oatpp-openssl version: ${oatpp-openssl_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp-openssl")
endif()

if(oatpp-postgresql_FOUND)
  message(STATUS "Found oatpp-postgresql version: ${oatpp-postgresql_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp-postgresql")
endif()

## jwt-cpp

find_package(jwt-cpp REQUIRED PATHS /usr/local/cmake)

if(jwt-cpp_FOUND)
  message(STATUS "Found jwt-cpp version: ${jwt-cpp_VERSION}")
else()
  message(FATAL_ERROR "Could not find jwt-cpp")
endif()

## Sqlite3

find_package(SQLite3 REQUIRED)

if(SQLite3_FOUND)
  message(STATUS "Found SQLite3 version: ${SQLite3_VERSION}")
else()
  message(FATAL_ERROR "Could not find SQLite3")
endif()

## stduuid

find_package(stduuid REQUIRED)

if(stduuid_FOUND)
  message(STATUS "Found stduuid version: ${stduuid_VERSION}")
else()
  message(FATAL_ERROR "Could not find stduuid")
endif()

## links

target_link_libraries(farm-fellows-lib
        
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
        PUBLIC oatpp::oatpp-openssl
        PUBLIC oatpp::oatpp-postgresql

        # third-party
        PUBLIC jwt-cpp::jwt-cpp
        PUBLIC OpenSSL::SSL
        PUBLIC OpenSSL::Crypto
        PUBLIC SQLite::SQLite3
        PUBLIC stduuid
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(farm-fellows-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_definitions(
    ## define host
    -DSERVER_HOST="127.0.0.1"

    ## define port
    -DSERVER_PORT=8000

    ## define jwt secret
    -DJWT_SECRET="AltaVist@1984"

    ## define jwt issuer
    -DJWT_ISSUER="Auth0"

    ## define path to swagger-ui static resources folder
    -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

    ## SQLite database file
    -DSQLITE_DATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
    ## SQLite database test file
    -DSQLITE_TESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

    ## Path to sqlite database migration scripts
    -DSQLITE_DATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql/sqlite"

    ## Path to postgresql database migration scripts
    -DPOSTGRESQL_DATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql/postgresql"

    ## Unix socket postgresql database libpq connection  
    -DPOSTGRESQL_DATABASE_LIBPQ_CONNECTION="postgresql:///officefish?host=/var/run/postgresql&port=5432&user=officefish"

)

## add executables

add_executable(farm-fellows-exe src/App.cpp)
target_link_libraries(farm-fellows-exe farm-fellows-lib)

add_executable(farm-fellows-test
        test/AuthTest.cpp
        test/AuthTest.hpp
        test/tests.cpp
)
target_link_libraries(farm-fellows-test farm-fellows-lib)

enable_testing()
add_test(project-tests farm-fellows-test)

