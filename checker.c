#include <stdio.h>
#include <assert.h>
#include "checker.h"

ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, "Charge Rate"}
};

int isParametersWithinRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[])) {
  if(inputValue < parameterDetails.minThreshold || inputValue > parameterDetails.maxThreshold) {
      Fn_Ptr_WarningMsg(parameterDetails.msgInput);
      return 0;
  }
  return 1;
}

void printOnConsole(char msg[]) {
    printf("%s out of range!\n",msg);
}

void testBattery(ParameterInfo parameterDetails[], double testData[], int expectedResult) {
  int result = 1;
  void (*Fn_Ptr_WarningMsg)(char[]);
  Fn_Ptr_WarningMsg = &printOnConsole;
  for(int i=0; i< MaxParameter; i++) {
      result &= isParametersWithinRange(parameterDetails[i], testData[i], Fn_Ptr_WarningMsg);
  }
  assert(result == expectedResult);
}

int main() {
  double testData1[] = {25,70,0.7};
  testBattery(parameterInfo, testData1, 1);
  double testData2[] = {50,85,0.9};
  testBattery(testData2, 0);
  double testData3[] = {46,70,0.7};
  testBattery(testData3, 0);
  double testData4[] = {25,85,0.7};
  testBattery(testData4, 0);
  double testData5[] = {25,70,0.9};
  testBattery(testData5, 0);
  double testData6[] = {-10,70,0.9};
  testBattery(testData6, 0);
  return 0;
}
