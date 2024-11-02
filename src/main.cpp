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
#include "web_server.h"
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
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  //DHT.begin();
  M5Dial.Encoder.write(-1000);

  setupMQTT();  //setup MQTT server and callback function. Must be defined before connect
  create_web(); //function create web server
  
  while((WiFi.status() != WL_CONNECTED) || (MQTTConnectFlag == false)){
    handleDNSRequests();
    delay(100);
  }  //loop wait until connect wifi and mqtt
  delay(1000);
  turn_off_dns();
  switch_wifi_mode();   //turn off M5 dial access point and close web server
  subcribeMQTT();       //subcribe to topics
  setupPahub();
  delay(100);
  setupTempHumi();
  delay(100);
  switchChanel_2();
  setupACsensor();
  delay(100);
  switchChanel_3();
  setupRelay();
  delay(100);
  ALLrelayState=OFF_ALL;
  controlALL();
  
  init_screen();

  updateAC.attach_ms(211,taskUpdateACinfor);
  tickerTempHumi.attach_ms(2002,getTempandHumi);
  updatescreen.attach_ms(1023,taskUpdateScreen);
  tickercontrolRelay.attach_ms(53,taskControlRelay);
  tickerMQTTpublish.attach_ms(60001, taskClientPublish);

  clientPublish("kienpham/feeds/topic0","0");
  clientPublish("kienpham/feeds/topic1","0");
  clientPublish("kienpham/feeds/topic2","0");
  clientPublish("kienpham/feeds/topic3","0");
  clientPublish("kienpham/feeds/topic4","0");

}
void loop() {
  //put your main code here, to run repeatedly:
    if (WiFi.status() == WL_CONNECTED)
  {
    checkWiFiStatus();
    checkConnectMQTT();
    clientLoop(); 
  }
}
