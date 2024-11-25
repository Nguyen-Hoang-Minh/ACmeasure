#include "DHT20.h"
#include "Wire.h"
#include "pahub.h"
#include "utils.h"

#define MAX_SAMPLES 250
extern float temperature;
extern float humidity;
extern int dhtStatus;
extern float data_samples[MAX_SAMPLES][3];
extern int sample_index; 
extern bool mutex_lock;
void setupTempHumi();
void getTempandHumi();