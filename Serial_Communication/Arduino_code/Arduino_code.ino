/* ARDUINO CODE */
#include <SoftwareSerial.h>

// RX = Pin 2, TX = Pin 3
// RX -> 0 | TX -> 1 . These pins should not be connected to esp
SoftwareSerial chatSerial(2, 3); 

void setup() {
  Serial.begin(9600);
  chatSerial.begin(9600);
  
  delay(2000); 

  // TURN 1 (Start)
  chatSerial.println("Hey, you awake?");
}

void loop() {
  if (chatSerial.available()) {
    String reply = chatSerial.readStringUntil('\n');
    reply.trim(); 

    if (reply.length() > 0) {
      Serial.print("ESP32: ");
      Serial.println(reply);

      // responses of arduino
      
      // TURN 3: Response to "dual cores"
      if (reply.indexOf("dual cores") != -1) {
        delay(2000);
        chatSerial.println("Two brains? Show off");
      }
      
      // TURN 5: Response to "slow"
      else if (reply.indexOf("slow") != -1) {
        delay(2000);
        chatSerial.println("I am reliable. No bugs");
      }
      
      // TURN 7: Response to "calculator"
      else if (reply.indexOf("calculator") != -1) {
        delay(2000);
        chatSerial.println("I run on pure 5V!");
      }

      // TURN 9: Response to "WiFi"
      else if (reply.indexOf("WiFi") != -1) {
        delay(2000);
        chatSerial.println("I have strong pins");
      }

      // TURN 11: Response to "sensors"
      else if (reply.indexOf("sensor pins") != -1) {
        delay(2000);
        chatSerial.println("Can you survive 5V?");
      }

      // TURN 13: Response to "fry"
      else if (reply.indexOf("fry") != -1) {
        delay(2000);
        chatSerial.println("Ha! I am tougher");
      }
    }
  }
}