#include "temp_humi_sensor.h"
DHT20 DHT(&Wire);
float temperature =0.0;
float humidity = 0.0;
int dhtStatus = 0;
void setupTempHumi(){
    DHT.begin();
}
void getTempandHumi(){
  switchChanel_4();
  dhtStatus = DHT.read();
//   switch (status)
//   {
//   case DHT20_OK:
//     M5Dial.Lcd.print("OK,\t");
//     break;
//   case DHT20_ERROR_CHECKSUM:
//     M5Dial.Lcd.print("Checksum error,\t");
//     break;
//   case DHT20_ERROR_CONNECT:
//     M5Dial.Lcd.print("Connect error,\t");
//     break;
//   case DHT20_MISSING_BYTES:
//     M5Dial.Lcd.print("Missing bytes,\t");
//     break;
//   case DHT20_ERROR_BYTES_ALL_ZERO:
//     M5Dial.Lcd.print("All bytes read zero");
//     break;
//   case DHT20_ERROR_READ_TIMEOUT:
//     M5Dial.Lcd.print("Read time out");
//     break;
//   case DHT20_ERROR_LASTREAD:
//     M5Dial.Lcd.print("Error read too fast");
//     break;
//   default:
//     M5Dial.Lcd.print("Unknown error,\t");
//     break;
//   }
//   M5Dial.Lcd.setCursor(50,100);
  //  DISPLAY DATA, sensor has only one decimal.
  humidity=DHT.getHumidity();
  temperature=DHT.getTemperature();
}
