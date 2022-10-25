#define DEBUG_MODE

#include "batteryLevel.h"

void setup() {
   Serial.begin(115200);
   initADS();
}


void loop() {
  delay(1000);
  getBatteryLevel();
}
