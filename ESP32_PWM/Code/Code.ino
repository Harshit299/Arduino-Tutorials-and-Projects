#define pwm_pin   18    // PWM pin (ENA)
#define dir1_pin  19    // Direction pin 1 (IN1)
#define dir2_pin  21    // Direction pin 2 (IN2)

// PWM Configuration
#define pwm_freq 1000  // 1 kHz
#define pwm_res 8     // 8-bit resolution(0–255)

void setup() {
  Serial.begin(9600);

  pinMode(dir1_pin, OUTPUT);
  pinMode(dir2_pin, OUTPUT);

  // attach pwm pin 
  ledcAttach(pwm_pin, pwm_freq, pwm_res);
}

// Set motor speed (-255 to 255) --> -255 to 0 to 255
void setMotorSpeed(int speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {
    digitalWrite(dir1_pin, HIGH);
    digitalWrite(dir2_pin, LOW);
    ledcWrite(pwm_pin, speed);
  }
  else if (speed < 0) {
    digitalWrite(dir1_pin, LOW);
    digitalWrite(dir2_pin, HIGH);
    ledcWrite(pwm_pin, -speed);
  }
  else {
    digitalWrite(dir1_pin, LOW);
    digitalWrite(dir2_pin, LOW);
    ledcWrite(pwm_pin, 0); // stop the motor
  }
}

void loop() {

  // speed increasing
  for (int speed = 0; speed <= 255; speed += 5) {
    setMotorSpeed(speed);
    Serial.print("Speed: "); Serial.println(speed);
    delay(50);
  }
  delay(1000);

  // slowing down
  for (int speed = 255; speed >= 0; speed -= 5) {
    setMotorSpeed(speed);
    Serial.print("Speed: "); Serial.println(speed);
    delay(50);
  }
  delay(1000);

  // reversing
  for (int speed = 0; speed >= -255; speed -= 5) {
    setMotorSpeed(speed);
    Serial.print("Speed: "); Serial.println(speed);
    delay(50);
  }
  delay(1000);

  setMotorSpeed(0);
  delay(2000);
}