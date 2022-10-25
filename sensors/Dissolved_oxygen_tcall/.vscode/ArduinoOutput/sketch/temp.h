#line 1 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\temp.h"
#ifndef _TEMPERATURE_DS18B20_H_
#define _TEMPERATURE_DS18B20_H_

//#define TEMPERATURE_DS18B20_DEBUG_MODE

#include <OneWire.h>                
#include <DallasTemperature.h>

#ifndef DS18B20_DIGITAL_PIN
#define DS18B20_DIGITAL_PIN 27 // digital pin for this sensor
#endif

OneWire ourWire(DS18B20_DIGITAL_PIN);
DallasTemperature ds18b20(&ourWire); 

void initTemperatureDS18B20() {
  ds18b20.begin();
}

float getTempDS18B20() {
  ds18b20.requestTemperatures();
  float tempValue = ds18b20.getTempCByIndex(0);
  
  #ifdef TEMPERATURE_DS18B20_DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  Serial.print("[TEMP] ds18b20 temperature:  "); Serial.print(tempValue); Serial.println("ºC");
  #endif

  return tempValue;
}
#endif