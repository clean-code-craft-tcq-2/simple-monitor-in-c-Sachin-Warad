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
  float minThreshold;
  float maxThreshold;
  char msgInput[100];
} ParameterInfo;

void printOnConsole(char msg[]);
int isParametersWithinRange (ParameterList parametersName, float inputValue);
void testBattery(float testData[], int expectedResult);
