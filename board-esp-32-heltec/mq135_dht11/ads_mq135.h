// instalar a lib ADS1x15 2.2.0 da adafruit no gerenciador de lib

#include <Adafruit_ADS1X15.h>

#define MQ135_ADS_PIN 0

Adafruit_ADS1115 ads;

void initADS() {
  Serial.println("[ADS] Hello!");
  Serial.println("[ADS] Getting single-ended readings from AIN0..3");
  Serial.println("[ADS] ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("[ADS] Failed to initialize ADS.");
    while (1);
  }
}

void getGas() {
  int16_t adc;
  float volts;

  adc = ads.readADC_SingleEnded(MQ135_ADS_PIN);
  volts = ads.computeVolts(adc);

  Serial.println("-----------------------------------------------------------");
  Serial.println("MQ-135");
  Serial.print("ADS Value: "); Serial.println(adc);
  Serial.print("Volts: "); Serial.print(volts, 3); Serial.println(" V");
}
