//https://naylampmechatronics.com/blog/46_Tutorial-sensor-de-temperatura-DS18B20.html

#include <OneWire.h>                
#include <DallasTemperature.h>

OneWire ourWire(27);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

void setup() {
  Serial.begin(115200);
  sensors.begin();   //Se inicia el sensor
}
 
void loop() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  
  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.println(" C");
  delay(500);
  
}
