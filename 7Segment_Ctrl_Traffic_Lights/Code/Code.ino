// 7-segment pins (a to g)
int segPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Traffic light pins
int greenLed = 9;
int yellowLed = 10;
int redLed = 11;

// Segment patterns for 0–9 (common cathode)
byte digits[10][7] = {
//{a,b,c,d,e,f,g}
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

void countdown() {
  for (int i = 9; i >= 0; i--) {
    displayDigit(i);
    delay(1000);
  }
}

void loop() {
  // GREEN
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);
  countdown();

  // YELLOW
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, LOW);
  countdown();

  // RED
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);
  countdown();
}