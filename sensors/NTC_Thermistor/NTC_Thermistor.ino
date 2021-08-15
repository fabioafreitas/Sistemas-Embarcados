#include <math.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  /*int temperature = temp.getTemp();
  Serial.print("Temperatura no Sensor eh: ");
  Serial.print(String(temperature, 5));
  Serial.println("*C");
  */

  double analogData = analogRead(A0);
  Serial.print("Analog: ");
  Serial.println(analogData);

  double resistance = (10240000/analogData) - 10000;
  Serial.print("resistance: ");
  Serial.println(resistance);

  double temp = log(resistance);
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;
  Serial.print("temp: ");
  Serial.println(temp);
  delay(1000);
}
