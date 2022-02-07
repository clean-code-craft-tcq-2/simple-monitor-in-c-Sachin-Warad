#include <stdio.h>
#include <assert.h>
#include "checker.h"

ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, "Charge Rate"}
};

int isParametersWithinRange (ParameterList parametersName, float inputValue) {
  printf("%f,%f,%f",inputValue, parameterInfo[parametersName].minThreshold, parameterInfo[parametersName].maxThreshold);
  if(inputValue < parameterInfo[parametersName].minThreshold || inputValue > parameterInfo[parametersName].maxThreshold) {
      printOnConsole(parameterInfo[parametersName].msgInput);
      return 0;
  }
  return 1;
}

void printOnConsole(char msg[]) {
    printf("%s out of range!\n",msg);
}

void testBattery(float testData[], int expectedResult) {
  for(int i=0; i< MaxParameter; i++) {
      result &= isParametersWithinRange(parameterInfo[i].parameterName, testData[i]);
  }
  assert(result == 1);
}

int main() {
  float testData1[] = {25, 70, 0.7};
  testBattery(testData1, 1);
  float testData2[] = {50,85,0.9};
  testBattery(testData2, 0);
  float testData3[] = {46,70,0.7};
  testBattery(testData3, 0);
  float testData4[] = {25,85,0.7};
  testBattery(testData4, 0);
  float testData5[] = {25,70,0.9};
  testBattery(testData5, 0);
  return0;
}
