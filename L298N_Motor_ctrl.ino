const int btn1 = 2;
const int btn2 = 3;

// Motor 1 pins
const int M1_IN1 = 6; // direction 1
const int M1_IN2 = 7; // direction 2

// Motor 2 pins 
const int M2_IN1 = 8; // direction 1
const int M2_IN2 = 9; // direction 2

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);

  stopMotors();
}

void loop() {
  bool b1 = digitalRead(btn1) == LOW;  // button pressed
  bool b2 = digitalRead(btn2) == LOW;  // button pressed

  // Logic 1: No button pressed
  if(!b1 && !b2) {
    stopMotors();
  }

  // Logic 2: Button 1 pressed only
  else if(b1 && !b2) {
    motor1Clockwise();
    motor2Clockwise();
  }

  // Logic 3: Button 2 pressed only
  else if(b2 && !b1) {
    motor1AntiClockwise();
    motor2AntiClockwise();
  }

  // If both pressed, stop
  else {
    stopMotors();
  }
}

void stopMotors() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
}

void motor1Clockwise() {
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);
}

void motor1AntiClockwise() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, HIGH);
}

void motor2Clockwise() {
  digitalWrite(M2_IN1, HIGH);
  digitalWrite(M2_IN2, LOW);
}

void motor2AntiClockwise() {
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, HIGH);
}