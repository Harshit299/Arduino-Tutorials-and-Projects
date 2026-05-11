#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>

// OLED display 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// MPU6050 
MPU6050 mpu(Wire);

const float shakeThreshold = 2.0; // We can adjust for sensitivity
unsigned long lastRollTime = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  
  // --- UPDATED TEXT SETTINGS ---
  display.setTextSize(2);      // Increased from 1 to 2
  display.setTextColor(WHITE);
  
  // Adjusting cursor to center the larger text
  // Text size 2 is roughly 12 pixels wide per character
  display.setCursor(10, 15);   
  display.println("SHAKE");
  display.setCursor(10, 35);
  display.println("TO ROLL!");
  // -----------------------------

  display.display();

  // Initialize MPU6050
  byte status = mpu.begin();
  if(status != 0) {
    Serial.println(F("MPU6050 not found"));
    while(1);
  }
  
  Serial.println(F("Calibrating... Keep MPU still"));
  mpu.calcOffsets();
  
  randomSeed(analogRead(0)); 
}

void loop() {
  mpu.update();

  // Calculate movement intensity
  float totalAcc = abs(mpu.getAccX()) + abs(mpu.getAccY()) + abs(mpu.getAccZ());

  // Trigger roll if shaken and cooldown time (1s) has passed
  if (totalAcc > shakeThreshold && millis() - lastRollTime > 1000) {
    playRollAnimation();
    int result = random(1, 7);
    drawDice(result);
    lastRollTime = millis();
  }
}

// Function to draw a dice face
void drawDice(int num) {
  display.clearDisplay();
  
  // Draw the dice outline (Rounded Rectangle)
  int x = 44; // Center the 40x40 die on 128px width
  int y = 12;
  int size = 40;
  display.drawRoundRect(x, y, size, size, 5, WHITE);

  // Dot coordinates relative to dice x,y
  int mid = x + size/2;
  int left = x + 10;
  int right = x + 30;
  int top = y + 10;
  int bottom = y + 30;
  int vMid = y + 20;

  // Draw dots based on number
  if (num == 1) {
    display.fillCircle(mid, vMid, 4, WHITE);
  } else if (num == 2) {
    display.fillCircle(left, top, 4, WHITE);
    display.fillCircle(right, bottom, 4, WHITE);
  } else if (num == 3) {
    display.fillCircle(left, top, 4, WHITE);
    display.fillCircle(mid, vMid, 4, WHITE);
    display.fillCircle(right, bottom, 4, WHITE);
  } else if (num == 4) {
    display.fillCircle(left, top, 4, WHITE);
    display.fillCircle(right, top, 4, WHITE);
    display.fillCircle(left, bottom, 4, WHITE);
    display.fillCircle(right, bottom, 4, WHITE);
  } else if (num == 5) {
    display.fillCircle(left, top, 4, WHITE);
    display.fillCircle(right, top, 4, WHITE);
    display.fillCircle(mid, vMid, 4, WHITE);
    display.fillCircle(left, bottom, 4, WHITE);
    display.fillCircle(right, bottom, 4, WHITE);
  } else if (num == 6) {
    display.fillCircle(left, top, 4, WHITE);
    display.fillCircle(right, top, 4, WHITE);
    display.fillCircle(left, vMid, 4, WHITE);
    display.fillCircle(right, vMid, 4, WHITE);
    display.fillCircle(left, bottom, 4, WHITE);
    display.fillCircle(right, bottom, 4, WHITE);
  }

  display.display();
}

void playRollAnimation() {
  for (int i = 0; i < 10; i++) {
    drawDice(random(1, 7));
    delay(50 + (i * 20)); // Gradually slow down the animation
  }
}