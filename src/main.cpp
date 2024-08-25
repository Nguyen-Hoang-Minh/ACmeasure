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
//#include "web_server.h"
// #include "AdafruitConnect.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);
AsyncWebServer server(80);

Ticker updatescreen;
Ticker updateAC;
Ticker tickercontrolRelay;
Ticker tickerMQTTpublish;
Ticker tickerTempHumi;

String wifiSSID;
String wifiPassword;

// Function to connect to the provided Wi-Fi
bool connectToWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  M5Dial.Lcd.setCursor(40,40);
  M5Dial.Lcd.print("Connecting to Wi-Fi...");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    WiFi.begin(ssid, password);
    delay(300);
    M5Dial.Lcd.setCursor(30,50+10*attempts);
    M5Dial.Lcd.print(attempts);
    attempts++;
  }

  return (WiFi.status() == WL_CONNECTED);
}

void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  M5Dial.Encoder.write(-1000);
  //setupPahub();
  //setupTempHumi();
  //switchChanel_2();
  //setupACsensor();
  //switchChanel_3();
  //setupRelay();
  //ALLrelayState=OFF_ALL;
  //controlALL();
  //M5Dial.Lcd.setCursor(40,40);
  //M5Dial.Lcd.print("creating web");
  //M5Dial.Lcd.setCursor(40,50);
  //create_web();
  //setupMQTT();
  //init_screen();
  //WiFi.mode(WIFI_STA);
  //WiFi.begin(wifi_ssid,wifi_pw);
  //while (WiFi.status() != WL_CONNECTED){
  //  M5Dial.Lcd.setCursor(158, 106);
  //  M5Dial.Lcd.setTextSize(1);
  //  M5Dial.Lcd.printf("Connecting...");
  //}
  //while(WiFiConnectFlag!=true && MQTTConnectFlag!=true){
  //  checkWiFiStatus();
  //  checkConnectMQTT(); 
  //}
  //updateAC.attach_ms(211,taskUpdateACinfor);
  //tickerTempHumi.attach_ms(2002,getTempandHumi);
  //updatescreen.attach_ms(1023,taskUpdateScreen);
  //tickercontrolRelay.attach_ms(53,taskControlRelay);
  //tickerMQTTpublish.attach_ms(5001, taskClientPublish);

  //clientPublish("kienpham/feeds/topic0","0");
  //clientPublish("kienpham/feeds/topic1","0");
  //clientPublish("kienpham/feeds/topic2","0");
  //clientPublish("kienpham/feeds/topic3","0");
  //clientPublish("kienpham/feeds/topic4","0");

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }

  // Start Wi-Fi in AP mode
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("M5Dial_Config", "12345678");

  // Print the IP Address
  Serial.println(WiFi.softAPIP());
  server.begin();


  // Serve the CSS file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
  });

  // Serve the main configuration page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><head><link rel='stylesheet' href='/style.css'></head><body>";
    html += "<h1>Configure Wi-Fi</h1>";
    html += "<form action='/submit' method='post'>";
    html += "SSID: <input type='text' name='ssid'><br>";
    html += "Password: <input type='password' name='password'><br>";
    html += "<input type='submit' value='Connect'>";
    html += "</form>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Handle the form submission and connect to Wi-Fi
  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Get the submitted SSID and password
    M5Dial.Lcd.setCursor(70,60);
    M5Dial.Lcd.print("id:" + request->getParam("ssid", true)->value());
    M5Dial.Lcd.setCursor(70,70);
    M5Dial.Lcd.print("pw" + request->getParam("password", true)->value());
    if (request->hasParam("ssid", true) && request->hasParam("password", true)) {
      wifiSSID = request->getParam("ssid", true)->value();
      wifiPassword = request->getParam("password", true)->value();

      // Attempt to connect to Wi-Fi
      if (connectToWiFi(wifiSSID.c_str(), wifiPassword.c_str())) {
        request->send(200, "text/html", "<html><body><h1>Connected Successfully!</h1></body></html>");
      } else {
        request->send(200, "text/html", "<html><body><h1>Failed to Connect. Please try again.</h1><a href='/'>Back</a></body></html>");
      }
    } else {
      request->send(200, "text/html", "<html><body><h1>Missing SSID or Password. Please try again.</h1><a href='/'>Back</a></body></html>");
    }
  });

  // Start the server

}

void loop() {
  //put your main code here, to run repeatedly:
    if (WiFi.status() == WL_CONNECTED)
  {
    //checkWiFiStatus();
    //checkConnectMQTT();
    //clientLoop(); 
    M5Dial.Speaker.tone(6000,10);
  }
}
