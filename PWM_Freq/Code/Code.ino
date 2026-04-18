/* PWM coe with frequency = 490Hz */

int motorPin = 9; // must be PWM pin
int duty = 0;
bool rising = true;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT); // direction 1 pin
  pinMode(8, OUTPUT); // direction 2 pin
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  // Sweep duty cycle 0 --> 255 --> 0
  if (rising) {
    duty++; // speed increasing
    if (duty >= 255) rising = false;
  } 
  else {
    duty--; // speed decreasing
    if (duty <= 0) rising = true;
  }

  analogWrite(motorPin, duty); // applying speed to motor

  Serial.print("DutyCycle:");
  Serial.print(duty);
  Serial.print("\t");

  Serial.print("Voltage_Approx:");
  Serial.print(map(duty, 0, 255, 0, 500)); // maps to 0–500 (representing 0–5V scaled x100)
  Serial.print("\t");

  Serial.print("PWM_Freq_Hz:");
  Serial.println(490); // Default constant freq of PWM (Hz) (smooth motion of motor)

  delay(10);
}


/* PWM coe with frequency = 5Hz */


// int duty = 0;
// bool rising = true;

// void setup() {
//   Serial.begin(9600);

//   pinMode(9, OUTPUT);  
//   pinMode(7, OUTPUT); 
//   pinMode(8, OUTPUT); 

//   digitalWrite(7, HIGH);
//   digitalWrite(8, LOW);

//   // Timer1 set to 5 Hz PWM on Pin 9
//   TCCR1A = 0;
//   TCCR1B = 0;

//   // Fast PWM Mode 14 (TOP = ICR1)
//   TCCR1A |= (1 << COM1A1); // Non-inverting PWM on OC1A (Pin 9)
//   TCCR1A |= (1 << WGM11);
//   TCCR1B |= (1 << WGM12) | (1 << WGM13);

//   // Prescaler = 64
//   TCCR1B |= (1 << CS11) | (1 << CS10);

//   ICR1 = 49999;   // TOP value for 5 Hz
//   OCR1A = 0;      // Initial duty = 0%
// }

// void loop() {

//   if (rising) {
//     duty++;
//     if (duty >= 255) rising = false;
//   } else {
//     duty--;
//     if (duty <= 0) rising = true;
//   }

//   // Converting 0–255 duty cycle to OCR1A range (0–49999)
//   OCR1A = map(duty, 0, 255, 0, 49999); // analogous to analogWrite()

//   Serial.print("DutyCycle:");
//   Serial.print(duty);
//   Serial.print("\t");

//   Serial.print("Voltage_Approx:");
//   Serial.print(map(duty, 0, 255, 0, 500)); // 0.0V to 5.0V x100
//   Serial.print("\t");

//   Serial.print("PWM_Freq_Hz:");
//   Serial.println(5);

//   delay(50);
// }