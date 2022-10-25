#ifndef _LED_H_
#define _LED_H_

#ifndef RED_LED_PIN   
#define RED_LED_PIN   23
#endif

#ifndef GREEN_LED_PIN 
#define GREEN_LED_PIN 2
#endif


void redOn() {
  digitalWrite(RED_LED_PIN, HIGH);
}

void redOff() {
  digitalWrite(RED_LED_PIN, LOW);
}

void greenOn() {
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void greenOff() {
  digitalWrite(GREEN_LED_PIN, LOW);
}

void initLED() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  redOff();
  greenOff();
}



#endif /* _LED_H_ */
