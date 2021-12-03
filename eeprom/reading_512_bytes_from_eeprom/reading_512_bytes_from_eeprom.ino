#include <EEPROM.h>
#define EEPROM_SIZE 512

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  for(int i = 0; i < EEPROM_SIZE ; i++) {
    if(i % 16 == 0) {
      Serial.println();
    }
    Serial.print(char(EEPROM.read(i)));
    Serial.print(" ");
  }
}

void loop() {

}
