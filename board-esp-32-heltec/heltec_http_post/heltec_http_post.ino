#include "Arduino.h"
#include "heltec.h"

#include <WiFi.h>
#include <HTTPClient.h>

#define JSON_BUFFER_SIZE (100)
char json[JSON_BUFFER_SIZE];

const char* ssid = "iot";
const char* password = "ufrpe_iot";

const char* serverName = "http://redeneural.fabiotest.online:5000/d6cc79";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Heltec.begin(true, false, true);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
      http.addHeader("Content-Type", "application/json");

      float ph = 7.54;
      float temp = 27.54;

      String wifi_ssid = WiFi.SSID();
      int len = wifi_ssid.length()+1;
      char wifi_ssid_buffer[len];
      wifi_ssid.toCharArray(wifi_ssid_buffer, len);
      
      String ip = WiFi.localIP().toString();
      len = ip.length()+1;
      char ip_buffer[len];
      ip.toCharArray(ip_buffer, len);
      
      snprintf (json, JSON_BUFFER_SIZE, \
      "{\"ph\":%3.2f,\"temperature\":%3.2f,\"wifi_ssid\":\"%s\",\"ip\":\"%s\"}", \
      ph, temp, wifi_ssid_buffer, ip_buffer);
      
      int httpResponseCode = http.POST(json);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
