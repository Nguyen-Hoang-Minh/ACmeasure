#include <PubSubClient.h>
#include <M5Dial.h>
#include <control_relays.h>
#include <pahub.h>
#include "web_server.h"

#define check_wifi "kienpham/feeds/m5stack"
#define temp_humi_mqtt "kienpham/feeds/topic0"
#define relay1_mqtt "kienpham/feeds/topic1"
#define relay2_mqtt "kienpham/feeds/topic2"
#define relay3_mqtt "kienpham/feeds/topic3"
#define relay4_mqtt "kienpham/feeds/topic4"
#define ac_measure_mqtt "kienpham/feeds/topic5"
#define temp "kienpham/feeds/topic6"

extern const char* mqtt_server;

extern char* mqtt_topic_sended;
extern byte* mqtt_arrived_mess;


void setupMQTT();
void clientPublish(char* topic, const char* payload);
void clientLoop();
void checkWiFiStatus();
void checkConnectMQTT();