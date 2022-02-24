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

TEST_CASE("Infers the high breach according to passive cooling limits and sending to e-mail") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "PASSIVE_COOLING_HIGH_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, batteryChar, 36) == ALERT_SUCCESS);
}

TEST_CASE("infers the low breach according to passive cooling limits and sending to controller") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "PASSIVE_COOLING_LOW_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, batteryChar, -2) == ALERT_SUCCESS);
}

TEST_CASE("infers the no breach according to high active cooling limits and sending to Console") {
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "NORMAL_HI_ACTIVE_COOLING"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, batteryChar, 45) == ALERT_SUCCESS);
}

TEST_CASE("infers the high breach according to high active cooling limits and sending to e-mail") {
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "HI_ACTIVE_COOLING_HIGH_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, batteryChar, 46) == ALERT_SUCCESS);
}

TEST_CASE("infers the low breach according to high active cooling limits and sending to controller") {
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "HI_ACTIVE_COOLING_LOW_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, batteryChar, -2) == ALERT_SUCCESS);
}

TEST_CASE("infers the high breach according to med active cooling limits and sending to e-mail") {
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "MED_ACTIVE_COOLING_HIGH_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, batteryChar, 41) == ALERT_SUCCESS);
}

TEST_CASE("infers the low breach according to med active cooling limits and sending to controller") {
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "MED_ACTIVE_COOLING_LOW_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, batteryChar, -2) == ALERT_SUCCESS);
}

TEST_CASE(" Negative test - Unknown cooling type requested") {
  BatteryCharacter batteryChar = {(CoolingType)4, "MED_ACTIVE_COOLING_LOW_BREACH"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, batteryChar, 40) == UNKNOWN_BREACH_ALERT_FAILED);
}

TEST_CASE(" Negative test - Unknown alert type requested") {
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "MED_ACTIVE_COOLING_LOW_BREACH"};
  REQUIRE(classifyBreachAndAlert((AlertTarget)3, batteryChar, -2) == ALERT_FAILURE);
}



