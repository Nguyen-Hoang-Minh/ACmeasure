#include "web_server.h"

String ssid = "";
String password = "";


AsyncWebServer server(80);

bool connectToWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  M5Dial.Lcd.setCursor(40,40);
  M5Dial.Lcd.print("Connecting to Wi-Fi...");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 15) {
    WiFi.begin(ssid, password);
    delay(300);
    M5Dial.Lcd.setCursor(30,50+10*attempts);
    M5Dial.Lcd.print(attempts);
    attempts++;
  }
   M5Dial.Lcd.setCursor(50,50);
   M5Dial.Lcd.print(WiFi.status() == WL_CONNECTED);
    M5Dial.Lcd.fillCircle(125,125,200,BLACK);
  return (WiFi.status() == WL_CONNECTED);
}

void create_web(){
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
  server.on("/MQTTstyle.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/MQTTstyle.css", "text/css");
  });
  server.on("/asset/M5_Dial.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/asset/M5_Dial.png", "image/png");
  });
  server.on("/asset/LostConnect.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/asset/LostConnect.png", "image/png");
  });
  server.on("/asset/MQTT.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/asset/MQTT.png", "image/png");
  });
  server.on("/asset/background.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/asset/background.jpg", "image/jpg");
  });
  server.on("/asset/MQTTbackground.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/asset/MQTTbackground.jpg", "image/jpg");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Handle the form submission and connect to Wi-Fi
  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Get the submitted SSID and password
    if (request->hasParam("ssid", true) && request->hasParam("password", true)) {

      ssid = request->getParam("ssid", true)->value();
      password = request->getParam("password", true)->value();
        M5Dial.Lcd.setCursor(70,60);
        M5Dial.Lcd.print(ssid);
        M5Dial.Lcd.setCursor(70,70);
        M5Dial.Lcd.print(password);
      // Attempt to connect to Wi-Fi
      if (connectToWiFi(ssid.c_str(), password.c_str()) == true) {
        // request->send(200, "text/html", "<html><body><h1>Connected Successfully!</h1></body></html>");
           request->send(LittleFS, "/MQTT.html", "text/html");
           server.on("/submit1", HTTP_POST, [](AsyncWebServerRequest *request) {
                M5Dial.Lcd.setCursor(120,60);
                M5Dial.Lcd.print("id:" + request->getParam("MQTTuser", true)->value());
                M5Dial.Lcd.setCursor(120,70);
                M5Dial.Lcd.print("pw" + request->getParam("MQTTpass", true)->value());
                request->send(200, "text/html", "<html><body><h1>Connected Successfully!</h1></body></html>");

           });
      } else {
        // request->send(200, "text/html", "<html><body><h1>Failed to Connect. Please try again.</h1><a href='/'>Back</a></body></html>");
           WiFi.disconnect();
           WiFi._setStatus(WL_CONNECT_FAILED);
           request->send(LittleFS, "/ErrorPage.html", "text/html");

      }
    } else {
      request->send(200, "text/html", "<html><body><h1>Missing SSID or Password. Please try again.</h1><a href='/'>Back</a></body></html>");
    }
  });
}