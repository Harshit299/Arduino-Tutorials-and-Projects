#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int potPin = A0;
int ENA = 6;
int IN1 = 8; // direction pin 1
int IN2 = 7; // direction pin 2

unsigned long lastLCDupdate = 0;

void setup() {

  Serial.begin(9600);

  Wire.setClock(400000);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  lcd.init();
  lcd.backlight();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {

  int potValue = analogRead(potPin);

  int pwmValue = map(potValue, 0,1023, 0,255);
  int speedPercent = map(potValue, 0,1023, 0,100);

  analogWrite(ENA,pwmValue);

  // Update LCD only every 200 ms
  if(millis() - lastLCDupdate > 200) {

    lcd.setCursor(0,0); // top row
    lcd.print("Motor Controller");

    lcd.setCursor(0,1); // bottom row
    lcd.print("Speed:");
    lcd.print(speedPercent);
    lcd.print("%   ");

    lastLCDupdate = millis();
  }
}