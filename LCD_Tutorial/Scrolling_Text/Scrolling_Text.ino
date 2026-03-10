#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

String message = "Subscribe to The OHM Lab for more Arduino and ESP32 tutorials     ";

void setup() {
  lcd.init();      // initialize LCD
  lcd.backlight(); // turn on backlight
}

void loop() {

  for (int i = 0; i < message.length(); i++) {

    lcd.clear();
    lcd.setCursor(0, 0);

    // print 16 characters starting from index i
    lcd.print(message.substring(i, i + 16));

    delay(350);
  }
}