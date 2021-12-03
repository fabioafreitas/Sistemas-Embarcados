#include <OneWire.h>                
#include <DallasTemperature.h>
#include "Arduino.h"
#include "heltec.h"

#define DS18B20_DIGITAL_PIN 23 // pois este pino não é analógico

OneWire ourWire(DS18B20_DIGITAL_PIN);
DallasTemperature ds18b20(&ourWire); 

float ds18b20TemperatureValue(bool verbose) {
  ds18b20.requestTemperatures();
  float temp = ds18b20.getTempCByIndex(0);
  if(verbose) {
    Serial.print("DS18B20:  "); Serial.print(temp); Serial.println("ºC\n");
  }
  return temp;
}

void setup() {
  Heltec.begin(true /*Display*/, false /*LoRa*/, true /*Serial*/);
  Serial.begin(9600);
  ds18b20.begin();
}


void loop() {
  float dsTemp = ds18b20TemperatureValue(true);
  
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 32, "temp (ds): " + String(dsTemp,2) + " ºC");
  Heltec.display->display();
        
  delay(1000);
}
