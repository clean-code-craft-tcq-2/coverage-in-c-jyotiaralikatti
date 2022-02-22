#include "typewise-alert.h"
#include <stdio.h>
CoolingTypeLimitsConfig LimitsConfig[] = {/* LimitsConfig[coolingType] */
    /*lowerLimit                    upperLimit*/
    {PASSIVECOOLING_LOWERLIMIT,    PASSIVECOOLING_UPPERLIMIT },
    {HI_ACTIVECOOLING_LOWERLIMIT,  HI_ACTIVECOOLING_UPPERLIMIT},
    {MED_ACTIVECOOLING_LOWERLIMIT, MED_ACTIVECOOLING_UPPERLIMIT}
  };
const char* BreachTypeParameters[] = {"NORMAL","TOO_LOW","TOO_HIGH"};

void (*alertTarget_FuncPtr[])(BreachType)={sendToController,sendToEmail};

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC );

alertTarget_FuncPtr[alertTarget](breachType);
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingTypeLimitsConfig LimitsConfigPtr;//
    LimitsConfigPtr = GetLimitsOfCoolingType(coolingType);//

  printf("limits->lowerLimit :%d",LimitsConfigPtr.lowerLimit);//
  return inferBreach(temperatureInC, coolingType);
}

CoolingTypeLimitsConfig GetLimitsOfCoolingType(CoolingType coolingType )
{
    return LimitsConfig[coolingType];
}

BreachType inferBreach(double temperatureInC, CoolingType coolingType )
{
  if(temperatureInC < LimitsConfig[coolingType].lowerLimit) {
    return TOO_LOW;
  }
  if(temperatureInC > LimitsConfig[coolingType].upperLimit) {
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
int main()
{
    BatteryCharacter batteryChar;
    double temperatureInC = 100;
    batteryChar.coolingType = HI_ACTIVE_COOLING;
    printf("Send to controller case + HI_ACTIVE_COOLING\n");
    checkAndAlert(TO_CONTROLLER,batteryChar,temperatureInC);
    
    printf("Send to email case\n ");
    temperatureInC = 0;
    checkAndAlert(TO_EMAIL,batteryChar,temperatureInC);
    return 0;
}
