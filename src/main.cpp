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
#include "Preferences.h"
#include "ESPAsyncWebServer.h"
// #include "AdafruitConnect.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);

Ticker updatescreen;
Ticker updateAC;
Ticker tickercontrolRelay;
Ticker tickerMQTTpublish;
Ticker tickerTempHumi;

AsyncWebServer server(80);
Preferences preferences;

String wf_ssid;
String wf_pw;
void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  //DHT.begin();
  M5Dial.Encoder.write(-1000);
  // setupPahub();
  // setupTempHumi();
  // switchChanel_2();
  // setupACsensor();
  // switchChanel_3();
  // setupRelay();
  // ALLrelayState=OFF_ALL;
  // controlALL();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("M5Dial_Config", "12345678");
  server.begin();
  // Set up the web server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "<form action='/get' method='post'><label>SSID:</label><input type='text' name='ssid'><br><label>Password:</label><input type='password' name='pass'><br><input type='submit' value='Save'></form>");
  });

    server.on("/get", HTTP_POST, [](AsyncWebServerRequest *request) {

    if (request->hasParam("ssid", true)) {
      wf_ssid = request->getParam("ssid", true)->value();
    }
    if (request->hasParam("pass", true)) {
      wf_pw = request->getParam("pass", true)->value();
    }
    
    // Store WiFi credentials in Preferences
    // preferences.begin("WiFiCreds", false);
    // preferences.putString("ssid", ssid);
    // preferences.putString("pass", );
    // preferences.end();
    M5Dial.Lcd.setCursor(40,40);
    M5Dial.Lcd.print(wf_ssid);
    M5Dial.Lcd.setCursor(40,48);
    M5Dial.Lcd.print(wf_pw);
    String response = "Saved SSID: " + wf_ssid + "<br>Password: " + wf_pw;
    request->send(200, "text/html", response + "<br><a href='/'>Go back</a>");
  });
  
    while(wf_ssid==""){
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(wf_ssid, wf_pw);
  // setupMQTT();
  // init_screen();
  // while (WiFi.status() != WL_CONNECTED){
  //   M5Dial.Lcd.setCursor(158, 106);
  //   M5Dial.Lcd.setTextSize(1);
  //   M5Dial.Lcd.printf("Connecting...");
  // }
  // while(WiFiConnectFlag!=true && MQTTConnectFlag!=true){
  //   checkWiFiStatus();
  //   checkConnectMQTT(); 
  // }
  // updateAC.attach_ms(211,taskUpdateACinfor);
  // tickerTempHumi.attach_ms(2002,getTempandHumi);
  // updatescreen.attach_ms(1023,taskUpdateScreen);
  // tickercontrolRelay.attach_ms(53,taskControlRelay);
  // tickerMQTTpublish.attach_ms(5001, taskClientPublish);

  // clientPublish("kienpham/feeds/topic0","0");
  // clientPublish("kienpham/feeds/topic1","0");
  // clientPublish("kienpham/feeds/topic2","0");
  // clientPublish("kienpham/feeds/topic3","0");
  // clientPublish("kienpham/feeds/topic4","0");

}

void loop() {
  //put your main code here, to run repeatedly:
  //   if (WiFi.status() == WL_CONNECTED)
  // {
  //   checkWiFiStatus();
  //   checkConnectMQTT();
  //   clientLoop(); 
  // }
  if(WiFi.status() == WL_CONNECTED)
    {
      M5Dial.Speaker.tone(3000, 5000);
    }
}
