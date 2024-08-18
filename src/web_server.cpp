#include "web_server.h"
#include "M5Dial.h"
String wifi_ssid="";
String wifi_pw="";
// char* mqtt_server;
// char* check_wifi;
// char* temp_humi_mqtt;
// char* relay1_mqtt;
// char* relay2_mqtt;
// char* relay3_mqtt;
// char* relay4_mqtt;
// char* ac_measure_mqtt;
// char* temp;
AsyncWebServer server(80);

void create_web(){
    if(!LittleFS.begin()){
        M5Dial.Lcd.setCursor(40,40);
        M5Dial.Lcd.print("failed to mount file system");
    }

    WiFi.mode(WIFI_AP);
    WiFi.softAP("M5Dial_Config", "12345678");
    server.begin();
    // Set up the web server routes
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS,"/web_server.html" ,"text/html");
    });

    server.on("/get", HTTP_POST, [](AsyncWebServerRequest *request) {

    if (request->hasParam("ssid", true)) {
        wifi_ssid = request->getParam("ssid", true)->value();
      //strcpy(wifi_ssid,request->getParam("ssid", true)->value().c_str());
    }
    if (request->hasParam("pass", true)) {
        wifi_pw = request->getParam("pass", true)->value();
      //strcpy(wifi_pw,request->getParam("pass", true)->value().c_str());
    }
    WiFi.mode()
    M5Dial.Lcd.setCursor(40,40);
    M5Dial.Lcd.print("ssid");
    M5Dial.Lcd.setCursor(50,40);
    M5Dial.Lcd.print(wifi_ssid);
    M5Dial.Lcd.setCursor(40,50);
    M5Dial.Lcd.print("pw");    
    M5Dial.Lcd.setCursor(50,50);
    M5Dial.Lcd.print(wifi_pw);
    //String response = "Saved SSID: " + String(wifi_ssid) + "<br>Password: " + String(wifi_pw);
    //request->send(200, "text/html", response + "<br><a href='/'>Go back</a>");
  });
  
    while(wifi_ssid==""){}
}

 