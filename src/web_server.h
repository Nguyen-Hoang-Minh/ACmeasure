#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "M5Dial.h"
#include <WiFi.h>
#include <String.h>
#include <PubSubClient.h>
extern String ssid;
extern String password;

extern String MQTT_user;
extern String MQTT_pass;

extern WiFiClient espClient;
extern PubSubClient client;

void create_web();