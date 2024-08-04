#include <screen.h>


void update_screen(){
  // M5Dial.Lcd.fillCircle(127,127,90,BLACK);
  M5Dial.Lcd.setTextSize(1.5);
  M5Dial.Lcd.setTextColor(WHITE);
  M5Dial.Lcd.fillRoundRect(82,58,71,21,10,TFT_DARKCYAN);
  M5Dial.Lcd.drawFloat(round(voltage*100)/100, 2, 90, 58);
  
  M5Dial.Lcd.fillRoundRect(82,106,71,21,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(WHITE);
  M5Dial.Lcd.drawFloat(round(current*100)/100, 2, 90, 108);

  M5Dial.Lcd.fillRoundRect(82,154,71,21,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(WHITE);
  M5Dial.Lcd.drawFloat(round(power*100)/100, 2, 90, 157);

  M5Dial.Lcd.fillRoundRect(82,201,71,21,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(WHITE);
  M5Dial.Lcd.drawFloat(round(kwh*100)/100, 2, 90, 205);
  
  if(relay_1_state==ON_SIGNAL){
      M5Dial.Lcd.fillCircle(62,58,10,GREEN);
  }
  else if(relay_1_state==OFF_SIGNAL){
      M5Dial.Lcd.fillCircle(62,58,10,RED);
  }

  if(relay_2_state==ON_SIGNAL){
      M5Dial.Lcd.fillCircle(62,106,10,RED);
  }
  else if(relay_2_state==OFF_SIGNAL){
      M5Dial.Lcd.fillCircle(62,106,10,GREEN);
  }

  if(relay_3_state==ON_SIGNAL){
      M5Dial.Lcd.fillCircle(62,154,10,RED);
  }
  else if(relay_3_state==OFF_SIGNAL){
      M5Dial.Lcd.fillCircle(62,154,10,GREEN);
  }

  if(relay_4_state==ON_SIGNAL){
      M5Dial.Lcd.fillCircle(62,202,10,RED);
  }
  else if(relay_4_state==OFF_SIGNAL){
      M5Dial.Lcd.fillCircle(62,202,10,GREEN);
  }

  M5Dial.Lcd.fillRect(150,58,68,255,BLACK);

  // if (WiFiConnectFlag)
  // {
  // if (MQTTConnectFlag)
  // {
  //     M5Dial.Lcd.fillRect(0, 190, 320, 30, BLACK);
  //     M5Dial.Lcd.setTextSize(2);
  //     M5Dial.Lcd.setTextColor(PINK);
  //     M5Dial.Lcd.setCursor(0, 190);
  //     M5Dial.Lcd.printf("Connected to MQTT_Server", mqtt_server);
  // } 
  // else
  // {
  //     M5Dial.Lcd.fillRect(0, 190, 320, 30, BLACK);
  //     M5Dial.Lcd.setTextSize(2);
  //     M5Dial.Lcd.setTextColor(GREEN);
  //     M5Dial.Lcd.setCursor(0, 190);
  //     M5Dial.Lcd.printf("Connected to %s", ssid);
  // }
  // }
  // else
  // {
  // Serial.print("false");
  // M5Dial.Lcd.fillRect(0, 190, 320, 30, BLACK);
  // M5Dial.Lcd.setTextSize(2);
  // M5Dial.Lcd.setTextColor(RED);
  // M5Dial.Lcd.setCursor(0, 190);
  // M5Dial.Lcd.printf("Connecting to %s", ssid);
  // }
}

void init_screen() 
{
  M5Dial.Lcd.fillCircle(125,125,200,BLACK);
  M5Dial.Lcd.setTextSize(1.5);
  M5Dial.Lcd.setTextColor(ORANGE);
  M5Dial.Lcd.drawString("ACMeasure", 75, 8);
  M5Dial.Lcd.drawFastHLine(0, 25, 300, WHITE);

 M5Dial.Lcd.fillRoundRect(82,37,68,43,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(0xFC60);
  M5Dial.Lcd.drawString("Vol(V)", 90, 40);

  M5Dial.Lcd.fillRoundRect(82,85,68,43,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(0xFC60);
  M5Dial.Lcd.drawString("Cur(mA)", 88, 88);

  M5Dial.Lcd.fillRoundRect(82,133,68,43,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(0xFC60);
  M5Dial.Lcd.drawString("Pow(W)", 90, 136);

  M5Dial.Lcd.fillRoundRect(82,181,68,43,10,TFT_DARKCYAN);
  M5Dial.Lcd.setTextColor(0xFC60);
  M5Dial.Lcd.drawString("KWM", 102, 184);

  M5Dial.Lcd.fillCircle(62,58,10,RED);
  M5Dial.Lcd.fillCircle(62,106,10,RED);
  M5Dial.Lcd.fillCircle(62,154,10,RED);
  M5Dial.Lcd.fillCircle(62,202,10,RED);

  
  // M5Dial.Lcd.setTextSize(2);
  // M5Dial.Lcd.setTextColor(RED);
  // M5Dial.Lcd.setCursor(18, 190);
  // M5Dial.Lcd.printf("Connecting to");
  
  // M5Dial.Lcd.setTextColor(WHITE);
  // M5Dial.Lcd.setTextSize(1);
  // M5Dial.Lcd.drawString("Independent switch    ALL relay", 10 , 220);
}

