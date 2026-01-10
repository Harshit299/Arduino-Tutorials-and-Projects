const int pwmLed = 18;   
const int dacLed = 25;   

// PWM parameters
const int freq = 5000;      // Hz
const int resolution = 8;   // 8-bit (0-255)

int brightness = 0;
int fadeAmount = 5;

void setup() {
  Serial.begin(9600);

  ledcAttach(pwmLed, freq, resolution);

  Serial.println("PWM on Pin 18 vs DAC on Pin 25");
}

void loop() {
  // 1. The PWM approach 
  ledcWrite(pwmLed, brightness);

  // 2. The DAC approach
  dacWrite(dacLed, brightness);

  Serial.print("Current Value: ");
  Serial.println(brightness);

  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}