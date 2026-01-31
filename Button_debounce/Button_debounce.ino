// /* Program with bouncing problem */

// #define button 3

// byte lastButtonState = LOW;

// void setup() {
//   Serial.begin(9600);
//   pinMode(button, INPUT_PULLUP);
// }

// void loop() {
//   byte currentButtonState = digitalRead(button);
//   if (currentButtonState != lastButtonState) {
//     lastButtonState = currentButtonState;
//     if (currentButtonState == LOW) {
//       Serial.println("Button pressed");
//     }
//   }
// }








/* Program with bouncing problem solved */

#define button 3

byte lastButtonState = LOW;

unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  if (millis() - lastTime > 50) {  // debounce time
    byte currentButtonState = digitalRead(button);
    if (currentButtonState != lastButtonState) {
      lastTime = millis();
      lastButtonState = currentButtonState;
      if (currentButtonState == LOW) {
        Serial.println("Button pressed");
      }
    }
  }
}