//https://naylampmechatronics.com/blog/46_Tutorial-sensor-de-temperatura-DS18B20.html

#include <OneWire.h>                
#include <DallasTemperature.h>
 #include "Arduino.h"
#include "heltec.h"

OneWire ourWire(23);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

int pin = 22;
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Serial.begin(115200);
  sensors.begin();   //Se inicia el sensor
}
 
void loop() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  
  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.println(" C");
  delay(100);    
  
  
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 22, "temperaura:");
  Heltec.display->drawString(64, 32, String(temp,2) + " ºC");
  Heltec.display->display();
  
}
