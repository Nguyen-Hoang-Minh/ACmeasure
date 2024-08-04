#include <Arduino.h>
#include "M5Dial.h"
#include <HWCDC.h>
#include "USB.h"
#include "USBMSC.h"
#include "screen.h"
#include "Ticker.h"
#include "task.h"
#include "Wire.h"
// put function declarations here:
M5GFX display;
M5Canvas img(&M5Dial.Display);

Ticker updatescreen;
Ticker updateAC;
Ticker tickercontrolRelay;
void printAddress(uint8_t address)  {
	M5Dial.Lcd.print("0x");
	if (address<0x10) {
		M5Dial.Lcd.print("0");
	}
	M5Dial.Lcd.println(address,HEX);
}
void setup() {
  // put your setup code here, to run once:
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);
  Serial.begin(115200);
  Wire.begin();
  M5Dial.Encoder.write(-1000);
  //setupPahub();
  // switchChanel_2();
   setupACsensor();
  // switchChanel_3();
   setupRelay();
   ALLrelayState=OFF_ALL;
   controlALL();
   init_screen();

  updateAC.attach_ms(211,taskUpdateACinfor);
  updatescreen.attach_ms(1023,taskUpdateScreen);
  tickercontrolRelay.attach_ms(53,taskControlRelay);

}

void loop() {
  // M5.update();
  // if(M5.BtnA.wasClicked()==true){
  //   relayState=ON_RELAY_1;
  //   switchChanel_3();
  //   controlALL();
  // }
  // put your main code here, to run repeatedly:
}
