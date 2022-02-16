#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "checker.h"

ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, TempWarLowThd, TempWarHighThd, "Temperature in Celcius"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, SOCWarLowThd, SOCWarHighThd, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, ChargeRateLowThd, ChargeRateHighThd, "Charge Rate"}
};

int isParametersWithinRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[])) {
  if(inputValue < parameterDetails.minBreachThreshold || inputValue > parameterDetails.maxBreachThreshold) {
      char message = strcat(parameterDetails.paramInput, "out of range");
      Fn_Ptr_WarningMsg(message);
      return 0;
  }
  return 1;
}

int isParametersWithingWarningRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[]), int isWarningRequired) {
    if(evaluateWarningRange(parameterDetails, inputValue) && isWarningRequired) {
        char *message = strcat(parameterDetails.paramInput, "in warning range");
        Fn_Ptr_WarningMsg(message);
        return 0;
    }
    return 1;
}

int evaluateWarningRange(ParameterInfo parameterDetails, double inputValue) {
    if(inputValue <= parameterDetails.minWarningThreshold || inputValue >= parameterDetails.maxWarningThreshold) {
        return 0;
    }
    return 1;
}

void convertFarenheitToCelcius(double testData[]) {
    testData[0] = ((testData[0]-32)*5/9);
}

void convertTemperatureToCelcius(char* temperatureUnit, double testData[]) {
    if(!strcmp(temperatureUnit,"F")) {
        convertFarenheitToCelcius(testData);
    }
}

void printOnConsole(char msg[]) {
    printf(msg);
}

void testBattery(ParameterInfo parameterDetails[], double testData[], int isWarningRequired[], int expectedResult, char* temperatureUnit) {
  int result = 1;
  void (*Fn_Ptr_WarningMsg)(char[]);
  Fn_Ptr_WarningMsg = &printOnConsole;
  convertTemperatureToCelcius(temperatureUnit, testData);
  
  printf(parameterDetails[0].minBreachThreshold, parameterDetails[0].maxBreachThreshold, parameterDetails[0].minWarningThreshold, parameterDetails[0].maxWarningThreshold,
        parameterDetails[1].minBreachThreshold, parameterDetails[1].maxBreachThreshold, parameterDetails[1].minWarningThreshold, parameterDetails[1].maxWarningThreshold,
        parameterDetails[2].minBreachThreshold, parameterDetails[2].maxBreachThreshold, parameterDetails[2].minWarningThreshold, parameterDetails[2].maxWarningThreshold,
        testData[0], testData[1], testData[2]);
  
  for(int i=0; i< MaxParameter; i++) {
      result &= isParametersWithinRange(parameterDetails[i], testData[i], Fn_Ptr_WarningMsg) ? 1 : 
        isParametersWithingWarningRange(parameterDetails[i], testData[i], Fn_Ptr_WarningMsg, isWarningRequired[i]);
  }
  assert(result == expectedResult);
}

int main() {
  double testData1[] = {10,70,0.7};
  int warningRequestStatus[] = {1,1,1};
  testBattery(parameterInfo, testData1, warningRequestStatus, 1, "C");
//   double testData2[] = {50,85,0.9};
//   testBattery(parameterInfo, testData2, 0);
//   double testData3[] = {46,70,0.7};
//   testBattery(parameterInfo, testData3, 0);
//   double testData4[] = {25,85,0.7};
//   testBattery(parameterInfo, testData4, 0);
//   double testData5[] = {25,70,0.9};
//   testBattery(parameterInfo, testData5, 0);
//   double testData6[] = {-10,70,0.9};
//   testBattery(parameterInfo, testData6, 0);
  return 0;
}
