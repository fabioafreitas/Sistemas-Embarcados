#include "heltec.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
byte localAddress = 0xBB;     // address of this device
byte destination = 0xAA;      // destination to send to
byte msgCount = 0;            // count of outgoing messages
long lastSendTime = 0;        // last send time
int interval = 10000;          // interval between sends

void setup() {
  Heltec.begin(false /*DisplayEnable Enable*/, true /*Heltec.LoRa Enable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  Serial.println("Heltec.LoRa Duplex");
}

void loop() {
  if (millis() - lastSendTime > interval) {
    String message = "Hello, My Address Is 0x" + String(localAddress, HEX);   // send a message
    sendMessage(message);
    Serial.println("Sending " + message);
    lastSendTime = millis();            // timestamp the message
    interval = random(2000) + 10000;    // 2-3 seconds
  }
}

void sendMessage(String outgoing)
{
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}
