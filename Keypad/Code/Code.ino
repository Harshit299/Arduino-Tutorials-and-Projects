#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// If 0x27 doesn't work, try 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

// Define the Keymap matching the 4x4 keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW1, ROW2, ROW3, ROW4 to these pins.
byte rowPins[ROWS] = {9, 8, 7, 6}; 
// Connect keypad COL1, COL2, COL3, COL4 to these pins.
byte colPins[COLS] = {5, 4, 3, 2}; 

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Initialize the LCD
  lcd.init();      
  lcd.backlight(); 
  
  lcd.setCursor(0, 0);
  lcd.print("Waiting for key.");
}

void loop() {
  // Read the key pressed
  char key = keypad.getKey();

  // If a key was pressed, update the LCD
  if (key) {
    lcd.clear(); // Clear previous screen
    
    // Top Row: "Key Pressed"
    lcd.setCursor(0, 0);
    lcd.print("Key Pressed");
    
    // Bottom Row: The actual key character
    lcd.setCursor(0, 1);
    lcd.print(key);
  }
}