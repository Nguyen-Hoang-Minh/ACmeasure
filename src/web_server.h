#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "M5Dial.h"
#include <WiFi.h>
#include <String.h>
#include <PubSubClient.h>
#include <DNSServer.h>

extern String ssid;
extern String password;

extern String MQTT_user;
extern String MQTT_pass;

extern WiFiClient espClient;
extern PubSubClient client;

extern bool MQTTConnectFlag;
extern bool WiFiConnectFlag;

void create_web();
void switch_wifi_mode();
void handleDNSRequests();
void turn_off_dns();