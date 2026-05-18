// these pins CAN be non-PWM
const int dataPin  = 9;
const int clockPin = 8;
const int latchPin = 10;

// Scanner Variables
int position = 0; // which led
int direction = 1; // moving left or right 

// Brightness levels for trail
byte ledBrightness[8];

// we can increase this to slow down the scanner movement and vice-versa
const int framesPerStep = 16; 

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {

  // 1. Calculate the new frame
  // Frame is one complete visual state of all LEDs at a particular moment

  // Fade all 8 LEDs to create trailing(moving) effect
  for (int i = 0; i < 8; i++) {
     
    // Right shifting by 2 (>> 2) divides the value by 4.
    ledBrightness[i] >>= 2;   

    // HARD CUTOFF: if led gets too dim turn it completely off.
    if (ledBrightness[i] < 15) {
      ledBrightness[i] = 0;
    }
    
  }
  
  // Set current LED to full brightness
  ledBrightness[position] = 255;

  // 2. Render the frame (Software PWM)
  for (int frame = 0; frame < framesPerStep; frame++) {

    for (int pwm = 0; pwm < 255; pwm += 15) {
      
      byte output = 0; // group of LEDs that should be ON right now

      for (int i = 0; i < 8; i++) {
        if (ledBrightness[i] > pwm) {
          // Shift a '1' left by 'i' positions, and OR it with the output byte.
          output |= (1 << i);
        }
      }

      sendToShiftRegister(output);
      delayMicroseconds(100); 
    }
  }

  // 3. Move scanner for the next loop iteration
  position += direction;

  // Reverse at ends
  if (position >= 7) {
    position = 7;
    direction = -1;
  } else if (position <= 0) {
    position = 0;
    direction = 1;
  }
}

// Send Data to 74HC595
void sendToShiftRegister(byte data) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}