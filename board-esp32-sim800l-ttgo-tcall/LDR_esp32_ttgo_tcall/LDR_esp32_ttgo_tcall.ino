#define SIM800L_IP5306_VERSION_20200811
#include "utilities.h"
#define sensorPin 36
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
}
