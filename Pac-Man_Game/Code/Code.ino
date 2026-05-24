#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Joystick Pins
#define VRX A0
#define VRY A1
#define SW  2

#define buzzer 13

// Pacman
int pacX = 10;
int pacY = 10;
int pacSize = 6;

// Food
int foodX = 50;
int foodY = 30;

int score = 0;

void setup() {
  Serial.begin(9600);

  pinMode(SW, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while(1);
  }

  display.clearDisplay();
}

void loop() {

  if(digitalRead(SW) == LOW) {

    score = 0;

    pacX = 10;
    pacY = 10;

    foodX = random(10, 120);
    foodY = random(15, 60);

    delay(300);
  }

  int xValue = analogRead(VRX);
  int yValue = analogRead(VRY);

  Serial.print("xValue = ");
  Serial.print(xValue);
  Serial.print(" | yValue = ");
  Serial.println(yValue);

  // Movement
  if(yValue < 400) {
    pacX -= 2;
  }

  if(yValue > 600) {
    pacX += 2;
  }

  if(xValue < 400) {
    pacY += 2;
  }

  if(xValue > 600) {
    pacY -= 2;
  }

  // Boundary
  if(pacX < 0) pacX = 0;
  if(pacX > 122) pacX = 122;

  if(pacY < 10) pacY = 10;
  if(pacY > 58) pacY = 58;

  // Collision with food
  if(abs(pacX - foodX) < 6 && abs(pacY - foodY) < 6) {

    score++;
    tone(buzzer, 1000);
    delay(100);
    noTone(buzzer);

    foodX = random(10, 120);
    foodY = random(15, 60);
  }

  // Display
  display.clearDisplay();

  // Score
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Score: ");
  display.print(score);

  // Draw Food
  display.fillCircle(foodX, foodY, 2, WHITE);

  // Draw Pacman
  display.fillCircle(pacX, pacY, pacSize, WHITE);

  // Mouth
  display.fillTriangle(
    pacX, pacY,
    pacX + 6, pacY - 4,
    pacX + 6, pacY + 4,
    BLACK
  );

  // Border
  display.drawRect(0, 10, 128, 54, WHITE);

  display.display();

  delay(40);
}