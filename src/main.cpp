#include <Arduino.h>
#include "M5Dial.h"
#include <HWCDC.h>
#include "USB.h"
#include "USBMSC.h"
#include "screen.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);
bool a;

void readi2c(){
  M5Dial.Ex_I2C.getPort();
}
void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  init_screen();
  delay(100);
  setupACsensor();
}


void loop() {
  M5Dial.update();
  update_screen();
  delay(100);

  // put your main code here, to run repeatedly:
}
