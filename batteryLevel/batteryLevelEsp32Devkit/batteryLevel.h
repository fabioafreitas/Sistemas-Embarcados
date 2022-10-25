#ifndef _BATTERY_LEVEL_H_
#define _BATTERY_LEVEL_H_

#ifndef BATTERY_SIGNAL_PIN
#define BATTERY_SIGNAL_PIN 0
#endif

#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void initADS() {

  #ifdef DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  Serial.println("[ADS] Hello!");
  Serial.println("[ADS] Getting single-ended readings from AIN0..3");
  Serial.println("[ADS] ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  #endif
  
  ads.setGain(GAIN_TWOTHIRDS);

  if (!ads.begin()) {
    #ifdef DEBUG_MODE
    Serial.println("[ADS] Failed to initialize ADS.");
    #endif
    while (1);
  }

  #ifdef DEBUG_MODE
  Serial.println("[ADS] ADS initialized succesfully.");
  #endif
}

float convertVoltageToPercentage(float voltage) {
  // 2.8 = min voltage, 4.2 = max voltage
  float min_max_scaling = (voltage - 2.8) / (4.2 - 2.8);
  return min_max_scaling * 100;
}

float getBatteryLevel() {
  int16_t voltageAnalogSignal = ads.readADC_SingleEnded(BATTERY_SIGNAL_PIN);
  float voltage = ads.computeVolts(voltageAnalogSignal);

  float batteryLevel = convertVoltageToPercentage(voltage);
   
  #ifdef DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  Serial.print("[BATTERY]\tanalog signal: "); Serial.println(voltageAnalogSignal);
  Serial.print("\t\tvoltage: "); Serial.print(voltage*2, 3); Serial.println(" V");
  Serial.print("\t\tBattery Level: "); Serial.print(batteryLevel, 1); Serial.println("%");
  #endif
  
  return batteryLevel;
}

#endif /*_BATTERY_LEVEL_H_*/
