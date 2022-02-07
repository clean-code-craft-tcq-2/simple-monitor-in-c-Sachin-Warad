#include <stdio.h>
#include <assert.h>
#include "checker.h"

const ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, "Charge Rate"}
};

int isParametersWithinRange (ParameterList parametersName, float inputValue) {
  if(inputValue < parameterInfo.minThreshold[parametersName] || inputValue > parameterInfo.maxThreshold[parametersName]) {
      printOnConsole(parameterInfo.msgInput[parametersName]);
      return 0;
  }
  return 1;
}

void printOnConsole(char msg[]) {
    printf("%s out of range!\n",msg);
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(temperature < 0 || temperature > 45) {
    printf("Temperature out of range!\n");
    return 0;
  } else if(soc < 20 || soc > 80) {
    printf("State of Charge out of range!\n");
    return 0;
  } else if(chargeRate > 0.8) {
    printf("Charge Rate out of range!\n");
    return 0;
  }
  return 1;
}

int main() {
  isParametersWithinRange(TempParameter, 25)
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
