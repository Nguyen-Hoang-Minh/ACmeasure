#include <WiFi.h>
#include <PubSubClient.h>
#include <M5Dial.h>
#include <control_relays.h>
#include <pahub.h>

extern const char* ssid;
extern const char* password;
extern const char* mqtt_server;

extern char* mqtt_topic_sended;
extern byte* mqtt_arrived_mess;

extern bool WiFiConnectFlag;
extern bool MQTTConnectFlag;

void setupMQTT();
void clientPublish(char* topic, const char* payload);
void clientLoop();
void checkWiFiStatus();
void checkConnectMQTT();