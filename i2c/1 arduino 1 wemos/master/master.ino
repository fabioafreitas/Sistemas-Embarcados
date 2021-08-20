#include <Wire.h>                                                        
                                                           
void setup(){
  Wire.begin();                                                             
  Serial.begin(9600);
  Serial.println("I'm the Master!");
}
void loop(){
  Wire.requestFrom(0x01, 20); /* request & read data of size 13 from slave */
  char data[20];
  for(int i = 0; Wire.available(); i++) {
    data[i] = Wire.read();
  }
  Serial.println(data);
  
  Wire.beginTransmission(0x01);                                                
  Wire.write("Master: Hello Slave!");                                                    
  Wire.endTransmission();
  delay(5000);                                                
}
