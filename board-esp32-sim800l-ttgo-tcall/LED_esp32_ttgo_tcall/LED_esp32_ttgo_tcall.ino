//#define SIM800L_IP5306_VERSION_20200811
//#include "utilities.h"
#define RELAY 14
void setup() {
  pinMode(RELAY, OUTPUT);
}

void loop() {
  digitalWrite(RELAY, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);                       // wait for a second
  digitalWrite(RELAY, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
