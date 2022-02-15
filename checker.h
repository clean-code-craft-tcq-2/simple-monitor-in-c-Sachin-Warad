#define TemperatureMinLimit 0
#define TemperatureMaxLimit 45
#define SOCMinLimit 20
#define SOCMaxLimit 80
#define ChargeRateMinLimit 0.0
#define ChargeRateMaxLimit 0.8
#define ToleranceRate 5
#define TempToleranceValue (TemperatureMaxLimit*(ToleranceRate/100))
#define TempWarLowThd (TemperatureMinLimit+TempToleranceValue)
#define TempWarHighThd (TemperatureMaxLimit-TempToleranceValue)
#define SOCToleranceValue (SOCMaxLimit*(ToleranceRate/100))
#define SOCWarLowThd (SOCMinLimit+SOCToleranceValue)
#define SOCWarHighThd (SOCMaxLimit-SOCToleranceValue)
#define ChargeRateToleranceValue (ChargeRateMaxLimit*(ToleranceRate/100))
#define ChargeRateLowThd (ChargeRateMinLimit+ChargeRateToleranceValue)
#define ChargeRateHighThd (ChargeRateMaxLimit-ChargeRateToleranceValue)

typedef enum {
  TempParameter,
  SOCParameter,
  ChargeRateParameter,
  MaxParameter
} ParameterList;

typedef struct {
  ParameterList parameterName;
  double minBreachThreshold;
  double maxBreachThreshold;
  double minWarningThreshold;
  double maxWarningThreshold;
  char paramInput[100];
} ParameterInfo;

void printOnConsole(char msg[]);
void testBattery(ParameterInfo parameterDetails[], double testData[], int isWarningRequired[], int expectedResult);
int isParametersWithinRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[]));
int isParametersWithingWarningRange (ParameterInfo parameterDetails, double inputValue, void (*Fn_Ptr_WarningMsg)(char[]), int isWarningRequired;
int evaluateWarningRange(ParameterInfo parameterDetails, double inputValue);
