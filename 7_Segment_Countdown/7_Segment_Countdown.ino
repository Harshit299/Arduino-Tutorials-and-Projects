// Pin connections for the 7 segments (a to g)
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// 2D Array mapping the numbers 0-9 to the 7 segments (a,b,c,d,e,f,g)
// 1 = HIGH (Segment ON), 0 = LOW (Segment OFF)
const byte numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Countdown from 9 down to 0
  for (int digit = 9; digit >= 0; digit--) {
    displayNumber(digit);
    delay(1000);
  }
}

void displayNumber(int num) {
  for (int segment = 0; segment < 7; segment++) {
    digitalWrite(segmentPins[segment], numbers[num][segment]);
  }
}