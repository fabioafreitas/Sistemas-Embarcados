#ifndef _ADS_HANDLER_H_
#define _ADS_HANDLER_H_

//#define ADS_HANDLER_DEBUG_MODE

#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void initAnalogDigitalConverter() {

  #ifdef ADS_HANDLER_DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  Serial.println("[ADS] Hello!");
  Serial.println("[ADS] Getting single-ended readings from AIN0..3");
  Serial.println("[ADS] ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  #endif
  
  ads.setGain(GAIN_TWOTHIRDS);

  if (!ads.begin(0x48)) {
    #ifdef ADS_HANDLER_DEBUG_MODE
    Serial.println("[ADS] Failed to initialize ADS.");
    #endif
    while (1);
  }

  #ifdef ADS_HANDLER_DEBUG_MODE
  Serial.println("[ADS] ADS initialized succesfully.");
  #endif
}

#endif /*_ADS_HANDLER_H_*/