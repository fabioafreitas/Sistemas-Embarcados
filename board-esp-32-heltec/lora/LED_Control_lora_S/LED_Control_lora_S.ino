#include "heltec.h"
#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

int counter = 0;

void setup() {
  
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(
    false /*DisplayEnable Enable*/, 
    true /*Heltec.LoRa Disable*/, 
    true /*Serial Enable*/, 
    true /*PABOOST Enable*/, 
    BAND /*long BAND*/
  );
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  
}

int val = 0;

void loop() {
  if(val == 0){
    Serial.print("Sending packet: OpenLED\r\n");
    // send packet
    LoRa.beginPacket();
    LoRa.print("OpenLED");
    LoRa.endPacket();
    val = 1;                      
  }
  if(val == 1){
    Serial.print("Sending packet: CloseLED\r\n");
    // send packet
    LoRa.beginPacket();
    LoRa.print("CloseLED");
    LoRa.endPacket(); 
    val = 0;
    delay(2000);
  }
  delay(1000);  
}
