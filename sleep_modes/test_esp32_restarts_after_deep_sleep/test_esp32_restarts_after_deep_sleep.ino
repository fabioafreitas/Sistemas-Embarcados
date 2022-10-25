#include "heltec.h"
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIME  10        /* Time ESP32 will go to sleep (in seconds) */

void blynk(int miliseconds, int times) {
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0 ; i < times ; i++ ) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(miliseconds);
    digitalWrite(LED_BUILTIN, LOW);
    delay(miliseconds);
  }
}

void setup() {
  blynk(500, 3);
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME * uS_TO_S_FACTOR);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  blynk(200, 10);
  esp_deep_sleep_start();
}
