// instalar a lib DHT 1.4.3 da adafruit no gerenciador de libs

#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void initDHT() {
  dht.begin();
}

void getDht() {
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  Serial.println("-----------------------------------------------------------");
  Serial.println("DHT11");
  
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float heatIndexF = dht.computeHeatIndex(tempF, humidity);
  float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);
  
  Serial.print(F(" Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempC);
  Serial.print(F("ºC "));
  Serial.print(tempF);
  Serial.print(F("ºF  Heat index: "));
  Serial.print(heatIndexC);
  Serial.print(F("C "));
  Serial.print(heatIndexF);
  Serial.println(F("F"));
}
