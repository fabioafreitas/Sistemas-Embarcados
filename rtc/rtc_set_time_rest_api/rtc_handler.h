#ifndef _RTC_HANDLER_H_
#define _RTC_HANDLER_H_

#define RTC_HANDLER_DEBUG_MODE

#include "wifi_handler.h"

#include <WiFi.h>
#include <Wire.h>
#include <HTTPClient.h>
#include "RTClib.h"
#include "ArduinoJson.h"

RTC_DS3231 rtc;


// return unixtime (int) or -1 if an error occurs
int getDateTimeGMT() {
  
  #ifdef RTC_HANDLER_DEBUG_MODE
  Serial.println("-----------------------------------------------------------");
  #endif

  initWiFiStation();

  if(WiFi.status()!= WL_CONNECTED){
    #ifdef RTC_HANDLER_DEBUG_MODE
    Serial.println("[RTC] WiFi Disconnected");
    #endif
    return -1;
  }
 
  // requisição http get
  HTTPClient http;
  String uri = "https://worldtimeapi.org/api/timezone/America/Sao_Paulo";
  http.begin(uri);
  int httpResponseCode = http.GET();

  #ifdef RTC_HANDLER_DEBUG_MODE
  Serial.print("[RTC] Response code: ");
  Serial.println(httpResponseCode);
  #endif

  if(httpResponseCode <= 0 || httpResponseCode != 200){
    #ifdef RTC_HANDLER_DEBUG_MODE
    Serial.print("[RTC] Error on sending GET: ");
    Serial.println(httpResponseCode);
    #endif
    return -1;
  }
  
  String json = http.getString();
  #ifdef RTC_HANDLER_DEBUG_MODE
  Serial.print("[RTC] JSON: ");
  Serial.println(String(json));
  #endif
  
  DynamicJsonDocument doc(512);
  deserializeJson(doc, json);
  int unixTime = doc["unixtime"];
  #ifdef RTC_HANDLER_DEBUG_MODE
  Serial.print("[RTC] Unixtime: ");
  Serial.println(unixTime);
  #endif

  http.end();
  
  return unixTime;
}


// set the RTC timedate to UTC+0
void setRtcTimeDate(int unixTime) {
  rtc.adjust(DateTime(unixTime));
}

DateTime getDateTimeNow() {
  DateTime now = rtc.now();

  #ifdef RTC_HANDLER_DEBUG_MODE
  String utc = \
    String(now.year())  +"-"+ \
    String(now.month()) +"-"+ \
    String(now.day())   +"T"+ \
    String(now.hour())  +":"+ \
    String(now.minute())+":"+ \
    String(now.second())+"Z";
  Serial.print("[RTC] UTC ISO8601: ");
  Serial.println(utc);
  
  Serial.print("[RTC] UTC Unixtime: ");
  Serial.println(now.unixtime());
  #endif
  
  return now;
}



void initRTC() {
  if (!rtc.begin()) {
    #ifdef RTC_HANDLER_DEBUG_MODE
    Serial.println("[RTC] Couldn't find RTC");
    #endif
    while (1);
  }

  // if not lost power, do nothing
  if (!rtc.lostPower()) {
    return;
  }
  
  #ifdef RTC_HANDLER_DEBUG_MODE
  Serial.println("[RTC] lost power, lets set the time!");
  #endif

  int gmt = getDateTimeGMT();
  if(gmt == -1) {
    #ifdef RTC_HANDLER_DEBUG_MODE
    Serial.println("[RTC] time not set up, didn't receive GMT");
    #endif
    return;
  }
  
  setRtcTimeDate(gmt);
}
#endif /*_RTC_HANDLER_H_*/
