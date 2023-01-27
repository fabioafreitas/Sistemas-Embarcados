# 1 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino"


# 4 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino" 2
# 5 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino" 2

//#define TEST_HTTP_GET




// Your GPRS credentials (leave empty, if not needed)
const char apn[] = "zap.vivo.com.br";
const char gprsUser[] = "vivo"; // GPRS User
const char gprsPass[] = "vivo"; // GPRS Password

// SIM card PIN (leave empty, if not defined)
const char simPIN[] = "";

// Server details
const char server[] = "712d-200-17-137-180.sa.ngrok.io"; // domain name: example.com
const char resource[] = "/"; // resource path, for example: /post-data.php
const int port = 80;


// Set serial for debug console (to Serial Monitor, default speed 115200)

// Set serial for AT commands (to SIM800 module)


// Configure TinyGSM library



// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS

# 38 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino" 2
# 39 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino" 2






  TinyGsm modem(Serial1);


// TinyGSM Client for Internet connection
TinyGsmClient client(modem);







void setup() {
  // Set serial monitor debugging window baud rate to 115200
  Serial.begin(115200);

  // Set modem reset, enable, power pins
  pinMode(4, 0x03);
  pinMode(5, 0x03);
  pinMode(23, 0x03);
  digitalWrite(4, 0x0);
  digitalWrite(5, 0x1);
  digitalWrite(23, 0x1);

  // Set GSM module baud rate and UART pins
  Serial1.begin(115200, 0x800001c, 26, 27);
  //delay(3000);

  // Restart SIM800 module, it takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  modem.restart();
  //modem.init(); // if you don't need the complete restart

  // Unlock your SIM card with a PIN if needed
  if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
    modem.simUnlock(simPIN);
  }

  // Configure the wake up source as timer wake up  
  esp_sleep_enable_timer_wakeup(3600 /* Time ESP32 will go to sleep (in seconds) 3600 seconds = 1 hour */ * 1000000UL /* Conversion factor for micro seconds to seconds */);
}

void loop() {
  Serial.print("Connecting to APN: ");
  Serial.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println(" fail");
    return;
  }

  Serial.println(" OK");

  Serial.print("Connecting to ");
  Serial.print(server);
  if (!client.connect(server, port)) {
    Serial.println(" fail");
    esp_deep_sleep_start();
  }

    Serial.println(" OK");
# 114 "c:\\Users\\fbioa\\Desktop\\dev\\firmware-mestrado\\test-scripts\\1_gprs_http\\1_gprs_http.ino"
    Serial.println("Performing HTTP POST request...");
    String httpRequestData = "{\"test\":\"post\"}";
    client.print(String("POST ") + resource + " HTTP/1.1\r\n");
    client.print(String("Host: ") + server + "\r\n");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(httpRequestData.length());
    client.println();
    client.print(httpRequestData + "\r\n\r\n");


  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 10000L) {
    // Print available data (HTTP response from server)
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      timeout = millis();
    }
  }
  Serial.println();

  // Close client and disconnect
  client.stop();
  Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("Server disconnected")))));
  modem.gprsDisconnect();
  Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("GPRS disconnected")))));


  // Put ESP32 into deep sleep mode (with timer wake up)
  esp_deep_sleep_start();
}
