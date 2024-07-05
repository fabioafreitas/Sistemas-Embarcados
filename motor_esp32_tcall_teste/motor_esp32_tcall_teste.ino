#define SIM800L_AXP192_VERSION_20200327
#define MOTOR 2
#include "utilities.h"

void setup() {
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  delay(2000);
  digitalWrite(MOTOR, HIGH);
  delay(2000);
  digitalWrite(MOTOR, LOW);
}
