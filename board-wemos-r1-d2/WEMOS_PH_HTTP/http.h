#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// NETWORK VARIABLES
const char* ssid = "Iot"; 
const char* password = "ufrpe_iot"; 
const char* http_server = "http://dojot.fabiotest.online:5000";

void setup_wifi() {
  Serial.print("\nConectando-se a ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void send_json(String uri, char* body) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, http_server+uri);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(body);
    Serial.println(httpCode);
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    http.end();   //Close connection
  }
}
