
#include <screen.h>


void update_screen(){
  M5Dial.Lcd.fillCircle(127,127,17,BLACK);

  M5Dial.Lcd.setTextSize(3);
  M5Dial.Lcd.setTextColor(YELLOW);
  M5Dial.Lcd.drawFloat(voltage, 2, 160, 30);
  // if (relay_1_state) 
  // {
  // M5Dial.Lcd.fillCircle(300, 40, 15, GREEN);
  // } 
  // else 
  // {
  // M5Dial.Lcd.fillCircle(300, 40, 15, RED);
  // }

  M5Dial.Lcd.setTextColor(CYAN);
  M5Dial.Lcd.drawFloat(current, 2, 160, 70);
  // if (relay_2_state) 
  // {
  // M5Dial.Lcd.fillCircle(300, 80, 15, GREEN);
  // } 
  // else 
  // {
  // M5Dial.Lcd.fillCircle(300, 80, 15, RED);
  // }

  M5Dial.Lcd.setTextColor(YELLOW);
  M5Dial.Lcd.drawFloat(power, 2, 160, 110);
  // if (relay_3_state) 
  // {
  // M5Dial.Lcd.fillCircle(300, 120, 15, GREEN);
  // }
  // else 
  // {
  // M5Dial.Lcd.fillCircle(300, 120, 15, RED);
  // }

  M5Dial.Lcd.setTextColor(CYAN);
  M5Dial.Lcd.drawFloat(kwh, 2, 160, 150);
  // if (relay_4_state)
  // {
  // M5Dial.Lcd.fillCircle(300, 160, 15, GREEN);
  // }
  // else
  // {
  // M5Dial.Lcd.fillCircle(300, 160, 15, RED);
  // }

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
  M5Dial.Lcd.setTextSize(1.5);
  M5Dial.Lcd.setTextColor(ORANGE);
  M5Dial.Lcd.drawString("ACMeasure", 72, 8);
  M5Dial.Lcd.drawFastHLine(10, 25, 300, WHITE);
  M5Dial.Lcd.setTextColor(YELLOW);
  M5Dial.Lcd.drawString("Voltage(V):", 40, 30);

  M5Dial.Lcd.setTextColor(CYAN);
  M5Dial.Lcd.drawString("Current(mA):", 10, 70);

  M5Dial.Lcd.setTextColor(YELLOW);
  M5Dial.Lcd.drawString("Power(W):", 10, 110);

  M5Dial.Lcd.setTextColor(CYAN);
  M5Dial.Lcd.drawString("KWM:", 10, 150);

  M5Dial.Lcd.setTextSize(2);
  M5Dial.Lcd.setTextColor(RED);
  M5Dial.Lcd.setCursor(18, 190);
  M5Dial.Lcd.printf("Connecting to");
  
  M5Dial.Lcd.setTextColor(WHITE);
  M5Dial.Lcd.setTextSize(1);
  M5Dial.Lcd.drawString("Independent switch    ALL relay", 10 , 220);
}

