#include "Arduino.h"
#include "heltec.h"

#include "ads_mq135.h"
#include "dht11.h"

void setup() {
  Heltec.begin(true, false, true);
  delay(1000);
  Serial.begin(9600);
  initADS();
  initDHT();
}

unsigned long lastReading = 0;
void loop() {
   unsigned long now = millis();
  if (now - lastReading > 5000) {
    lastReading = now;
    getGas();
    getDht();
  }
}
