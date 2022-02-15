#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "checker.h"

ParameterInfo parameterInfo [MaxParameter] = {
  {TempParameter, TemperatureMinLimit, TemperatureMaxLimit, TempWarLowThd, TempWarHighThd, "Temperature"},
  {SOCParameter, SOCMinLimit, SOCMaxLimit, SOCWarLowThd, SOCWarHighThd, "State of Charge" },
  {ChargeRateParameter, ChargeRateMinLimit, ChargeRateMaxLimit, ChargeRateLowThd, ChargeRateHighThd, "Charge Rate"}
};

void formatPrintMsg(char ParamInput[][50], char MsgInput[][50], int LanguageInput);

int isParametersWithinRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[])) {
  if(inputValue < parameterDetails.minBreachThreshold || inputValue > parameterDetails.maxBreachThreshold) {
      Fn_Ptr_WarningMsg(parameterDetails.msgInput);
      return 0;
  }
  return 1;
}

int isParametersWithingWarningRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[]), int isWarningRequired) {
    if(evaluateWarningRange(parameterDetails, inputValue) && isWarningRequired) {
        Fn_Ptr_WarningMsg(parameterDetails.msgInput);
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

void printOnConsole(char msg[]) {
    printf("%s out of range!\n",msg);
}

void formatPrintMsg(char ParamInput[][50], char MsgInput[][50], int LanguageInput) {
    if(LanguageInput) {
        for(int i=0; i<MaxParameter; i++){
            strcpy(ParamInput[i][50], ENGParamInput[i][50]);
        }
        strcpy(MsgInput[0][50], ENGMsgInput[0][50]);
        strcpy(MsgInput[1][50], ENGMsgInput[1][50]);
    }
}

void testBattery(ParameterInfo parameterDetails[], double testData[], int isWarningRequired[], int expectedResult) {
  int result = 1;
  char ParamInput[MaxParameter][50] = {0};
  char MsgInput[2][50] = {0};
  formatPrintMsg(ParamInput, MsgInput,1);
  void (*Fn_Ptr_WarningMsg)(char[]);
  Fn_Ptr_WarningMsg = &printOnConsole;
  
  for(int i=0; i< MaxParameter; i++) {
      result &= isParametersWithinRange(parameterDetails[i], testData[i], Fn_Ptr_WarningMsg) ? 1 : 
        isParametersWithingWarningRange(parameterDetails[i], testData[i], Fn_Ptr_WarningMsg, isWarningRequired[i]);
  }
  assert(result == expectedResult);
}

int main() {
  double testData1[] = {25,70,0.7};
  int warningRequestStatus[] = {1,1,1};
  testBattery(parameterInfo, testData1, warningRequestStatus, 1);
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
