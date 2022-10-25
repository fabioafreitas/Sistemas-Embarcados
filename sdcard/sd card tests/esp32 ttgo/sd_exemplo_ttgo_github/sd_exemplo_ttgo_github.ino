// #define SIM800L_IP5306_VERSION_20190610
// #define SIM800L_AXP192_VERSION_20200327
// #define SIM800C_AXP192_VERSION_20200609
#define SIM800L_IP5306_VERSION_20200811
#define ENABLE_SPI_SDCARD   //Uncomment will test external SD card
#include "utilities.h"

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial


#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */

#ifdef ENABLE_SPI_SDCARD

#include "FS.h"
#include "SD.h"
#include <SPI.h>

SPIClass SPI1(HSPI);

#define MY_CS       33
#define MY_SCLK     25
#define MY_MISO     27
#define MY_MOSI     26

void setupSDCard()
{
    SPI1.begin(MY_SCLK, MY_MISO, MY_MOSI, MY_CS);
    //Assuming use of SPI SD card
    if (!SD.begin(MY_CS, SPI1)) {
        Serial.println("Card Mount Failed");
    } else {
        Serial.println("SDCard Mount PASS");
        String size = String((uint32_t)(SD.cardSize() / 1024 / 1024)) + "MB";
        Serial.println(size);
    }
}
#else
#define setupSDCard()
#endif

void setup() {
    // Set console baud rate
    SerialMon.begin(115200);
    delay(10);
    setupSDCard();

}

void loop() {
    //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    //esp_deep_sleep_start();

    /*
    The sleep current using AXP192 power management is about 500uA,
    and the IP5306 consumes about 1mA
    */
}
