#include "rtc_handler.h"

void setup() {
  Serial.begin(115200);
  initRTC();
}

void loop() {
  getDateTimeNow();
  delay(1000);
}
