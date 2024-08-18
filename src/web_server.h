#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "LittleFS.h"
extern String wifi_ssid;
extern String wifi_pw;
// extern char* mqtt_server;
// extern char* check_wifi;
// extern char* temp_humi_mqtt;
// extern char* relay1_mqtt;
// extern char* relay2_mqtt;
// extern char* relay3_mqtt;
// extern char* relay4_mqtt;
// extern char* ac_measure_mqtt;
// extern char* temp;

void create_web();