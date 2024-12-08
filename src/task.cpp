#include "task.h"

#define MAX_MEASUREMENT 150
#define DETECT_THRESHOLD 20.0

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

Preferences env;

float mahal;
float measurement[MAX_MEASUREMENT];
float mad[3];
float threshold = DETECT_THRESHOLD;
bool abnormal_flag = false;
float mean_temp = 0;
float mean_humi = 0;
float mean_hi = 0;

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

    if(mutex_lock == false){
        mutex_lock = true;
        Serial.println("current index:");
        Serial.println(sample_index);
        delay(10);
        for(int axis = 0; axis < 3; axis++){
            Serial.println("Feature");
            for(int i = 0; i < sample_index; i++){   //consider using sample_index instead of MAX_MEASUREMENT
                measurement[i] = data_samples[i][axis];
                // Serial.println(measurement[i]);
                // delay(5);
                // Serial.println("index");
                // Serial.println(sample_index);
                // delay(5);
            }
            if(axis==0){
                mean_temp = mean(measurement, sample_index);//consider using sample_index instead of MAX_MEASUREMENT
            }
            else if(axis == 1){
                mean_humi = mean(measurement, sample_index);//consider using sample_index instead of MAX_MEASUREMENT
            }
            else if(axis == 2){
                mean_hi = mean(measurement, sample_index);//consider using sample_index instead of MAX_MEASUREMENT
            }
            mad[axis] = calc_mad(measurement, sample_index);//consider using sample_index instead of MAX_MEASUREMENT
        }

        mahal = mahalanobis(mad, model_mu, *model_inv_cov, model_mu_dim1);
        Serial.println("mahalanobis distance: ");
        delay(10);
        Serial.println(mahal);
        if(mahal > threshold){
            abnormal_flag = true;
        }
        else{
            abnormal_flag = false;
        }

        temp_humi_mes += String(mean_temp);
        temp_humi_mes += ",";
        temp_humi_mes += String(mean_humi);
        temp_humi_mes += ",";
        temp_humi_mes += String(mean_hi);
        temp_humi_mes += ",";
        temp_humi_mes += String(abnormal_flag);
        temp_humi_mes += ",";
        temp_humi_mes += String(mahal);

        env.putString("mean_temp", String(mean_temp));
        env.putString("mean_humi", String(mean_humi));
        env.putString("mean_hi", String(mean_hi));
        env.putString("abnormal_flag", String(abnormal_flag));
        env.putString("mahal", String(mahal));

        mean_temp = 0;
        mean_humi = 0;
        mean_hi = 0;

        clientPublish(ac_measure_mqtt, mes.c_str());
        mes = "";
        clientPublish(temp_humi_mqtt,temp_humi_mes.c_str());
        temp_humi_mes = "";
        
        sample_index = 0;
        mutex_lock = false; 
    }
        
}

