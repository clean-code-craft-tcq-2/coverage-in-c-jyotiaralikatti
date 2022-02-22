#include "typewise-alert.h"
#include <stdio.h>
#include <assert.h>

CoolingTypeLimitsConfig LimitsConfig[] = {/* LimitsConfig[coolingType] */
    /*lowerLimit                    upperLimit*/
    {PASSIVECOOLING_LOWERLIMIT,    PASSIVECOOLING_UPPERLIMIT },
    {HI_ACTIVECOOLING_LOWERLIMIT,  HI_ACTIVECOOLING_UPPERLIMIT},
    {MED_ACTIVECOOLING_LOWERLIMIT, MED_ACTIVECOOLING_UPPERLIMIT}
  };
const char* BreachTypeParameters[] = {"NORMAL","TOO_LOW","TOO_HIGH"};

void (*alertTarget_FuncPtr[])(BreachType)={sendToController,sendToEmail};

BreachType  checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC );

alertTarget_FuncPtr[alertTarget](breachType);

return breachType ;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingTypeLimitsConfig LimitsConfigPtr;
    LimitsConfigPtr = GetLimitsOfCoolingType(coolingType);

  return inferBreach(temperatureInC, LimitsConfigPtr.lowerLimit, LimitsConfigPtr.upperLimit);
}

CoolingTypeLimitsConfig GetLimitsOfCoolingType(CoolingType coolingType )
{
    return LimitsConfig[coolingType];
}

BreachType inferBreach(double temperatureInC, int lowerLimit, int upperLimit )
{
  if(temperatureInC < lowerLimit) {
    return TOO_LOW;
  }
  if(temperatureInC > upperLimit) {
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
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is %s\n",BreachTypeParameters[breachType]);
}
