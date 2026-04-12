// Code using delay function

#define buzzer 8

// Pattern selection
int mode;  
// 1 = Normal
// 2 = Warning
// 3 = Critical
// 4 = Emergency

#define btn1 4
#define btn2 5
#define btn3 6
#define btn4 7

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(btn1) == LOW){
    mode = 1;
  }
  else if (digitalRead(btn2) == LOW){
    mode = 2;
  }
  else if (digitalRead(btn3) == LOW){
    mode = 3;
  }
  else if (digitalRead(btn4) == LOW){
    mode = 4;
  }

  // Run pattern based on mode
  switch (mode) {
    case 1:
      Serial.println("Normal | btn1");
      normalAlert();
      break;
    case 2:
      Serial.println("alert | btn2");
      warningAlert();
      break;
    case 3:
      Serial.println("warning | btn3");
      criticalAlert();
      break;
    case 4:
      Serial.println("emergency | btn4");
      emergencyAlert();
      break;
  }
}

// Pattern 1: Normal Alert (slow beeps)
void normalAlert() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(800);
}

// Pattern 2: Warning (medium speed)
void warningAlert() {
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}

// Pattern 3: Critical (long beep)
void criticalAlert() {
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer, LOW);
  delay(1000);
}

// Pattern 4: Emergency (fast beeps)
void emergencyAlert() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}


// Code using millis function

// #define buzzer 8
// #define btn1 4
// #define btn2 5
// #define btn3 6
// #define btn4 7

// int mode = 0;

// // Buzzer state
// bool buzzerOn = false;
// unsigned long lastBuzzerTime = 0;

// // {mode1, mode2, mode3, mode4}
// unsigned int onTime[]  = {200, 500, 2000, 100};
// unsigned int offTime[] = {800, 500, 1000, 100};
// /*                        ^    ^     ^     ^ 
//                           |    |     |     |
//                         mode1 mode2 mode3 mode4*/

// void setup() {
//   Serial.begin(9600);
//   pinMode(buzzer, OUTPUT);
//   pinMode(btn1, INPUT_PULLUP);
//   pinMode(btn2, INPUT_PULLUP);
//   pinMode(btn3, INPUT_PULLUP);
//   pinMode(btn4, INPUT_PULLUP);
// }

// void loop() {
//   // Buttons are checked every loop iteration
//   if (digitalRead(btn1) == LOW)      { mode = 1; Serial.println("Normal | btn1"); }
//   else if (digitalRead(btn2) == LOW) { mode = 2; Serial.println("Warning | btn2"); }
//   else if (digitalRead(btn3) == LOW) { mode = 3; Serial.println("Critical | btn3"); }
//   else if (digitalRead(btn4) == LOW) { mode = 4; Serial.println("Emergency | btn4"); }

//   // Run non-blocking buzzer pattern
//   if (mode > 0) {
//     runBuzzer(onTime[mode - 1], offTime[mode - 1]);
//   }
// }

// void runBuzzer(unsigned int onDuration, unsigned int offDuration) {
//   unsigned long now = millis();
//   unsigned int waitTime = buzzerOn ? onDuration : offDuration;

//   // just checks if enough time has passed each loop.
//   if (now - lastBuzzerTime >= waitTime) {
//     buzzerOn = !buzzerOn;
//     digitalWrite(buzzer, buzzerOn ? HIGH : LOW);
//     lastBuzzerTime = now;
//   }
// }