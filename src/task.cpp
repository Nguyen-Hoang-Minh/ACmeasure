#include "task.h"

void taskUpdateScreen(){
    update_screen();
}

void taskUpdateACinfor(){
    switchChanel_2();
    updateACinfor();
}

int oldPosition = -1000;

void taskControlRelay(){
    M5Dial.update();
    int newPosition = M5Dial.Encoder.read();
    if(newPosition>=(oldPosition+3)){
        // M5Dial.Lcd.clear();
        // M5Dial.Lcd.setCursor(70,70);
        // M5Dial.Lcd.print(oldPosition);
        // M5Dial.Lcd.setCursor(70,80);
        // M5Dial.Lcd.print(newPosition);
        // M5Dial.Lcd.setCursor(70,90);
        // M5Dial.Lcd.print(selected_relay);
        M5Dial.Encoder.write(oldPosition+3);
        oldPosition+=3;
        selected_relay+=1;
        M5Dial.Speaker.tone(10000,40);
        if(selected_relay>3){
            selected_relay = 3;
            M5Dial.Speaker.tone(18000,2000);
        }
    }
    else if(newPosition<oldPosition-3){
        // M5Dial.Lcd.clear();
        // M5Dial.Lcd.setCursor(70,100);
        // M5Dial.Lcd.print(oldPosition);
        // M5Dial.Lcd.setCursor(70,110);
        // M5Dial.Lcd.print(newPosition);
        // M5Dial.Lcd.setCursor(70,120);
        // M5Dial.Lcd.print(selected_relay);
        M5Dial.Encoder.write(oldPosition-3);
        oldPosition-=3;
        selected_relay-=1;
        M5Dial.Speaker.tone(5000,40);
        if(selected_relay<0){
            selected_relay=0;
            M5Dial.Speaker.tone(18000,2000);
        }
    }

    if(M5.BtnA.wasClicked()==true){
        M5Dial.Speaker.tone(3000,40);
        switch (selected_relay)
        {
        case RELAY_1:
            if(relayState==SWITCH_FLAG){
                switchChanel_3();
                controlRelay();
            }
            if(relay_1_state==ON_SIGNAL){
                relayState=OFF_RELAY_1;
                clientPublish(relay1_mqtt,"0");
            }
            else if(relay_1_state==OFF_SIGNAL){
                relayState=ON_RELAY_1;
                clientPublish(relay1_mqtt,"1");
            }
            switchChanel_3();
            controlRelay();
            break;
        case RELAY_2:
            if(relayState==SWITCH_FLAG){
                switchChanel_3();
                controlRelay();
            }
            if(relay_2_state==ON_SIGNAL){
                relayState=OFF_RELAY_2;
                clientPublish(relay2_mqtt,"0");
            }
            else if(relay_2_state==OFF_SIGNAL){
                relayState=ON_RELAY_2;
                clientPublish(relay2_mqtt,"1");
            }
            switchChanel_3();
            controlRelay();
            break;
        case RELAY_3:
            if(relayState==SWITCH_FLAG){
                switchChanel_3();
                controlRelay();
            }
            if(relay_3_state==ON_SIGNAL){
                relayState=OFF_RELAY_3;
                clientPublish(relay3_mqtt,"0");
            }
            else if(relay_3_state==OFF_SIGNAL){
                relayState=ON_RELAY_3;
                clientPublish(relay3_mqtt,"1");
            }
            switchChanel_3();
            controlRelay();
            break;
        case RELAY_4:
            if(relayState==SWITCH_FLAG){
                switchChanel_3();
                controlRelay();
            }
            if(relay_4_state==ON_SIGNAL){
                relayState=OFF_RELAY_4;
                clientPublish(relay4_mqtt,"0");
            }
            else if(relay_4_state==OFF_SIGNAL){
                relayState=ON_RELAY_4;
                clientPublish(relay4_mqtt,"1");
            }
            switchChanel_3();
            controlRelay();
            break;
        default:
            break;
        }
    }

    if(M5.BtnA.wasHold()==true){
        switch(ALLrelayState)
        {
            case IDLE:
                ALLrelayState = OFF_ALL;
                switchChanel_3();
                controlALL();
                break;
            case ON_ALL:
                switchChanel_3();
                ALLrelayState = OFF_ALL;
                controlALL();
                clientPublish(relay1_mqtt,"0");
                clientPublish(relay2_mqtt,"0");
                clientPublish(relay3_mqtt,"0");
                clientPublish(relay4_mqtt,"0");
                break;
            case OFF_ALL:
                switchChanel_3();
                ALLrelayState = ON_ALL;
                controlALL();
                clientPublish(relay1_mqtt,"1");
                clientPublish(relay2_mqtt,"1");
                clientPublish(relay3_mqtt,"1");
                clientPublish(relay4_mqtt,"1");
                break;
            default:
                break;
        }
    }
}

uint8_t counterSend = 0;
String mes;
String temp_humi_mes;

void taskClientPublish()
{
  mes += String(vol_str);
  mes += ",";
  mes += String(cur_str);
  mes += ",";
  mes += String(pow_str);
  mes += ",";
  mes += String(appow_str);
  mes += ",";

  temp_humi_mes += String(temperature);
  temp_humi_mes += ",";
  temp_humi_mes += String(humidity);
  temp_humi_mes += ";";

  counterSend ++;
  if (counterSend == 1)
  {
    clientPublish(ac_measure_mqtt, mes.c_str());
    mes = "";
    clientPublish(temp_humi_mqtt,temp_humi_mes.c_str());
    temp_humi_mes = "";
    counterSend = 0;
  }
}

