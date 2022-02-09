#define TemperatureMinLimit 0
#define TemperatureMaxLimit 45
#define SOCMinLimit 20
#define SOCMaxLimit 80
#define ChargeRateMinLimit 0.0
#define ChargeRateMaxLimit 0.8

typedef enum {
  TempParameter,
  SOCParameter,
  ChargeRateParameter,
  MaxParameter
} ParameterList;

typedef struct {
  ParameterList parameterName;
  double minThreshold;
  double maxThreshold;
  char msgInput[100];
} ParameterInfo;

void printOnConsole(char msg[]);
int isParametersWithinRange (int i, ParameterInfo parameterDetails[], double inputValue, void (*Fn_Ptr_WarningMsg)(char[]));
void testBattery(double parameterDetails[], double testData[], int expectedResult);
// int isParametersWithinRange (ParameterList parametersName, double inputValue);
// void testBattery(double testData[], int expectedResult);
