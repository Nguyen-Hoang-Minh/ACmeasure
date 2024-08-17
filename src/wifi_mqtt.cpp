#include <wifi_mqtt.h>

#define MQTT_user  "kienpham"
#define MQTT_pass  ""

WiFiClient espClient;
PubSubClient client(espClient);

char* mqtt_topic_sended;
byte* mqtt_arrived_mess;

bool WiFiConnectFlag = false;
bool MQTTConnectFlag = false;

const char* ssid        = "ACLAB";
const char* password    = "ACLAB2023";
// const char* mqtt_server = "172.28.182.87";
const char* mqtt_server = "io.adafruit.com"
;

void checkWiFiStatus()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    WiFiConnectFlag = true;
  }
  else
  {
    WiFiConnectFlag = false;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // M5.Lcd.print("Message arrived [");
  // M5.Lcd.print(topic);
  // M5.Lcd.print("] ");
  // for (int i = 0; i < length; i++) {
  //   M5.Lcd.print((char)payload[i]);
  // }
  // M5.Lcd.println();

  char message[5] = "0000";

  if (topic[20] == '1')
  {
    if ((char)payload[0] == '1')
    {
      relay_1_state = true;
      switchChanel_3();
      relay.relayWrite(RELAY_1, ON_SIGNAL);
    }
    else 
    {
      relay_1_state = false;
      switchChanel_3();
      relay.relayWrite(RELAY_1, OFF_SIGNAL);
    }
  }

  if (topic[20] == '2')
  {
    if ((char)payload[0] == '1')
    {
      relay_2_state = true;
      switchChanel_3();
      relay.relayWrite(RELAY_2, ON_SIGNAL);
    }
    else 
    {
      relay_2_state = false;
      switchChanel_3();
      relay.relayWrite(RELAY_2, OFF_SIGNAL);
    }
  }

  if (topic[20] == '3')
  {
    if ((char)payload[0] == '1')
    {
      relay_3_state = true;
      switchChanel_3();
      relay.relayWrite(RELAY_3, ON_SIGNAL);
    }
    else 
    {
      relay_3_state = false;
      switchChanel_3();
      relay.relayWrite(RELAY_3, OFF_SIGNAL);
    }
  }

  if (topic[20] == '4')
  {
    if ((char)payload[0] == '1')
    {
      relay_4_state = true;
      switchChanel_3();
      relay.relayWrite(RELAY_4, ON_SIGNAL);
    }
    else 
    {
      relay_4_state = false;
      switchChanel_3();
      relay.relayWrite(RELAY_4, OFF_SIGNAL);
    }
  }
  if (topic[20] == '0')
  {
    if ((char)payload[0] == '1')
    {
      ALLrelayState = ON_ALL;
      switchChanel_3();
      controlALL();
    }
    else 
    {
      ALLrelayState = OFF_ALL;
      switchChanel_3();
      controlALL();
    }
  }

  Serial.println(topic);
  Serial.println((char)payload[0]);
  if (topic[5] == '6')
  {
    if ((char)payload[0] == 'S')
    {
      if (relay_1_state) message[0] = '1';
      if (relay_2_state) message[1] = '1';
      if (relay_3_state) message[2] = '1';
      if (relay_4_state) message[3] = '1';
      client.publish("topic6", message);
    }
  }

}

void checkConnectMQTT()
{
  if (!client.connected())
  {
    String clientID = "M5Stack-";
    clientID += String(random(0xffff), HEX);
    bool result = client.connect(clientID.c_str(), MQTT_user, MQTT_pass);
    if (result)
    {
      MQTTConnectFlag = true;
      client.publish(check_wifi, "hello world11");
      client.subscribe(check_wifi);
      client.subscribe(temp_humi_mqtt);
      client.subscribe(relay1_mqtt);
      client.subscribe(relay2_mqtt);
      client.subscribe(relay3_mqtt);
      client.subscribe(relay4_mqtt);
      client.subscribe(temp);
    }
    else
    {
      MQTTConnectFlag = false;
    }
  }
}

void setupMQTT() 
{
  client.setServer(mqtt_server, 1883);  // Sets the server details.  
  client.setCallback(callback);  // Sets the message callback function.  
}

void clientPublish(char* topic, const char* payload)
{
  client.publish(topic, payload);
}

void clientLoop(){
  client.loop();
}