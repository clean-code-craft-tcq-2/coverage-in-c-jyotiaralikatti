#pragma once

#define PASSIVECOOLING_LOWERLIMIT 0
#define PASSIVECOOLING_UPPERLIMIT 35

#define HI_ACTIVECOOLING_LOWERLIMIT 0
#define HI_ACTIVECOOLING_UPPERLIMIT 45

#define MED_ACTIVECOOLING_LOWERLIMIT 0
#define MED_ACTIVECOOLING_UPPERLIMIT 40

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  int lowerLimit ;
  int upperLimit ;
}CoolingTypeLimitsConfig;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

BreachType inferBreach(double temperatureInC, CoolingType coolingType );
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
CoolingTypeLimitsConfig GetLimitsOfCoolingType(CoolingType coolingType  );

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
