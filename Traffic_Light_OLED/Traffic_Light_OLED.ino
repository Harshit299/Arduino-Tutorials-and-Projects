#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define LED pins
const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 9;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Initialize the OLED screen (0x3C is the most common I2C address)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); // Loop forever if OLED initialization fails
  }
  
  // Clear the display buffer and set text color
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  // 1. RED LIGHT PHASE (Turns on Red, turns off Green)
  runTrafficPhase(redPin, greenPin, "STOP");

  // 2. YELLOW LIGHT PHASE (Turns on Yellow, turns off Red)
  runTrafficPhase(yellowPin, redPin, "WAIT");

  // 3. GREEN LIGHT PHASE (Turns on Green, turns off Yellow)
  runTrafficPhase(greenPin, yellowPin, "GO");
}

void runTrafficPhase(int turnOnPin, int turnOffPin, String message) {
  // Switch the LEDs
  digitalWrite(turnOnPin, HIGH);
  digitalWrite(turnOffPin, LOW);

  // Run the 3 to 1 countdown
  for (int i = 3; i > 0; i--) {
    display.clearDisplay();

    // Display the phase message (STOP, WAIT, GO)
    display.setTextSize(2);
    display.setCursor(38, 5);
    display.print(message);

    // Display the countdown number
    display.setTextSize(4);
    display.setCursor(52, 28);
    display.print(i);

    // Push the updated graphics to the screen
    display.display();
    
    delay(1000);
  }
}