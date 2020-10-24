#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int ledTempPin = 2; //GPIO 2 = D4
int ledPhPin = 5; // GPIO5 = D1

const char* ssid = "BBG_JOSELITO";
const char* password = "Singularidade10";

//Adicione ou retire um comentário no inpicio da linha abaixo para trocar de url
//String url = "http://iot-aquacultura.duckdns.org";/*
String url = "http://a0c39a8297cd.ngrok.io";//*/

//gerencia se os leds acendem ou apagam
void ledsHandler(char ledTemp, char ledPh) {
  if(ledTemp == 'H') 
    digitalWrite(ledTempPin, HIGH);
  else 
    digitalWrite(ledTempPin, LOW);

  if(ledPh == 'H') 
    digitalWrite(ledPhPin, HIGH);
  else 
    digitalWrite(ledPhPin, LOW);
}

void sendJson(String uri, String temp, String pH) {
  char ledStatus;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, url+uri);
    http.addHeader("Content-Type", "application/json");
    String body = "{\"temperature\":";
    body.concat(temp);   
    body.concat(",\"ph\":");
    body.concat(pH);
    body.concat("}");
    

    int httpCode = http.POST(body);
    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        /* CASO UMA MUDANCA SEJA REALIZADA NO METODO POST DO
         * SERVER.PY EH IMPORTANTE OBSERVAR DA RESPOSTA EM ORDEM
         * ALFABETICA, POIS ISSO PODE ALTERAR OS LEDS QUE ACENDEM
         */
//        const String& serverResponse = http.getString();
//        ledsHandler(serverResponse[10], serverResponse[24]);
        String payload = http.getString();
        const size_t capacity = JSON_OBJECT_SIZE(2) + 20;
        DynamicJsonDocument doc(capacity);
        
        char json[payload.length()];
        //char* json = "{\"ledPh\":\"L\",\"ledTemp\":\"L\"}";
        payload.toCharArray(json, payload.length());

        Serial.println(payload);
        Serial.println(json);
        
        
        deserializeJson(doc, json);

        const char* ledPh = doc["ledPh"]; // "L"
        const char* ledTemp = doc["ledTemp"]; // "L"
        Serial.print("ledTemp = ");
        Serial.println(ledTemp);
        Serial.print("ledPh = ");
        Serial.println(ledPh);
        ledsHandler(ledTemp[0], ledPh[0]);
      }
      http.end();   //Close connection
    }
  }
}


void setup() {
  pinMode(ledTempPin, OUTPUT);
  pinMode(ledPhPin, OUTPUT);
  Serial.begin(9600);
  Serial.print("\nTrying to connect to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("\nConnected succesfully with IP ");
  Serial.println(WiFi.localIP());
  Serial.println("\n\n");
}

void loop() {
  String temp = Serial.readStringUntil(';'); //primeira leitura é da temperatura
  String ph = Serial.readStringUntil(';'); //segunda leitura é do ph
  delay(500);
  sendJson("/save", "30", "6");
  delay(2500);
}
