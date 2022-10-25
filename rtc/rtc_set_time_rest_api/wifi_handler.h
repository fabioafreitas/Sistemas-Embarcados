#ifndef _WIFI_HANDLER_H_
#define _WIFI_HANDLER_H_

#define WIFI_HANDLER_DEBUG_MODE

#include <WiFi.h>

String ssid = "iot";
String pass = "ufrpe_iot";

// Initialize WiFi
// return true if connects to a wifi
// return false if an error occur
bool initWiFiStation() {
  // validation of wifi already connected, in case of running 
  // this method twice when wifi is already initialized
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  }

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid.c_str(), pass.c_str());
  #ifdef WIFI_HANDLER_DEBUG_MODE
  Serial.println("[WIFI] Connecting to WiFi...");
  #endif

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef WIFI_HANDLER_DEBUG_MODE
    Serial.print(".");
    #endif

    if(tries++ >= 20) {
      //ESP.restart();
      return false;
    }
  }
  
  #ifdef WIFI_HANDLER_DEBUG_MODE
  Serial.println();
  Serial.println(WiFi.localIP());
  #endif

  return true;
}

#endif /*_WIFI_HANDLER_H_*/
