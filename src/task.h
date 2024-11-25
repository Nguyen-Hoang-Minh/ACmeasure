#include "ACmeasure.h"
#include "screen.h"
#include "control_relays.h"
#include "pahub.h"
#include "wifi_mqtt.h"
#include "MAHO_model_c.h"
void taskUpdateScreen();
void taskUpdateACinfor();
void taskCheckWiFiStatus();
void taskControlRelay();
void taskClientPublish();

