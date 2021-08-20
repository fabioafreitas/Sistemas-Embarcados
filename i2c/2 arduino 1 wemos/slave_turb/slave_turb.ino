#include <Wire.h>
                                
void setup() {                   
  Wire.begin(0x01);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);  
  Serial.println("I'm the Slave 1!");                  
}
void loop() {
  delay(100);
}

void receiveEvent(int numBytes) {
  char data[20];
  for(int i = 0; Wire.available(); i++) {
    data[i] = Wire.read();
  }
  Serial.println(data);
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write("Slave 1: Hello Master!");
}
