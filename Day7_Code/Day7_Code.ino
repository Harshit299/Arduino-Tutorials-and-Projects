const int buttonPin = 2;

const int segPins[7] = {3, 4, 5, 6, 7, 8, 9};

int digits[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

bool timerStarted = false;
int count = 0;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  displayDigit(0);
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !timerStarted) {
    delay(200);
    timerStarted = true;
    count = 0;
    previousMillis = millis();
    displayDigit(count);
  }

  if (timerStarted) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      count++;

      if (count <= 9) {
        displayDigit(count);
      } else {
        timerStarted = false;
      }
    }
  }
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}