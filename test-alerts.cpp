#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Test case to Infer breach when limit is TOO_LOW") {
  REQUIRE(inferBreach(12, 20,30) == TOO_LOW);
}

TEST_CASE("Test case to Infer breach when limit is TOO_HIGH") {
  REQUIRE(inferBreach(32, 20,30) == TOO_HIGH);
}

TEST_CASE("Test case to Infer breach when limit is NORMAL") {
  REQUIRE(inferBreach(25, 20,30) == NORMAL);
}

//** Test cases for checkAndAlert() **//
TEST_CASE("Test case to alert TO_CONTROLLER for cooling type HI_ACTIVE_COOLING") {
    BatteryCharacter batteryChar;
    double temperatureInC = 50;
    BreachType breachType;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    breachType = checkAndAlert(TO_CONTROLLER,batteryChar,temperatureInC);
  
  REQUIRE(inferBreach(50, 0,45) == TOO_HIGH);// to cross verify
  REQUIRE(breachType == TOO_HIGH);
}

TEST_CASE("Test case to alert TO_EMAIL for cooling type MED_ACTIVE_COOLING") {
    BatteryCharacter batteryChar;
    double temperatureInC = -10;
    BreachType breachType;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
    breachType = checkAndAlert(TO_EMAIL,batteryChar,temperatureInC);
  
  REQUIRE(inferBreach(-10, 0,40) == TOO_LOW);// to cross verify
  REQUIRE(breachType == TOO_LOW);
  
}
