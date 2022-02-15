#include <stdio.h>
#include <assert.h>
#include "checker.h"

ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, TempWarLowThd, TempWarHighThd, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, SOCWarLowThd, SOCWarHighThd, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, ChargeRateLowThd, ChargeRateHighThd, "Charge Rate"}
};

int isParametersWithinRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[])) {
  if(inputValue < parameterDetails.minBreachThreshold || inputValue > parameterDetails.maxBreachThreshold) {
      Fn_Ptr_WarningMsg(parameterDetails.msgInput);
      return 0;
  }else(inputValue <= parameterDetails.minWarningThreshold || inputValue > parameterDetails.maxWarningThreshold) {
      Fn_Ptr_WarningMsg(parameterDetails.msgInput);
      return 0;
  }
//   return 1;
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
  testBattery(parameterInfo, testData2, 0);
  double testData3[] = {46,70,0.7};
  testBattery(parameterInfo, testData3, 0);
  double testData4[] = {25,85,0.7};
  testBattery(parameterInfo, testData4, 0);
  double testData5[] = {25,70,0.9};
  testBattery(parameterInfo, testData5, 0);
  double testData6[] = {-10,70,0.9};
  testBattery(parameterInfo, testData6, 0);
  return 0;
}
