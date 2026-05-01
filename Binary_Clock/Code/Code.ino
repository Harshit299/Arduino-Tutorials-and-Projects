// Pin definitions
const int dataPin  = 10;  // DS
const int clockPin = 8;  // SH_CP
const int latchPin = 9;  // ST_CP

// Time variables
unsigned long previousMillis = 0;
int seconds = 0;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  updateTime();
  displaySeconds(seconds);
}

void updateTime() {
  if (millis() - previousMillis >= 1000) {
    previousMillis += 1000;

    seconds++;

    if (seconds >= 60) {
      seconds = 0;
    }
  }
}

// Send data to 74HC595
void displaySeconds(int value) {
  digitalWrite(latchPin, LOW);

  // Send 8 bits (only lower 6 used)
  shiftOut(dataPin, clockPin, MSBFIRST, value);

  digitalWrite(latchPin, HIGH);
}