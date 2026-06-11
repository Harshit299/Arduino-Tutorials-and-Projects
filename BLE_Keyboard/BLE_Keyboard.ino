#include <BleKeyboard.h>

// Initialize BLE Keyboard
BleKeyboard bleKeyboard("ESP32 BLE Keyboard", "Maker", 100);

// Pin Definitions
const int BUTTON_1 = 13; // Bit 0
const int BUTTON_2 = 33; // Bit 1
const int BUTTON_3 = 25; // Bit 2
const int BUTTON_4 = 27; // Bit 3
const int BUTTON_5 = 26; // Bit 4 (Space key)

const int buttonPins[5] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5};

/*  
Keymap Array (Size 32 for 5-bit combinations)
Index 0 is unused (no buttons pressed)
*/
const uint8_t keyMap[32] = {
      0,            // 0: No press
    'a',            // 1: B1 (0 1 1 1 1)
    'b',            // 2: B2 (1 0 1 1 1)
    'c',            // 3: B1+B2 (0 0 1 1 1)
    'd',            // 4: B3 (1 1 0 1 1)
    'e',            // 5: B1+B3 (0 1 0 1 1)
    'f',            // 6: B2+B3
    'g',            // 7: B1+B2+B3
    'h',            // 8: B4
    'i',            // 9: B1+B4
    'j',            // 10: B2+B4
    'k',            // 11: B1+B2+B4
    'l',            // 12: B3+B4
    'm',            // 13: B1+B3+B4
    'n',            // 14: B2+B3+B4
    'o',            // 15: B1+B2+B3+B4
    ' ',            // 16: B5 ONLY (Space)
    'p',            // 17: B1+B5
    'q',            // 18: B2+B5
    'r',            // 19: B1+B2+B5
    's',            // 20: B3+B5
    't',            // 21: B1+B3+B5
    'u',            // 22: B2+B3+B5
    'v',            // 23: B1+B2+B3+B5
    'w',            // 24: B4+B5
    'x',            // 25: B1+B4+B5
    'y',            // 26: B2+B4+B5
    'z',            // 27: B1+B2+B4+B5
    KEY_BACKSPACE,  // 28: B3+B4+B5
    ',',            // 29: B1+B3+B4+B5
    '.',            // 30: B2+B3+B4+B5
    KEY_RETURN      // 31: PRESS ALL BUTTONS (Enter)
};

uint8_t currentChord = 0;
bool isKeyReleased = true;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE Keyboard...");
    bleKeyboard.begin();

    for (int i = 0; i < 5; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void loop() {
    if (bleKeyboard.isConnected()) {
        uint8_t liveState = 0;

        // Read the current state of all 5 buttons
        for (int i = 0; i < 5; i++) {
            // LOW means the button is pressed
            if (digitalRead(buttonPins[i]) == LOW) { 
                liveState |= (1 << i); // Set the corresponding bit
            }
        }

        // Accumulate the pressing of multiple buttons
        if (liveState > 0) {
            currentChord |= liveState;
            isKeyReleased = false;
        } 
        // Fire the keystroke on release
        else {
            if (!isKeyReleased && currentChord > 0) {
                // All keys have been released, lookup the char in the array
                uint8_t charToSend = keyMap[currentChord];

                if (charToSend != 0) {
                    bleKeyboard.write(charToSend);

                    Serial.print("Chord Value: ");
                    Serial.println(currentChord);
                }

                // Reset state for the next keypress
                currentChord = 0;
                isKeyReleased = true;
                delay(50); // Debounce delay
            }
        }
    }
    
    delay(10);
}