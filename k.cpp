[1mdiff --git a/platformio.ini b/platformio.ini[m
[1mindex 9398a5b..1dec60c 100644[m
[1m--- a/platformio.ini[m
[1m+++ b/platformio.ini[m
[36m@@ -25,8 +25,11 @@[m [mlib_deps =[m
 	https://github.com/adafruit/Adafruit_IO_Arduino[m
 	robtillaart/TCA9548@^0.3.0[m
 	https://github.com/RobTillaart/DHT20.git[m
[32m+[m	[32mhttps://github.com/me-no-dev/ESPAsyncWebServer.git[m
[32m+[m
[32m+[m[32mboard_bulid.filesystem = littlefs[m
 upload_speed = 115200[m
 monitor_speed = 115200[m
 board_upload.flash_size = 8MB[m
 board_upload.maximum_size = 8388608[m
[31m-board_bulid.filesystem = spiffs[m
[41m+[m
[1mdiff --git a/src/main.cpp b/src/main.cpp[m
[1mindex 6ae559f..197419f 100644[m
[1m--- a/src/main.cpp[m
[1m+++ b/src/main.cpp[m
[36m@@ -8,6 +8,7 @@[m
 #include "task.h"[m
 #include <WiFi.h>[m
 #include "temp_humi_sensor.h"[m
[32m+[m[32m#include "web_server.h"[m
 // #include "AdafruitConnect.h"[m
 // put function declarations here:[m
 M5GFX display;[m
[36m@@ -26,6 +27,12 @@[m [mvoid setup() {[m
   Wire.begin();[m
   //DHT.begin();[m
   M5Dial.Encoder.write(-1000);[m
[32m+[m[32m  create_web();[m
[32m+[m
[32m+[m[32m  while(WiFi.status() != WL_CONNECTED){[m
[32m+[m
[32m+[m[32m  }[m
[32m+[m[32m  delay(1000);[m
   setupPahub();[m
   setupTempHumi();[m
   switchChanel_2();[m
[36m@@ -34,19 +41,9 @@[m [mvoid setup() {[m
   setupRelay();[m
   ALLrelayState=OFF_ALL;[m
   controlALL();[m
[31m-  WiFi.mode(WIFI_STA);[m
[31m-  WiFi.begin(ssid, password);[m
   setupMQTT();[m
[31m-  init_screen();[m
[31m-  while (WiFi.status() != WL_CONNECTED){[m
[31m-    M5Dial.Lcd.setCursor(158, 106);[m
[31m-    M5Dial.Lcd.setTextSize(1);[m
[31m-    M5Dial.Lcd.printf("Connecting...");[m
[31m-  }[m
[31m-  while(WiFiConnectFlag!=true && MQTTConnectFlag!=true){[m
[31m-    checkWiFiStatus();[m
[31m-    checkConnectMQTT(); [m
[31m-  }[m
[32m+[m[32m   init_screen();[m
[32m+[m
   updateAC.attach_ms(211,taskUpdateACinfor);[m
   tickerTempHumi.attach_ms(2002,getTempandHumi);[m
   updatescreen.attach_ms(1023,taskUpdateScreen);[m
[1mdiff --git a/src/screen.cpp b/src/screen.cpp[m
[1mindex 984004f..48731a8 100644[m
[1m--- a/src/screen.cpp[m
[1m+++ b/src/screen.cpp[m
[36m@@ -74,7 +74,7 @@[m [mvoid update_screen(){[m
   M5Dial.Lcd.printf("Wifi:");[m
   M5Dial.Lcd.setTextSize(1);[m
   M5Dial.Lcd.setCursor(158, 110);[m
[31m-  M5Dial.Lcd.printf(ssid);[m
[32m+[m[32m  M5Dial.Lcd.print(ssid);[m
   if (MQTTConnectFlag==true)[m
   {[m
       M5Dial.Lcd.setTextSize(1.5);[m
[36m@@ -111,7 +111,7 @@[m [mvoid update_screen(){[m
 [m
 void init_screen() [m
 {[m
[31m-  M5Dial.Lcd.fillCircle(125,125,200,BLACK);[m
[32m+[m[32m  M5Dial.Lcd.fillCircle(0,0,400,BLACK);[m
   M5Dial.Lcd.setTextSize(1.5);[m
   M5Dial.Lcd.setTextColor(ORANGE);[m
   M5Dial.Lcd.drawString("ACMeasure", 75, 8);[m
[1mdiff --git a/src/screen.h b/src/screen.h[m
[1mindex 4528b29..f8f9583 100644[m
[1m--- a/src/screen.h[m
[1m+++ b/src/screen.h[m
[36m@@ -3,5 +3,6 @@[m
 #include "control_relays.h"[m
 #include "wifi_mqtt.h"[m
 #include "temp_humi_sensor.h"[m
[32m+[m[32m#include "web_server.h"[m
 void init_screen();[m
 void update_screen();[m
\ No newline at end of file[m
[1mdiff --git a/src/task.cpp b/src/task.cpp[m
[1mindex 149a430..4608e93 100644[m
[1m--- a/src/task.cpp[m
[1m+++ b/src/task.cpp[m
[36m@@ -175,7 +175,7 @@[m [mvoid taskClientPublish()[m
   temp_humi_mes += ";";[m
 [m
   counterSend ++;[m
[31m-  if (counterSend == 5)[m
[32m+[m[32m  if (counterSend == 1)[m
   {[m
     clientPublish(ac_measure_mqtt, mes.c_str());[m
     mes = "";[m
[1mdiff --git a/src/web_server.cpp b/src/web_server.cpp[m
[1mnew file mode 100644[m
[1mindex 0000000..6da59f9[m
[1m--- /dev/null[m
[1m+++ b/src/web_server.cpp[m
[36m@@ -0,0 +1,119 @@[m
[32m+[m[32m#include "web_server.h"[m
[32m+[m
[32m+[m[32mString ssid = "";[m
[32m+[m[32mString password = "";[m
[32m+[m
[32m+[m[32mString MQTT_user = "";[m
[32m+[m[32mString MQTT_pass = "";[m
[32m+[m
[32m+[m[32mWiFiClient espClient;[m
[32m+[m[32mPubSubClient client(espClient);[m
[32m+[m[32mAsyncWebServer server(80);[m
[32m+[m
[32m+[m[32mbool connectToWiFi(const char* ssid, const char* password) {[m
[32m+[m[32m  WiFi.begin(ssid, password);[m
[32m+[m[32m  M5Dial.Lcd.setCursor(40,40);[m
[32m+[m[32m  M5Dial.Lcd.print("Connecting to Wi-Fi...");[m
[32m+[m[41m  [m
[32m+[m[32m  int attempts = 0;[m
[32m+[m[32m  while (WiFi.status() != WL_CONNECTED && attempts < 15) {[m
[32m+[m[32m    WiFi.begin(ssid, password);[m
[32m+[m[32m    delay(300);[m
[32m+[m[32m    M5Dial.Lcd.setCursor(30,50+10*attempts);[m
[32m+[m[32m    M5Dial.Lcd.print(attempts);[m
[32m+[m[32m    attempts++;[m
[32m+[m[32m  }[m
[32m+[m[32m   M5Dial.Lcd.setCursor(50,50);[m
[32m+[m[32m   M5Dial.Lcd.print(WiFi.status() == WL_CONNECTED);[m
[32m+[m[32m    M5Dial.Lcd.fillCircle(125,125,200,BLACK);[m
[32m+[m[32m  return (WiFi.status() == WL_CONNECTED);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mbool connectMQTT(const char* MQTTuser, const char* MQTTpass){[m
[32m+[m[32m    String clientID = "M5Stack-";[m
[32m+[m[32m    clientID += String(random(0xffff), HEX);[m
[32m+[m[32m    bool result = client.connect(clientID.c_str(), MQTTuser, MQTTpass);[m
[32m+[m[32mreturn result;[m
[32m+[m[32m}[m
[32m+[m[32mvoid create_web(){[m
[32m+[m[32m    if (!LittleFS.begin()) {[m
[32m+[m[32m    Serial.println("An error has occurred while mounting LittleFS");[m
[32m+[m[32m    return;[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  // Start Wi-Fi in AP mode[m
[32m+[m[32m  WiFi.mode(WIFI_AP_STA);[m
[32m+[m[32m  WiFi.softAP("M5Dial_Config", "12345678");[m
[32m+[m
[32m+[m[32m  // Print the IP Address[m
[32m+[m[32m  Serial.println(WiFi.softAPIP());[m
[32m+[m[32m  server.begin();[m
[32m+[m
[32m+[m
[32m+[m[32m  // Serve the CSS file[m
[32m+[m[32m  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/style.css", "text/css");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/MQTTstyle.css", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/MQTTstyle.css", "text/css");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/asset/M5_Dial.png", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/asset/M5_Dial.png", "image/png");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/asset/LostConnect.png", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/asset/LostConnect.png", "image/png");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/asset/MQTT.png", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/asset/MQTT.png", "image/png");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/asset/background.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/asset/background.jpg", "image/jpg");[m
[32m+[m[32m  });[m
[32m+[m[32m  server.on("/asset/MQTTbackground.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    request->send(LittleFS, "/asset/MQTTbackground.jpg", "image/jpg");[m
[32m+[m[32m  });[m
[32m+[m
[32m+[m[32m  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){[m
[32m+[m[32m    request->send(LittleFS, "/index.html", "text/html");[m
[32m+[m[32m  });[m
[32m+[m
[32m+[m[32m  // Handle the form submission and connect to Wi-Fi[m
[32m+[m[32m  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m    // Get the submitted SSID and password[m
[32m+[m[32m    if (request->hasParam("ssid", true) && request->hasParam("password", true)) {[m
[32m+[m[32m      ssid = request->getParam("ssid", true)->value();[m
[32m+[m[32m      password = request->getParam("password", true)->value();[m
[32m+[m[32m        M5Dial.Lcd.setCursor(70,60);[m
[32m+[m[32m        M5Dial.Lcd.print(ssid);[m
[32m+[m[32m        M5Dial.Lcd.setCursor(70,70);[m
[32m+[m[32m        M5Dial.Lcd.print(password);[m
[32m+[m[32m      // Attempt to connect to Wi-Fi[m
[32m+[m[32m      if (connectToWiFi(ssid.c_str(), password.c_str()) == true) {[m
[32m+[m[32m        // request->send(200, "text/html", "<html><body><h1>Connected Successfully!</h1></body></html>");[m
[32m+[m[32m           request->send(LittleFS, "/MQTT.html", "text/html");[m
[32m+[m[32m           server.on("/submit1", HTTP_POST, [](AsyncWebServerRequest *request) {[m
[32m+[m[32m                MQTT_user = request->getParam("MQTTuser", true)->value();[m
[32m+[m[32m                MQTT_pass = request->getParam("MQTTpass", true)->value();[m
[32m+[m[32m                // M5Dial.Lcd.setCursor(120,60);[m
[32m+[m[32m                // M5Dial.Lcd.print("id:" + MQTT_user);[m
[32m+[m[32m                // M5Dial.Lcd.setCursor(120,70);[m
[32m+[m[32m                // M5Dial.Lcd.print("pw" + MQTT_pass);[m
[32m+[m[32m                if (connectMQTT(MQTT_user.c_str(), MQTT_pass.c_str()) == true) {[m
[32m+[m[32m                    request->send(200, "text/html", "<html><body><h1>Connected Successfully!</h1></body></html>");[m
[32m+[m[32m                }[m
[32m+[m[32m                else{[m
[32m+[m[32m                    request->send(200, "text/html", "<html><body><h1>Failed to Connect. Please try again.</h1><a href='/'>Back</a></body></html>");[m
[32m+[m[32m                }[m
[32m+[m[32m           });[m
[32m+[m[32m      } else {[m
[32m+[m[32m        // request->send(200, "text/html", "<html><body><h1>Failed to Connect. Please try again.</h1><a href='/'>Back</a></body></html>");[m
[32m+[m[32m           WiFi.disconnect();[m
[32m+[m[32m           WiFi._setStatus(WL_CONNECT_FAILED);[m
[32m+[m[32m           request->send(LittleFS, "/ErrorPage.html", "text/html");[m
[32m+[m
[32m+[m[32m      }[m
[32m+[m[32m    } else {[m
[32m+[m[32m      request->send(200, "text/html", "<html><body><h1>Missing SSID or Password. Please try again.</h1><a href='/'>Back</a></body></html>");[m
[32m+[m[32m    }[m
[32m+[m[32m  });[m
[32m+[m[32m}[m
\ No newline at end of file[m
[1mdiff --git a/src/web_server.h b/src/web_server.h[m
[1mnew file mode 100644[m
[1mindex 0000000..d08a92b[m
[1m--- /dev/null[m
[1m+++ b/src/web_server.h[m
[36m@@ -0,0 +1,16 @@[m
[32m+[m[32m#include <ESPAsyncWebServer.h>[m
[32m+[m[32m#include <LittleFS.h>[m
[32m+[m[32m#include "M5Dial.h"[m
[32m+[m[32m#include <WiFi.h>[m
[32m+[m[32m#include <String.h>[m
[32m+[m[32m#include <PubSubClient.h>[m
[32m+[m[32mextern String ssid;[m
[32m+[m[32mextern String password;[m
[32m+[m
[32m+[m[32mextern String MQTT_user;[m
[32m+[m[32mextern String MQTT_pass;[m
[32m+[m
[32m+[m[32mextern WiFiClient espClient;[m
[32m+[m[32mextern PubSubClient client;[m
[32m+[m
[32m+[m[32mvoid create_web();[m
\ No newline at end of file[m
[1mdiff --git a/src/wifi_mqtt.cpp b/src/wifi_mqtt.cpp[m
[1mindex b332ba0..bbdac6f 100644[m
[1m--- a/src/wifi_mqtt.cpp[m
[1m+++ b/src/wifi_mqtt.cpp[m
[36m@@ -1,10 +1,7 @@[m
 #include <wifi_mqtt.h>[m
 [m
[31m-#define MQTT_user  "kienpham"[m
[31m-#define MQTT_pass  ""[m
 [m
[31m-WiFiClient espClient;[m
[31m-PubSubClient client(espClient);[m
[32m+[m
 [m
 char* mqtt_topic_sended;[m
 byte* mqtt_arrived_mess;[m
[36m@@ -12,11 +9,8 @@[m [mbyte* mqtt_arrived_mess;[m
 bool WiFiConnectFlag = false;[m
 bool MQTTConnectFlag = false;[m
 [m
[31m-const char* ssid        = "ACLAB";[m
[31m-const char* password    = "ACLAB2023";[m
[31m-// const char* mqtt_server = "172.28.182.87";[m
[31m-const char* mqtt_server = "io.adafruit.com"[m
[31m-;[m
[32m+[m
[32m+[m[32mconst char* mqtt_server = "io.adafruit.com";[m
 [m
 void checkWiFiStatus()[m
 {[m
[36m@@ -144,7 +138,7 @@[m [mvoid checkConnectMQTT()[m
   {[m
     String clientID = "M5Stack-";[m
     clientID += String(random(0xffff), HEX);[m
[31m-    bool result = client.connect(clientID.c_str(), MQTT_user, MQTT_pass);[m
[32m+[m[32m    bool result = client.connect(clientID.c_str(), MQTT_user.c_str(), MQTT_pass.c_str());[m
     if (result)[m
     {[m
       MQTTConnectFlag = true;[m
[1mdiff --git a/src/wifi_mqtt.h b/src/wifi_mqtt.h[m
[1mindex fa85eeb..70cd82f 100644[m
[1m--- a/src/wifi_mqtt.h[m
[1m+++ b/src/wifi_mqtt.h[m
[36m@@ -1,8 +1,9 @@[m
[31m-#include <WiFi.h>[m
 #include <PubSubClient.h>[m
 #include <M5Dial.h>[m
 #include <control_relays.h>[m
 #include <pahub.h>[m
[32m+[m[32m#include "web_server.h"[m
[32m+[m
 #define check_wifi "kienpham/feeds/m5stack"[m
 #define temp_humi_mqtt "kienpham/feeds/topic0"[m
 #define relay1_mqtt "kienpham/feeds/topic1"[m
[36m@@ -11,8 +12,7 @@[m
 #define relay4_mqtt "kienpham/feeds/topic4"[m
 #define ac_measure_mqtt "kienpham/feeds/topic5"[m
 #define temp "kienpham/feeds/topic6"[m
[31m-extern const char* ssid;[m
[31m-extern const char* password;[m
[32m+[m
 extern const char* mqtt_server;[m
 [m
 extern char* mqtt_topic_sended;[m
