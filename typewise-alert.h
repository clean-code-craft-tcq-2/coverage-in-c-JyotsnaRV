#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  TOO_LOW,
  TOO_HIGH,
  NORMAL,
  NOTABREACH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef enum
{
  ALERT_FAILURE,
  ALERT_SUCCESS,
  ALERT_NOT_REQ
}AlertRetStatus;

AlertRetStatus checkAndAlert(AlertTarget alertTarget, BreachType typeOfBreach, double temperatureInC);
AlertRetStatus classifyBreachAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
