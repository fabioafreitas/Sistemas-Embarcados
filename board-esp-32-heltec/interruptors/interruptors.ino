#include "Arduino.h"
#include "heltec.h"

#define BTN 22
 
int count = 0;
bool state = false;

void IRAM_ATTR funcao_ISR() {

  // debounce para evitar da função ativar várias vezes seguidas
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) {

    /* inicio da logica da funcao*/
    last_interrupt_time = interrupt_time;
    state = !state;
    digitalWrite(LED_BUILTIN, state);
    Serial.println("ativou");
    /* fim da logica da funca*/
  }
}

void setup() {
  Heltec.begin(true, false, true);
  Serial.begin(9600);
  pinMode(BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), funcao_ISR, FALLING);
}

void loop() {
  Serial.println(++count);
  delay(1000);
}
