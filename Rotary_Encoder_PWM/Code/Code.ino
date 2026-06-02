#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Rotary encoder Pins
const int CLK = 2; // output A
const int DT  = 3; // output B

// LED PWM pin
const int LED = 9;

int brightness = 128; // Initial brightness | total range --> 0-255
int lastCLK;

void setup()
{
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(LED, OUTPUT);

  analogWrite(LED, brightness);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  lastCLK = digitalRead(CLK);

  updateDisplay();
}

void loop()
{
  int currentCLK = digitalRead(CLK);

  // check if encoder is rotated or not (only react when CLK makes LOW to HIGH transition i.e rising edge)
  if (currentCLK != lastCLK && currentCLK == LOW)
  {
    // determine direction of rotation
    if (digitalRead(DT) == currentCLK){
      brightness -= 5;  // Clockwise
    }
    else{
      brightness += 5;  // Counter Clockwise
    }

    brightness = constrain(brightness, 0, 255);

    analogWrite(LED, brightness);

    updateDisplay();
  }

  lastCLK = currentCLK;
}

void updateDisplay()
{
  display.clearDisplay();

  int percent = map(brightness, 0, 255, 0, 100);

  // Title
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("LED Brightness");

  // Percentage
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print(percent);
  display.print("%");

  // Percentage bar
  display.drawRect(10, 50, 108, 10, SSD1306_WHITE);

  // Filled Bar
  int barWidth = map(brightness, 0, 255, 0, 106);
  display.fillRect(11, 51, barWidth, 8, SSD1306_WHITE);

  display.display();
}