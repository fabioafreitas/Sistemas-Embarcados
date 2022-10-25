#ifndef _HTTP_H_
#define _HTTP_H_

#include <WiFi.h>
#include <HTTPClient.h>

#define JSON_BUFFER_SIZE (300)
char json[JSON_BUFFER_SIZE];
const char* hostname = "http://thingsboard.smartrural.com.br";
String accessToken = "c37vb55nNVHiCYlLgMaP";

// return true of http code is 200, false if not
bool sendHttpToServer(float current, float power) {
  #ifdef DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  #endif
  if(WiFi.status()== WL_CONNECTED){
    String wifi_ssid = WiFi.SSID();
    int len = wifi_ssid.length()+1;
    char wifi_ssid_buffer[len];
    wifi_ssid.toCharArray(wifi_ssid_buffer, len);
    
    String ip = WiFi.localIP().toString();
    len = ip.length()+1;
    char ip_buffer[len];
    ip.toCharArray(ip_buffer, len);
    
    snprintf (json, JSON_BUFFER_SIZE, \
      "{" \
        "\"current\":%3.3f," \
        "\"power\":%i," \
        "\"ssid\":\"%s\"," \
        "\"ip\":\"%s\""
      "}", \
      current, power, wifi_ssid_buffer, ip_buffer);

    // requisição http post
    HTTPClient http;
    String uri = String(hostname) + "/api/v1/" + String(accessToken) + "/telemetry";
    http.begin(uri);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);

    #ifdef DEBUG_MODE
    Serial.print("[HTTP] Response code: ");
    Serial.println(httpResponseCode);
    #endif
    
    http.end();
    
    return (httpResponseCode == 200) ? true : false;
  }
  else {
    #ifdef DEBUG_MODE
    Serial.println("[HTTP] WiFi Disconnected");
    #endif
  }
  return false;
}

#endif /*_HTTP_H_*/