//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  float ph = 7.012;
  float temp = 26.23;
  lcd.init();

  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("ph: ");
  lcd.print(String(ph, 3));
  lcd.setCursor(0,1);
  lcd.print("temp: ");
  lcd.print(temp);
  lcd.print(" *C");
  
}


void loop()
{
}
