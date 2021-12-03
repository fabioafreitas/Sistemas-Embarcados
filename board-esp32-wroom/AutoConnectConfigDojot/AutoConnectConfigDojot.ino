#include <WiFi.h>          // Replace with WiFi.h for ESP32
#include <WebServer.h>     // Replace with WebServer.h for ESP32
#include <AutoConnect.h>

static const char DOJOT_CONFIG[] PROGMEM = R"(
{
  "title": "Dojot Config",
  "uri": "/",
  "menu": true,
  "element": [
    {
      "name": "header1",
      "type": "ACText",
      "value": "<h2>Dojot Settings</h2>",
      "style": "text-align:center;color:#2f4f4f;"
    },
    {
      "name":"caption",
      "type":"ACText",
      "value":"<h3>Current settings shown in the input fields bellow, to reconfigure change the data and click in save.</h3>",
      "style":"font-family:serif;color:#4682b4;"
    },
    {
      "name": "dojotServer",
      "type": "ACInput",
      "label": "Server   ",
      "placeholder":"example.com",
      "value":""
    },
    {
      "name": "deviceID",
      "type": "ACInput",
      "label":"Device ID",
      "placeholder": "caf4f",
      "value":""
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "SAVE",
      "uri": "/save"
    }
  ]
}
)";

static const char DOJOT_SAVE[] PROGMEM = R"(
{
  "title": "Dojot Results",
  "uri": "/save",
  "menu": false,
  "element": [
    {
      "name": "header2",
      "type": "ACText",
      "value": "<h2>Settings Saved Succesfully</h2>",
      "style": "text-align:center;color:#2f4f4f;"
    },
    {
      "name": "save",
      "type": "ACText",
      "style":"font-family:serif;color:#4682b4;"
    },
    {
      "name": "home",
      "type": "ACSubmit",
      "value": "HOME",
      "uri": "/"
    }
  ]
}
)";

WebServer       server;
AutoConnect     portal(server);
AutoConnectAux  dojot_config;
AutoConnectAux  dojot_save;

String onLoad(AutoConnectAux& aux, PageArgument& args) {
  //[TODO] carregar dados do EEPROM
  aux["dojotServer"].as<AutoConnectInput>().value = "fabiotest.online";
  aux["deviceID"].as<AutoConnectInput>().value = "caf4f";
  return String();
}

String onSave(AutoConnectAux& aux, PageArgument& args) {

  String dojotServer = args.arg("dojotServer");
  String deviceID = args.arg("deviceID");

  aux["save"].as<AutoConnectText>().value = \
    "<h3>Server: " + String(dojotServer) + "</h3>" \
    "<h3>Device Id: " + String(deviceID) + "</h3>";
  
  return String();
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  dojot_config.load(DOJOT_CONFIG);
  dojot_save.load(DOJOT_SAVE);
  portal.join({ dojot_config, dojot_save });
  portal.on("/", onLoad);
  portal.on("/save", onSave);
  portal.begin();
}

unsigned long lastMsg = 0;
void loop() {
  portal.handleClient();

  unsigned long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    Serial.println(portal.getEEPROMUsedSize());
  }
}
