#include "DHT20.h"
#include "Wire.h"
#include "pahub.h"

extern float temperature;
extern float humidity;
extern int dhtStatus;
void setupTempHumi();
void getTempandHumi();