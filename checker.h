#define TemperatureMinLimit 0
#define TemperatureMaxLimit 45
#definr SOCMinLimit 20
#define SOCMaxLimit 80
#define ChargeRateMinLimit 0.0
#define ChargeRateMaxLimit 0.8

typedef enum {
  TempParameter,
  SOCParameter,
  ChargeRateParameter,
  MaxParameter
} parameterList;

typedef struct {
  parameterList parameterName,
  int minThreshold,
  int maxThreshold,
  char msgInput[100]
} parameterInfo;
