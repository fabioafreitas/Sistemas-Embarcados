//#include "Arduino.h"
//#include "heltec.h"
#define TINY_GSM_MODEM_SIM800

#include <SoftwareSerial.h>

#define RXD2 16
#define TXD2 17

#define LED_BUILTIN 13

SoftwareSerial mySerial(26, 27);  //RX,TX

void setup() {
    //Heltec.begin(false /*Display*/, false /*LoRa*/, true /*Serial*/);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(300);
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.begin(9600);     // communication with the host computer
    //Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    mySerial.begin(115200);  
    //mySerial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
}

int x = 0;
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void loop() {
    if ((millis() - lastTime) > timerDelay) {
      Serial.print("print ");
      Serial.println(x++);
      lastTime = millis();
    }
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
}
