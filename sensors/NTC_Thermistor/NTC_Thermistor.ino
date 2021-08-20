#include <math.h>

#define VERBOSE 1

int analogPin = A1;

void setup() {
  Serial.begin(9600);
}

double ntcTemperature(int analogPin, bool verbose) {
  double analogData = analogRead(analogPin);
  double resistance = (10240000/analogData) - 10000;
  
  // https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
  double temp = log(resistance);
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;

  if(verbose) {
    Serial.println("NTC Thermistor 10k");
    Serial.print("analog: ");
    Serial.print(analogData);
    Serial.print("    resistance: ");
    Serial.print(resistance);
    Serial.print("    temp: ");
    Serial.print(temp);
    Serial.println("ºC\n");
  }
  
  return temp;
}

void loop() {
  double temp = ntcTemperature(analogPin, true); 
  delay(1000);
}
