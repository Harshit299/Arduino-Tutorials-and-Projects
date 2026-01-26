const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int buttonPin = 5;

int state = 0;
bool lastButtonState = HIGH;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  turnOffAll();
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Detect button press (pressed = LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    state++;
    if (state > 3) state = 1;

    updateTrafficLight();
    delay(200);
  }

  lastButtonState = currentButtonState;
}

void updateTrafficLight() {
  turnOffAll();

  if (state == 1) digitalWrite(redLED, HIGH);
  else if (state == 2) digitalWrite(yellowLED, HIGH);
  else if (state == 3) digitalWrite(greenLED, HIGH);
}

void turnOffAll() {
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}