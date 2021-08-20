#include <Wire.h>                                                        
                                                           
void setup(){
  Wire.begin();                                                             
  Serial.begin(9600);
  Serial.println("I'm the Master!");
}
void loop(){
  int len = 13;
  Wire.requestFrom(0x01, len); /* request & read data of size 13 from slave */
  char data[len];
  for(int i = 0; Wire.available(); i++) {
    data[i] = Wire.read();
  }
  Serial.println(data);
  
  delay(4000);  

  /*Wire.requestFrom(0x01, 22); // request & read data of size 13 from slave 
  data[22];
  for(int i = 0; Wire.available(); i++) {
    data[i] = Wire.read();
  }
  Serial.println(data);

  delay(2000); */
}
