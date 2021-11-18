#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>




const int relay1 = D2;
const int relay2 = D3;




const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<a href="frente" style="font-size: 50px">frente</a><br>
<a href="re" style="font-size: 50px">re</a><br>
<hr>
</center>

</body>
</html>
)=====";





//SSID and Password of your WiFi router
const char* ssid = "fabio_ap";
const char* password = "capivara123";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80





void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}




void frente() {
  digitalWrite(relay1, HIGH); digitalWrite(relay2, LOW);
  delay(1000);
  digitalWrite(relay1, LOW); digitalWrite(relay2, LOW);

  server.sendHeader("Location","/");
  server.send(303);
}

void re() {
  digitalWrite(relay1, LOW); digitalWrite(relay2, HIGH);
  delay(1000);
  digitalWrite(relay1, LOW); digitalWrite(relay2, LOW);

  server.sendHeader("Location","/");
  server.send(303);
}





void setup(void){
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/frente", frente);
  server.on("/re", re);

  server.begin();
  Serial.println("HTTP server started");

  int led = D12;
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}




void loop(void){
  server.handleClient();
}
