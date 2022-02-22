#include "typewise-alert.h"
#include <stdio.h>

void (*alertTarget_FuncPtr[])(BreachType)={sendToController,sendToEmail};

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC );

alertTarget_FuncPtr[alertTarget](breachType);
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingTypeLimitsConfig LimitsConfigPtr;
    LimitsConfigPtr = GetLimitsOfCoolingType(coolingType);

  printf("limits->lowerLimit :%d",LimitsConfigPtr.lowerLimit);
  return inferBreach(temperatureInC, LimitsConfigPtr.lowerLimit, LimitsConfigPtr.upperLimit);
}

CoolingTypeLimitsConfig GetLimitsOfCoolingType(CoolingType coolingType )
{
    return LimitsConfig[coolingType];
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
