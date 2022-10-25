#define DEBUG_MODE

// Please select the corresponding model

// #define SIM800L_IP5306_VERSION_20190610
// #define SIM800L_AXP192_VERSION_20200327
#define SIM800C_AXP192_VERSION_20200609
// #define SIM800L_IP5306_VERSION_20200811

#include <Arduino.h>
#include "utilities.h"

#include "rfmanager.h"
#include "http.h"
#include "batteryLevel.h"

void setup() {
   Serial.begin(115200);
   initWiFi();
   initBATTERY();

    pinMode(LED_GPIO, OUTPUT);
    digitalWrite(LED_GPIO, LED_ON);
    delay(1000);
    digitalWrite(LED_GPIO, LED_OFF);

}


void loop() {
  delay(1000);
  Battery battery = getBatteryLevel();
  delay(1000);
  sendHttpToServer(battery.voltage, battery.level);
}
