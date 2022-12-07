#define DEBUG_MODE

#include "rfmanager.h"
#include "http.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIME  1        /* Time ESP32 will go to sleep (in seconds) */

void setup() {
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME * uS_TO_S_FACTOR);
  
  #ifdef DEBUG_MODE
  Serial.begin(115200);
  #endif
  
  delay(1000);

  initWiFi();

  int current = random(20,30);
  int power = random(10,20);
  bool httpSuccess = sendHttpToServer(current, power);

  #ifdef DEBUG_MODE
  Serial.println("[DEEP SLEEP] Going to sleep!");
  #endif
  esp_deep_sleep_start();
}

void loop() {
}
