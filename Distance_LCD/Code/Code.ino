#include <LiquidCrystal_I2C.h>

// LCD I2C address (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 7;
const int echoPin = 6;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Clear any buffer signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH); // in us

  distance = duration * 0.0340 / 2; // in cm (340m/s to 0.0340cm/us)

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm   "); // extra spaces to clear old data

  delay(500);
}