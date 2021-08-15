#include "serial.h"
#include "lcd.h"
#include "ph.h"
#define BODY_BUFFER_SIZE 50
char body[BODY_BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  init_lcd();
  delay(1000);
}

void loop() {
  delay(5000);
  float phValue = read_ph();
  String phStr = String(phValue, 3);
  print_lcd(phStr);
  snprintf(body, BODY_BUFFER_SIZE, "{\"ph\":%f}", phValue);
  send_serial("/a6b59d", body);              
}
