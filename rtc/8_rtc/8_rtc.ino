//https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/

//#define SIM800L_IP5306_VERSION_20200811
#define SIM800L_AXP192_VERSION_20200327

//#include "utilities.h"

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


// set the RTC timedate to UTC+0, based on UTC-3 (sao paulo)
void setRtcTimeDate() {
    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    
    // it takes almost 2min to compile. I consider this to the setup time correctly
    DateTime compilingTimeCorrection (now + TimeSpan(0,0,2,0));

    DateTime utc0 (compilingTimeCorrection + TimeSpan(0,3,0,0));
    rtc.adjust(utc0);
}

void setup () {
  Serial.begin(115200);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
	
	// Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    setRtcTimeDate();
	
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void test1(DateTime dt) {
    Serial.println("Thingsboard Time Format (Unixtime)");
    uint32_t aux = dt.unixtime();
    Serial.println(aux);
    Serial.println("unixtime with miliseconds");
    Serial.println(String(aux)+"000");
}

void test2(DateTime now) {
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void test3(DateTime now) {
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.println("Unix Time: ");
    Serial.print("elapsed ");
    Serial.print(now.unixtime());
    Serial.print(" seconds/");
    Serial.print(now.unixtime() / 86400L);
    Serial.println(" days since 1/1/1970");
    
    // calculate a date which is 7 days & 30 seconds into the future
    DateTime future (now + TimeSpan(7,0,0,30));
    
    Serial.println("Future Date & Time (Now + 7days & 30s): ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
}

void loop () {
    DateTime now = rtc.now();
    //test1(now);
    test2(now);
    //test3(now);
    delay(2000);
}
