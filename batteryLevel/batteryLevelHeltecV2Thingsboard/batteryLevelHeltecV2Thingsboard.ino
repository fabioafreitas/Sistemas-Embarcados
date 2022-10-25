#define DEBUG_MODE

#include "heltec.h"
#include "rfmanager.h"
#include "http.h"
#include "batteryLevel.h"

void setup() {
   Heltec.begin(false, false, true);
   Serial.begin(115200);
   initWiFi();
   initHTTP();
   initBATTERY();
}


void loop() {
  delay(1000);
  float batLevel = getBatteryLevel();
  delay(1000);
  sendHttpToServer(batLevel);
}
