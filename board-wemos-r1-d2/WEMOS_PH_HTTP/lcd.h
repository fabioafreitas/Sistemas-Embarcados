#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void init_lcd() {
  lcd.init();
}

void print_lcd(String ph_reading) {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("Valor pH");
  lcd.setCursor(5,1);
  lcd.print(ph_reading);
}
