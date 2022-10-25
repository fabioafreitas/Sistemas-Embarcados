#include "DFRobot_ORP_PRO.h"
#include <Adafruit_ADS1X15.h>

#define PIN_ORP 0

float ADC_voltage;

DFRobot_ORP_PRO ORP(0);
Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  ads.setGain(GAIN_TWOTHIRDS);
  if (!ads.begin(0x48)) {
    while (1);
  }
}

void loop() {
  ADC_voltage = ads.computeVolts(ads.readADC_SingleEnded(PIN_ORP));
  Serial.print("ORP value is : ");
  Serial.print(ORP.getORP(ADC_voltage));
  Serial.println("mV");
  Serial.print("Voltage value is : ");
  Serial.print(ORP.getORP(ADC_voltage));
  Serial.println("V");
  delay(1000);
}
