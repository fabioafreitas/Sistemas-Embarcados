#define DEBUG_MODE

#include "heltec.h"
#include "batteryLevel.h"

void setup() {
   Heltec.begin(false, false, true);
   Serial.begin(115200);
   initADS();
}


void loop() {
  delay(1000);
  getBatteryLevel();
}
