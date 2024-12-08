#include "temp_humi_sensor.h"
DHT20 DHT(&Wire);
float temperature =0.0;
float humidity = 0.0;
int dhtStatus = 0;
float data_samples[MAX_SAMPLES][3];
int sample_index = 0;
bool mutex_lock = false;



void setupTempHumi(){
    DHT.begin();
}
void getTempandHumi(){
  switchChanel_4();
  dhtStatus = DHT.read();
  switch (dhtStatus)
  {
  case DHT20_OK:
    Serial.println("OK,\t");
    break;
  case DHT20_ERROR_CHECKSUM:
    Serial.println("Checksum error,\t");
    break;
  case DHT20_ERROR_CONNECT:
    Serial.println("Connect error,\t");
    break;
  case DHT20_MISSING_BYTES:
    Serial.println("Missing bytes,\t");
    break;
  case DHT20_ERROR_BYTES_ALL_ZERO:
    Serial.println("All bytes read zero");
    break;
  case DHT20_ERROR_READ_TIMEOUT:
    Serial.println("Read time out");
    break;
  case DHT20_ERROR_LASTREAD:
    Serial.println("Error read too fast");
    break;
  default:
    Serial.println("Unknown error,\t");
    break;
  }
  M5Dial.Lcd.setCursor(50,100);
  //  DISPLAY DATA, sensor has only one decimal.
  humidity=DHT.getHumidity();
  temperature=DHT.getTemperature();
  

  if(mutex_lock == false){        //error might be come from this condition
    mutex_lock = true;
    //if(temperature!=0 && humidity!=0){}
    data_samples[sample_index%MAX_SAMPLES][0] = temperature;
    data_samples[sample_index%MAX_SAMPLES][1] = humidity;
    data_samples[sample_index%MAX_SAMPLES][2] = fareheit_to_celcius(heat_index(temperature, humidity));
    // Serial.println(temperature);
    // Serial.println(humidity); 
    // Serial.println(fareheit_to_celcius(heat_index(temperature, humidity)));
    sample_index++;
    mutex_lock = false;
  }
}
