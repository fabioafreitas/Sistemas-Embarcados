#define SIM800L_AXP192_VERSION_20200327
#include "utilities.h"
#include "rtc_handler.h"

void setup() {
  Serial.begin(115200);
  initRTC();
}

void loop() {
  getDateTimeNow();
  delay(1000);
}
