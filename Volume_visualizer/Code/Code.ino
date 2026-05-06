const int DATA_PIN  = 11;
const int LATCH_PIN = 8;
const int CLOCK_PIN = 12;
const int MIC_PIN   = A0;

const int SAMPLES     = 50;
const int NOISE_FLOOR = 8;    // Silence threshold
const int MAX_AMP     = 900; 
const int DECAY_RATE  = 1;    // How fast LEDs drop (1 = slow, 2 = faster,...)

int peakLevel = 0;  // Holds the highest recent level

const byte BAR[9] = {
  0b00000000,  // 0 LEDs
  0b00000001,  // 1 LED
  0b00000011,  // 2 LEDs
  0b00000111,  // 3 LEDs
  0b00001111,  // 4 LEDs
  0b00011111,  // 5 LEDs
  0b00111111,  // 6 LEDs
  0b01111111,  // 7 LEDs
  0b11111111   // 8 LEDs --> all ON at loud sound
};

void updateLEDs(byte pattern) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pattern);
  digitalWrite(LATCH_PIN, HIGH);
}

int getAmplitude() {
  int maxVal = 0, minVal = 1023;
  for (int i = 0; i < SAMPLES; i++) {
    int s = analogRead(MIC_PIN);
    if (s > maxVal) maxVal = s;
    if (s < minVal) minVal = s;
  }
  int amplitude = maxVal - minVal;
  return amplitude;
}

void setup() {
  pinMode(DATA_PIN,  OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  Serial.begin(9600);

  // Startup animation
  for (int i = 0; i <= 8; i++) { updateLEDs(BAR[i]); delay(60); }
  delay(300);
  for (int i = 8; i >= 0; i--) { updateLEDs(BAR[i]); delay(60); }
}

void loop() {
  int amplitude = getAmplitude();

  // removing noise
  if (amplitude < NOISE_FLOOR) amplitude = 0;

  // map amplitude to LED level
  int level = map(amplitude, 0, MAX_AMP, 0, 8);
  level = constrain(level, 0, 8);

  // Peak-hold with decay
  // If new level is HIGHER --> jump instantly
  // If new level is LOWER --> drop slowly by DECAY_RATE
  if (level >= peakLevel) {
    peakLevel = level;          // Rise instantly
  } else {
    peakLevel -= DECAY_RATE;    // Fall slowly
    if (peakLevel < 0) peakLevel = 0;
  }

  updateLEDs(BAR[peakLevel]);

  Serial.print("Amplitude: ");
  Serial.print(amplitude);
  Serial.print("  |  Level: ");
  Serial.print(level);
  Serial.print("  |  Peak: ");
  Serial.println(peakLevel);

  delay(20);
}


/* PROGRAM TO CHECK MAX VALUE OF AMPLITUDE */


// const int mic_pin = A1;
// const int samples = 50;

// void setup(){ 
//   Serial.begin(9600); 
// }

// void loop() {
//   int maxVal = 0, minVal = 1023;
//   for (int i = 0; i < samples; i++) {
//     int s = analogRead(mic_pin);
//     if (s > maxVal) maxVal = s;
//     if (s < minVal) minVal = s;
//   }
//   int amplitude = maxVal - minVal;
//   Serial.print("Amplitude: ");
//   Serial.println(amplitude);
//   delay(50);
// }