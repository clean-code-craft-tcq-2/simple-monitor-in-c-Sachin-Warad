#include <stdio.h>
#include <assert.h>
#include "checker.h"

const ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, "Charge Rate"}
};

int isParametersWithinRange (const parameterDetails[], const double testData[], void (*Fn_Ptr_WarningMsg)(const char)) {
  int result = 1;
  for(int i=0; i< MaxParameter; i++) {
      if(testData[i] < parameterDetails[i].minThreshold || testData[i] > parameterDetails[i].maxThreshold) {
          Fn_Ptr_WarningMsg(parameterDetails[i].msgInput);
          result &= 0;
      } else{
          result &= 1;
      }
  }
  return result;
}

void printOnConsole(const char msg[]) {
    printf("%s out of range!\n",msg);
}

void testBattery(int isBatteryOK, int expectedResult) {
  assert(isBatteryOK == expectedResult);
}

int main() {
  void (*Fn_Ptr_WarningMsg)(const char);
  Fn_Ptr_WarningMsg = &printOnConsole;
  double testData1[] = {25,70,0.7};
  int isBatteryOK = isParametersWithinRange(parameterInfo, testData1, Fn_Ptr_WarningMsg);
  testBattery(isBatteryOk, 1)
//   testBattery(testData1, 1);
//   double testData2[] = {50,85,0.9};
//   testBattery(testData2, 0);
//   double testData3[] = {46,70,0.7};
//   testBattery(testData3, 0);
//   double testData4[] = {25,85,0.7};
//   testBattery(testData4, 0);
//   double testData5[] = {25,70,0.9};
//   testBattery(testData5, 0);
//   double testData6[] = {-10,70,0.9};
//   testBattery(testData6, 0);
  return 0;
}
