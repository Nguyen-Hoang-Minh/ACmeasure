#include <wifi_mqtt.h>




char* mqtt_topic_sended;
byte* mqtt_arrived_mess;


char* check_wifi; 
char* temp_humi_mqtt;
char* relay1_mqtt; 
char* relay2_mqtt; 
char* relay3_mqtt; 
char* relay4_mqtt; 
char* ac_measure_mqtt;
char* temp; 
const char* mqtt_server = "io.adafruit.com";

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

  // Serial.println("Message arrived [");
  // Serial.println(topic);
  // Serial.println("] ");
  // for (int i = 0; i < length; i++) {
  //   Serial.println((char)payload[i]);
  // }
  // Serial.println();



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
}

void checkConnectMQTT()
{
  if (!client.connected())
  {
    String clientID = "M5Stack-";
    clientID += String(random(0xffff), HEX);
    bool result = client.connect(clientID.c_str(), MQTT_user.c_str(), MQTT_pass.c_str());
    result=true;
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
      client.subscribe(ac_measure_mqtt);
    }
    else
    {
      MQTTConnectFlag = false;
    }
  }
}

void subcribeMQTT(){
    check_wifi = strdup((MQTT_user + "/feeds/m5stack").c_str());
    temp_humi_mqtt = strdup((MQTT_user + "/feeds/topic0").c_str());
    relay1_mqtt = strdup((MQTT_user + "/feeds/topic1").c_str());
    relay2_mqtt = strdup((MQTT_user + "/feeds/topic2").c_str());
    relay3_mqtt = strdup((MQTT_user + "/feeds/topic3").c_str());
    relay4_mqtt = strdup((MQTT_user + "/feeds/topic4").c_str());
    ac_measure_mqtt = strdup((MQTT_user + "/feeds/topic5").c_str());
    temp = strdup((MQTT_user + "/feeds/topic6").c_str());
      client.publish(check_wifi, "hello world11");
      client.subscribe(check_wifi);
      client.subscribe(temp_humi_mqtt);
      client.subscribe(relay1_mqtt);
      client.subscribe(relay2_mqtt);
      client.subscribe(relay3_mqtt);
      client.subscribe(relay4_mqtt);
      client.subscribe(ac_measure_mqtt);
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