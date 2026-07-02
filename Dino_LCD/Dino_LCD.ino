#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define button pins
const int JUMP_BTN = 2;
const int RESET_BTN = 3;

// Custom character for the Dinosaur
byte dino[8] = {
  B00111,
  B00101,
  B00111,
  B10110,
  B11111,
  B01010,
  B01010,
  B00000
};

// Custom character for the Cactus obstacle
byte cactus[8] = {
  B00100,
  B00101,
  B10101,
  B10111,
  B11100,
  B00100,
  B00100,
  B00000
};

// Game Variables
int dinoRow = 1;         // 1 = bottom row, 0 = top row
int cactusCol = 15;      // Starts at the far right of the screen
int score = 0;
int jumpFrames = 0;      // How long the dino stays in the air
int gameSpeed = 200;     // Milliseconds per frame (lower is faster)
bool isGameOver = false;
unsigned long lastFrameTime = 0;

void setup() {
  // Initialize the I2C LCD and turn on the backlight
  lcd.init();
  lcd.backlight();
  
  // Use internal pull-up resistors (buttons read LOW when pressed)
  pinMode(JUMP_BTN, INPUT_PULLUP);
  pinMode(RESET_BTN, INPUT_PULLUP);
  
  // Load custom characters into LCD memory
  lcd.createChar(0, dino);
  lcd.createChar(1, cactus);
  
  // Show Start Screen
  lcd.setCursor(0, 0);
  lcd.print("  Dino Game!  ");
  lcd.setCursor(0, 1);
  lcd.print("Press Jump Pin 8");
  
  // Wait for the player to press jump to start
  while(digitalRead(JUMP_BTN) == HIGH) {
    delay(10);
  }
  lcd.clear();
}

void loop() {
  if (!isGameOver) {
    // If button is pressed (LOW) and dino is on the ground
    if (digitalRead(JUMP_BTN) == LOW && dinoRow == 1) {
      dinoRow = 0;       // Move dino to top row
      jumpFrames = 3;    // Stay up for 3 frames
    }

    // Advance the game frame based on gameSpeed
    if (millis() - lastFrameTime > gameSpeed) {
      
      // Handle jump gravity
      if (dinoRow == 0) {
        jumpFrames--;
        if (jumpFrames <= 0) {
          dinoRow = 1;   // Bring dino back to ground
        }
      }

      // Move cactus left
      cactusCol--;
      
      // If cactus goes off screen, reset it and add a point
      if (cactusCol < 0) {
        cactusCol = 15;
        score++;
        
        // Speed up the game slightly every time an obstacle is cleared
        if (gameSpeed > 60) {
          gameSpeed -= 5; 
        }
      }

      // Collision Detection
      // If cactus is in the same column as the dino and dino is on ground
      if (cactusCol == 1 && dinoRow == 1) {
        isGameOver = true;
      }

      // 4. Draw the Screen
      lcd.clear();
      
      // Draw Dino (always in column 1, row depends on jump)
      lcd.setCursor(1, dinoRow);
      lcd.write(byte(0));
      
      // Draw Cactus
      lcd.setCursor(cactusCol, 1);
      lcd.write(byte(1));
      
      // Draw Score
      lcd.setCursor(12, 0);
      lcd.print(score);

      lastFrameTime = millis();
    }
  } else {
    // GAME OVER STATE 
    lcd.setCursor(0, 0);
    lcd.print("   Game Over!   ");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.print("       ");

    // Wait for Reset Button to be pressed
    if (digitalRead(RESET_BTN) == LOW) {
      resetGame();
      delay(200); // Small debounce delay
    }
  }
}

// Resets all variables to their starting values
void resetGame() {
  isGameOver = false;
  cactusCol = 15;
  score = 0;
  gameSpeed = 200;
  dinoRow = 1;
  jumpFrames = 0;
  lcd.clear();
}