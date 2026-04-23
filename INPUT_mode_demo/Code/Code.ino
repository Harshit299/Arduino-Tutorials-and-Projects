const int buttonPin = A0; 
const int ledPin = A1; 

void setup() {
  pinMode(buttonPin, INPUT); 
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) { 
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}


