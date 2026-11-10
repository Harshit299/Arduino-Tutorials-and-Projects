// hd44780 auto-detects the LCD's I2C address, we don't need to enter the address manually

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <RTClib.h>

hd44780_I2Cexp lcd;   // no address needed, it is detected automatically
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  int status = lcd.begin(16, 2);
  if (status) {
    // LCD not found: blinks the built-in LED
    hd44780::fatalError(status);
  }
  lcd.clear();

  if (!rtc.begin()) {
    lcd.print(F("RTC not found!"));
    while (1);
  }

  // If the RTC lost power or was never set, set it to the compile time
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  static int lastSecond = -1;
  DateTime now = rtc.now();

  if (now.second() != lastSecond) {
    lastSecond = now.second();

    char line1[21];
    char line2[21];

    snprintf(line1, sizeof(line1), "Time:   %02u:%02u:%02u",
             (unsigned)now.hour(), (unsigned)now.minute(), (unsigned)now.second());
    snprintf(line2, sizeof(line2), "Date: %02u.%02u.%04u",
             (unsigned)now.day(), (unsigned)now.month(), (unsigned)now.year());

    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);

    Serial.println(line1);
    Serial.println(line2);
  }

  delay(100);
}
