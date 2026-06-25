#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// FC16_HW is the most common for 8x8 matrix modules. 
// If your text displays backward or upside down change this to GENERIC_HW or PAROLA_HW.
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW 
#define MAX_DEVICES 1
#define CS_PIN 9
#define DATA_PIN 8
#define CLK_PIN 10

// Initialize the Parola display object
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// First byte (8) represents the width of the character in columns
// Further 8 bytes map the LED states column by column.

// Smiley Frame 1 (Smile)
uint8_t smileFrame1[] = { 8, 0x7E, 0x81, 0x95, 0xA1, 0xA1, 0x95, 0x81, 0x7E };
// Smiley Frame 2 (Open Mouth)
uint8_t smileFrame2[] = { 8, 0x7E, 0x81, 0x95, 0x91, 0x91, 0x95, 0x81, 0x7E };
// Arrow (Pointing left to match left scrolling effect)
uint8_t arrowSprite[] = { 8, 0x10, 0x38, 0x7C, 0xFE, 0x38, 0x38, 0x38, 0x38 };

uint8_t animState = 0;
uint8_t smileLoops = 0;

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(15); // Set brightness (0 to 15)

  // Map our custom byte arrays to unused ASCII characters so the text engine can use them
  myDisplay.addChar('$', smileFrame1);
  myDisplay.addChar('&', smileFrame2);
  myDisplay.addChar('>', arrowSprite);

  // Start the very first animation (Scrolling Text)
  // Syntax: displayText(text, alignment, speed, pause, effectIN, effectOUT)
  myDisplay.displayText("The OHM Lab", PA_CENTER, 75, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  // displayAnimate() updates the matrix and returns TRUE when an animation fully finishes
  if (myDisplay.displayAnimate()) {
    
    switch (animState) {
      case 0: // State 0: Text just finished. Start Smiley Frame 1.
        animState = 1;
        smileLoops = 0;
        // PA_PRINT displays it instantly. We hold it for 300ms.
        myDisplay.displayText("$", PA_CENTER, 0, 300, PA_PRINT, PA_PRINT);
        break;

      case 1: // State 1: Swap to Smiley Frame 2
        animState = 2;
        myDisplay.displayText("&", PA_CENTER, 0, 300, PA_PRINT, PA_PRINT);
        break;

      case 2: // State 2: Check if we should loop the smile or move to the arrow
        smileLoops++;
        if (smileLoops < 3) { // Animate the mouth 3 times
          animState = 1;
          myDisplay.displayText("$", PA_CENTER, 0, 300, PA_PRINT, PA_PRINT);
        } else {
          animState = 3; // Move to Arrow
          // Scroll the custom arrow character faster than the text (speed: 40)
          myDisplay.displayText(">", PA_CENTER, 40, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        }
        break;

      case 3:
        animState = 0;
        myDisplay.displayText("The OHM Lab", PA_CENTER, 75, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        break;
    }
  }
}
