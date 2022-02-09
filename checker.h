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

void printOnConsole(const char msg[]);
int isParametersWithinRange (ParameterList parametersName, double inputValue);
void testBattery(double testData[], int expectedResult);
