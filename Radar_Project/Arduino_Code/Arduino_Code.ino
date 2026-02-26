#include <Servo.h>

const int trigPin = 8;
const int echoPin = 9;

long duration;
int distance;

Servo myServo; // Creates a servo object 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(6); 
}

void loop() {
  // rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  
  Serial.print(i);
  Serial.print(","); // Sends addition character right next to the previous value needed in the Processing IDE 
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed in the Processing IDE 
  }
  // Repeats the previous lines from 180 to 0 degrees
  for(int i=180;i>=0;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}