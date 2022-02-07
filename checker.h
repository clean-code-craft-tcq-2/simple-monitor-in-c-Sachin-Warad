#define TemperatureMinLimit (float)0
#define TemperatureMaxLimit (float)45
#define SOCMinLimit (float)20
#define SOCMaxLimit (float)80
#define ChargeRateMinLimit (float)0.0
#define ChargeRateMaxLimit (float)0.8

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
