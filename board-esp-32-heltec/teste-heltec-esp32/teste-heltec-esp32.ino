#include "Arduino.h"
#include "heltec.h"
 
void setup () {
 Heltec.begin(false, false, false);
// 
// Heltec.display->setContrast(255);
// Heltec.display->clear();
//  
// Heltec.display->setFont(ArialMT_Plain_24);
// Heltec.display->drawString(0, 0, "LoRa WiFi");
//  
// Heltec.display->setFont(ArialMT_Plain_16);
// Heltec.display->drawString(0, 25, "Usinainfo");
//  
// Heltec.display->setFont(ArialMT_Plain_10);
// Heltec.display->drawString(0, 45, "www.usinainfo.com.br/blog/");
// 
// Heltec.display->display();
}
 
void loop () {}
