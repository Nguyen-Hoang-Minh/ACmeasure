#include <Arduino.h>
#include "M5Dial.h"
#include <HWCDC.h>
#include "USB.h"
#include "USBMSC.h"
#include "screen.h"
#include "Ticker.h"
#include "task.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);

Ticker updatescreen;
Ticker updateAC;
void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  setupACsensor();
  init_screen();

  updatescreen.attach_ms(1023,taskUpdateScreen);
  updateAC.attach_ms(211,taskUpdateACinfor);
}


void loop() {
  M5Dial.update();

  // put your main code here, to run repeatedly:
}
