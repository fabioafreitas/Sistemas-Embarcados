#include "heltec.h"
#include "string.h"
#include "stdio.h"
#include "root_ca.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
byte localAddress = 0xAA;     // address of this device
byte destination = 0x11;      // destination to send to
byte msgCount = 0;            // count of outgoing messages
long lastSendTime = 0;        // last send time

#define JSON_BUFFER_SIZE (300)
char json[JSON_BUFFER_SIZE];

/*
const char* ssid = "iot";
const char* password = "ufrpe_iot";
*/
const char* ssid = "BBGJOSELITO";
const char* password = "Singularidade10";

const char* hostname = "https://thingsboard.smartrural.com.br";
const char* access_token = "D63C1pgDOirzveQOpg3K";
String uri = String(hostname) + "/api/v1/" + String(access_token) + "/telemetry";




void setup() {
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(
    true /*DisplayEnable Enable*/, 
    true /*Heltec.LoRa Disable*/, 
    true /*Serial Enable*/, 
    true /*PABOOST Enable*/, 
    BAND /*long BAND*/
  );
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("-----------------------------------------------------------");
  Serial.println("[WIFI] Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  
}

void loop() {
  onReceive(LoRa.parsePacket());
}

void onReceive(int packetSize) {
  if (packetSize == 0) {
    digitalWrite(LED_BUILTIN, LOW);
    return;
  };          // if there's no packet, return
  digitalWrite(LED_BUILTIN, HIGH);
  
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length())
  {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("-----------------------------------------------------------");
  Serial.print("Sender ADDR: 0x" + String(sender, HEX));
  Serial.println("\tReceiver ADDR: 0x" + String(recipient, HEX));
  Serial.print("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("\t\tSnr: " + String(LoRa.packetSnr()));
  Serial.print("Msg ID: " + String(incomingMsgId));
  Serial.println("\t\tMsg length: " + String(incomingLength));
  Serial.println("Message: " + incoming);

  assembleJson(recipient, sender, incomingMsgId, incomingLength, incoming, LoRa.packetRssi(), LoRa.packetSnr());
  sendJson();

}

void assembleJson(
  int recipient, 
  byte sender, 
  byte incomingMsgId, 
  byte incomingLength,
  String incoming,
  int rssi,
  float snr) {

  String wifi_ssid = WiFi.SSID();
  int len = wifi_ssid.length()+1;
  char wifi_ssid_buffer[len];
  wifi_ssid.toCharArray(wifi_ssid_buffer, len);

  String ip = WiFi.localIP().toString();
  len = ip.length()+1;
  char ip_buffer[len];
  ip.toCharArray(ip_buffer, len);  

  len = incoming.length()+1;
  char incoming_buffer[len];
  incoming.toCharArray(incoming_buffer, len);  


  snprintf (json, JSON_BUFFER_SIZE, \
      "{\"recipient\":\"0x%x\",\"sender\":\"0x%x\",\"messageId\":%i,\"messageLength\":%i,\"message\":\"%s\",\"rssi\":%i,\"snr\":%f,\"wifi_ssid\":\"%s\",\"ip\":\"%s\"}", \
      recipient, 
      int(sender), 
      int(incomingMsgId), 
      int(incomingLength), 
      incoming_buffer, 
      rssi, 
      snr, 
      wifi_ssid_buffer, 
      ip_buffer
  );
}

void sendJson() {
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(uri, root_ca);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  } 
  else {
    Serial.println("WiFi Disconnected");
  }
}
