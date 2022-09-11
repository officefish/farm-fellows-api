#ifndef FALL_FOLLOWS_AUTH_TEST_HPP
#define FALL_FOLLOWS_AUTH_TEST_HPP

#include "oatpp-test/UnitTest.hpp"

class AuthTest : public oatpp::test::UnitTest {
public:
  AuthTest() : oatpp::test::UnitTest("[MyTest]")
  {}

  void onRun() override;

};


#endif //FALL_FOLLOWS_AUTH_TEST_HPP