//#include "Arduino.h"
//#include "heltec.h"
#include <Preferences.h>

Preferences preferences;

const char* server = "google";
const char* deviceID = "abcdefg";

void setup() {
  delay(2000);
  //Heltec.begin(false, false, true);
  delay(1000);
  Serial.begin(115200);
  Serial.println("init");

  preferences.begin("dojot", false);
  preferences.putString("server", server); 
  preferences.putString("deviceID", deviceID);

  Serial.println("Dojot Credentials Saved using Preferences");

  preferences.end();


  for(int i = 0; i < 5 ; i++) {
    Serial.print(".");
    delay(1000);
  }

  String server2;
  String deviceID2;
  preferences.begin("dojot", false);
 
  server2 = preferences.getString("server2", ""); 
  deviceID2 = preferences.getString("deviceID2", "");

  if (server2 == "" || deviceID2 == ""){
    Serial.println("No values saved for server or deviceID");
  }
  else {
    Serial.println("Server: " + server2);
    Serial.println("deviceID: " + deviceID2);  
  }
}

void loop() {

}
