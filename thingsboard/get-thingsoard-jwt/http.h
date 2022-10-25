#ifndef _HTTP_H_
#define _HTTP_H_

#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

#define JSON_BUFFER_SIZE (300)
char json[JSON_BUFFER_SIZE];
const char* hostname = "http://thingsboard.smartrural.com.br";
const char* username = "fbio.alves095@gmail.com";
const char* password = "QVt$D3%8V8!Z0B";

// return the next Quote Char Index, based on a initPosition
// returns -1 if dont find it
int findQuoteIndex(String json, int initPosition) {
  for(int i = initPosition ; i < json.length() ; i++ ) {
    if(String(json.charAt(i)) ==  String("\"")) {
      return i;
    }
  }
  return -1;
}

String getJwt(String json) {
  int iniIndex, endIndex = -1;
  String key = "";
  while(key != "token") {
    iniIndex = endIndex+1;
    iniIndex = findQuoteIndex(json, iniIndex);
    endIndex  = findQuoteIndex(json, iniIndex+1);
    key = json.substring(iniIndex+1, endIndex);
  }
  iniIndex = findQuoteIndex(json, endIndex+1);
  endIndex  = findQuoteIndex(json, iniIndex+1);
  return json.substring(iniIndex+1, endIndex);
}

// return true of http code is 200, false if not
void getJwt() {
  #ifdef DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  #endif
  if(WiFi.status()== WL_CONNECTED){
      snprintf (json, JSON_BUFFER_SIZE, \
      "{" \
        "\"username\":\"%s\"," \
        "\"password\":\"%s\""
      "}", \
      username, password);

    // requisição http post
    HTTPClient http;
    String uri = String(hostname) + "/api/auth/login";
    http.begin(uri);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    int httpResponseCode = http.POST(json);

    if(httpResponseCode>0){

        String json = http.getString();
        Serial.println(String(json));
        String jwt = getJwt(json);
        Serial.println(String(jwt));

        /*
         * DAQUI PARA BAIXO COLOCAR O CÓDIGO DE PEGAR A TELEMETRIA DO SERVIDOR
         */
        
    }else{
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
    
    #ifdef DEBUG_MODE
    Serial.print("[HTTP] Response code: ");
    Serial.println(httpResponseCode);
    #endif
    
    http.end();
  }
  else {
    #ifdef DEBUG_MODE
    Serial.println("[HTTP] WiFi Disconnected");
    #endif
  }
}

#endif /*_HTTP_H_*/
