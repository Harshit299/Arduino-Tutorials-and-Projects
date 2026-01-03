#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

// LED pins
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;
const int LED7 = 8;

int levelState = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);

  Serial.println("Initializing MPU6050...");

  byte status = mpu.begin();

  while (status != 0) {
    Serial.println("MPU6050 not found");
    delay(1000);
  }

  if (status == 0) {
    Serial.println("MPU6050 connected");
  }

  Serial.println("Calibrating...");
  delay(1000);
  mpu.calcOffsets(true, true);
  Serial.println("Ready");
}

void loop() {

  mpu.update();
  float angleX = mpu.getAngleX();

  Serial.print("Angle X: ");
  Serial.println(angleX);

  // Decide level state
  if (angleX < -30)          levelState = 1; // LED1
  else if (angleX < -20)     levelState = 2; // LED2
  else if (angleX <= -10)    levelState = 3; // LED3
  else if (angleX <= 10)     levelState = 4; // LED4 (level)
  else if (angleX <= 20)     levelState = 5; // LED5
  else if (angleX <= 30)     levelState = 6; // LED6
  else                       levelState = 7; // LED7

  // Turn OFF all LEDs first
  allLedsOff();

  // Switch-case LED control
  switch (levelState) {

    case 1:
      digitalWrite(LED1, HIGH);
      break;

    case 2:
      digitalWrite(LED2, HIGH);
      break;

    case 3:
      digitalWrite(LED3, HIGH);  
      break;

    case 4:
      digitalWrite(LED4, HIGH); // Perfect level
      break;

    case 5:
      digitalWrite(LED5, HIGH);
      break;

    case 6:
      digitalWrite(LED6, HIGH); 
      break;

    case 7:
      digitalWrite(LED7, HIGH);
      break;
  }

  delay(50);
}

void allLedsOff() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
}