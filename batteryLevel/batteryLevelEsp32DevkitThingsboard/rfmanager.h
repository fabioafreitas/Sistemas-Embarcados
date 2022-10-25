#ifndef _RF_MANAGER_H_
#define _RF_MANAGER_H_

#include <WiFi.h>

String ssid = "brisa-2599747";
String pass = "iqawp1v1";

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid.c_str(), pass.c_str());
  #ifdef DEBUG_MODE
  Serial.println("[WIFI] Connecting to WiFi...");
  #endif

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG_MODE
    Serial.print(".");
    #endif

    if(tries++ >= 20) {
      ESP.restart();
    }
  }
  
  #ifdef DEBUG_MODE
  Serial.println(WiFi.localIP());
  #endif
}

#endif /*_RF_MANAGER_H_*/
