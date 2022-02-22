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
    batteryChar.coolingType = HI_ACTIVE_COOLING;
  
  REQUIRE(inferBreach(50, 0,45) == TOO_HIGH);// to cross verify
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,50) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,-15) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,42) == NORMAL);
}

TEST_CASE("Test case to alert TO_CONTROLLER for cooling type MED_ACTIVE_COOLING") {
    BatteryCharacter batteryChar;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
  
  REQUIRE(inferBreach(-10, 0,40) == TOO_LOW);// to cross verify
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,50) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,-10) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,35) == NORMAL);
  
}

TEST_CASE("Test case to alert TO_CONTROLLER for cooling type PASSIVE_COOLING") {
    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
  
  REQUIRE(inferBreach(-10, 0,30) == TOO_LOW);// to cross verify
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,40) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,-10) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,15) == NORMAL);
  
}

TEST_CASE("Test case to alert TO_EMAIL for cooling type HI_ACTIVE_COOLING") {
    BatteryCharacter batteryChar;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
  
  REQUIRE(inferBreach(50, 0,45) == TOO_HIGH);// to cross verify
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,50) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-15) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,42) == NORMAL);
}

TEST_CASE("Test case to alert TO_EMAIL for cooling type MED_ACTIVE_COOLING") {
    BatteryCharacter batteryChar;
    batteryChar.coolingType = MED_ACTIVE_COOLING;
  
  REQUIRE(inferBreach(-10, 0,40) == TOO_LOW);// to cross verify
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,50) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-10) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,35) == NORMAL);
  
}

TEST_CASE("Test case to alert TO_EMAIL for cooling type PASSIVE_COOLING") {
    BatteryCharacter batteryChar;
    batteryChar.coolingType = PASSIVE_COOLING;
  
  REQUIRE(inferBreach(-10, 0,30) == TOO_LOW);// to cross verify
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,40) == TOO_HIGH);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-10) == TOO_LOW);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,15) == NORMAL);
  
}
