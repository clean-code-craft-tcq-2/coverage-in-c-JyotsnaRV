#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to lower limit crossed") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach to higher limit crossed") {
  REQUIRE(inferBreach(42, 10, 40) == TOO_HIGH);
}

TEST_CASE("infers the breach is normal") {
  REQUIRE(inferBreach(40, 5, 40) == NORMAL);
}
