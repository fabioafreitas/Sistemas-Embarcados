#include "Arduino.h"
#include "heltec.h"


#define TEMP_SENSOR 22; //PINO 22
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 22, "Joana");
  Heltec.display->drawString(64, 32, "Darc");
  Heltec.display->display();
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}
