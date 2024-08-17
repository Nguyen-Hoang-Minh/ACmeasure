#include <Arduino.h>
#include "M5Dial.h"
#include <HWCDC.h>
#include "USB.h"
#include "USBMSC.h"
#include "screen.h"
#include "Ticker.h"
#include "task.h"
#include <WiFi.h>
#include "temp_humi_sensor.h"
// #include "AdafruitConnect.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);

Ticker updatescreen;
Ticker updateAC;
Ticker tickercontrolRelay;
Ticker tickerMQTTpublish;
Ticker tickerTempHumi;
void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  //DHT.begin();
  M5Dial.Encoder.write(-1000);
  setupPahub();
  setupTempHumi();
  switchChanel_2();
  setupACsensor();
  switchChanel_3();
  setupRelay();
  ALLrelayState=OFF_ALL;
  controlALL();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  setupMQTT();
  init_screen();
  while (WiFi.status() != WL_CONNECTED){
    M5Dial.Lcd.setCursor(158, 106);
    M5Dial.Lcd.setTextSize(1);
    M5Dial.Lcd.printf("Connecting...");
  }
  while(WiFiConnectFlag!=true && MQTTConnectFlag!=true){
    checkWiFiStatus();
    checkConnectMQTT(); 
  }
  updateAC.attach_ms(211,taskUpdateACinfor);
  tickerTempHumi.attach_ms(2002,getTempandHumi);
  updatescreen.attach_ms(1023,taskUpdateScreen);
  tickercontrolRelay.attach_ms(53,taskControlRelay);
  tickerMQTTpublish.attach_ms(5001, taskClientPublish);

  clientPublish("kienpham/feeds/topic0","0");
  clientPublish("kienpham/feeds/topic1","0");
  clientPublish("kienpham/feeds/topic2","0");
  clientPublish("kienpham/feeds/topic3","0");
  clientPublish("kienpham/feeds/topic4","0");

}
M5Dial
void loop() {
  //put your main code here, to run repeatedly:
    if (WiFi.status() == WL_CONNECTED)
  {
    checkWiFiStatus();
    checkConnectMQTT();
    clientLoop(); 
  }
  //  READ DATA
  //Serial.print("DHT20, \t");
  
}
