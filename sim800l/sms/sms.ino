#include <SoftwareSerial.h>
//#defina os pinos TX e RX utilizados com softserial
#define SIM800_TX 8
#define SIM800_RX 9
 
SoftwareSerial sim800(SIM800_TX,SIM800_RX);
 
void setup()
{
  char buffer[20];
  Serial.begin(115200);
  while(!Serial);
   
  Serial.println("Enviando SMS, um momento...");
   
  Serial.write("AT+CMGF=1\r\n");
  Serial.write("AT\r\n");
  Serial.readBytes(buffer, 20);
  Serial.println(buffer);
  for(int i = 0; i < 10 ; i++) 
    delay(1000);
 
  Serial.write("AT+CMGS=\"+5581998309134\"\r\n");
  delay(1000);
   
  Serial.write("SMS do Arduino");   
  Serial.write((char)26);
  delay(1000);
     
  Serial.println("Feito");
}
 
void loop()
{

}
