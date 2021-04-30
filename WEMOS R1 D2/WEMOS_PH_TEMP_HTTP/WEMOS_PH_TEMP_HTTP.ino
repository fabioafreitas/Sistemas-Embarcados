#include <OneWire.h>                
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>



// SENSOR VARIABLES
OneWire ourWire(D8);                
DallasTemperature tempSensor(&ourWire);
float calibration = 23.00;
const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;




// NETWORK VARIABLES
#define BODY_BUFFER_SIZE  (50)
char body[BODY_BUFFER_SIZE];
unsigned long lastMsg = 0;
const char* ssid = "BBG_JOSELITO";
const char* password = "Singularidade10";
const char* http_server = "http://dojot-testes.duckdns.org:5000";







// leitura do sensor de ph
float read_ph() {
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(analogInPin);
    delay(30);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)
  avgValue += buf[i];
  float pHVol = (float)avgValue * 3.3 / 1024 / 6; //dividir por 3.3, pois estou usando um regulador de tensao 5v 3.3v
  float phValue = -5.70 * pHVol + calibration;
  //Serial.print("PH = ");
  //Serial.println(phValue);
  return phValue;
}






// leitura do sensor de temperatura
float read_temp() {
  tempSensor.requestTemperatures();  
  float tempValue= tempSensor.getTempCByIndex(0);
  Serial.print("Temp = ");
  Serial.print(tempValue);
  Serial.println(" C");
  return tempValue;
}







void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}





void setup() {
  Serial.begin(115200);
  tempSensor.begin();
  setup_wifi();
  delay(1000);
}



void sendJson(String uri) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(http_server+uri);
    http.addHeader("Content-Type", "application/json");
    Serial.println(body);
    int httpCode = http.POST(body);
    Serial.println(httpCode);
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    http.end();   //Close connection
  }
}



void loop() {
  unsigned long now = millis();
  if (now - lastMsg > 3000) {
    float phValue = read_ph();
    float tempValue = read_temp();
    snprintf(body, BODY_BUFFER_SIZE, "{\"temperature\":%f,\"ph\":%f}", tempValue, phValue);
    sendJson("/ec94d3");
  }                 
}
