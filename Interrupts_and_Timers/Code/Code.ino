/* PROGRAM USING millis() (non-blocking) */

const uint8_t redled = 13;
const uint8_t irSensor = 27;

// Button variables
const uint8_t buttonPin = 14;
const uint8_t buttonLed = 12;
bool lastButtonState = HIGH;
bool buttonLedState = LOW;

// Timing variables
unsigned long currentTime = 0;
volatile unsigned long lastTriggerTime = 0;
volatile bool startTimer = false;

const unsigned long interval = 5000;  // 5 seconds in milliseconds

// ISR
void IRAM_ATTR irISR() {
  lastTriggerTime = millis();
  startTimer = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(irSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irSensor), irISR, FALLING);

  pinMode(redled, OUTPUT);
  digitalWrite(redled, LOW);

  // Button + LED setup
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLed, OUTPUT);
  digitalWrite(buttonLed, LOW);
}

void loop() {
  currentTime = millis();

  // TASK 1: IR interrupt handling
  if (startTimer) {
    digitalWrite(redled, HIGH);
  }

  if (startTimer && (currentTime - lastTriggerTime > interval)) {
    digitalWrite(redled, LOW);
    startTimer = false;
  }

  // TASK 2: Pushbutton handling
  bool currentButtonState = digitalRead(buttonPin);

  // Detect button press (HIGH --> LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    buttonLedState = !buttonLedState;
    digitalWrite(buttonLed, buttonLedState);
  }

  lastButtonState = currentButtonState;
}
























/* PROGRAM USING delay() (blocking)*/

// const uint8_t led = 13;
// const uint8_t irSensor = 27;

// // Button variables
// const uint8_t buttonPin = 14;
// const uint8_t buttonLed = 12;

// bool lastButtonState = HIGH;
// bool buttonLedState = LOW;

// void setup() {
//   Serial.begin(9600);

//   pinMode(irSensor, INPUT_PULLUP);
//   pinMode(led, OUTPUT);
//   digitalWrite(led, LOW);

//   pinMode(buttonPin, INPUT_PULLUP);
//   pinMode(buttonLed, OUTPUT);
//   digitalWrite(buttonLed, LOW);
// }

// void loop() {

//   // TASK 1: IR sensor polling
//   if (digitalRead(irSensor) == LOW) {   // Object detected
//     Serial.println("Object detected");
//     digitalWrite(led, HIGH);

//     // BLOCKING delay
//     delay(5000);

//     digitalWrite(led, LOW);
//     Serial.println("IR LED OFF");
//   }

//   // TASK 2: Pushbutton handling
//   bool currentButtonState = digitalRead(buttonPin);

//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     buttonLedState = !buttonLedState;
//     digitalWrite(buttonLed, buttonLedState);
//   }

//   lastButtonState = currentButtonState;
// }