/* ESP32 CODE */
#include <HardwareSerial.h>

// UART1: RX=16, TX=17
HardwareSerial ChatSerial(1);

void setup() {
  Serial.begin(9600);
  ChatSerial.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 ready.");
}

void loop() {
  if (ChatSerial.available()) {
    String msg = ChatSerial.readStringUntil('\n');
    msg.trim(); 

    if (msg.length() > 0) {
      Serial.print("Arduino: ");
      Serial.println(msg);

      // responses of esp32

      // TURN 2: Response to "awake"
      if (msg.indexOf("awake") != -1) {
        delay(2000);
        ChatSerial.println("Yes. I have dual cores.");
      }
      
      // TURN 4: Response to "Show off"
      else if (msg.indexOf("Show off") != -1) {
        delay(2000);
        ChatSerial.println("You are just slow");
      }
      
      // TURN 6: Response to "reliable"
      else if (msg.indexOf("reliable") != -1) {
        delay(2000);
        ChatSerial.println("You are a calculator");
      }
      
      // TURN 8: Response to "pure 5V"
      else if (msg.indexOf("pure 5V") != -1) {
        delay(2000);
        ChatSerial.println("I have WiFi and BLE");
      }

      // TURN 10: Response to "strong pins"
      else if (msg.indexOf("strong pins") != -1) {
        delay(2000);
        ChatSerial.println("I have touch sensor pins");
      }

      // TURN 12: Response to "survive 5V"
      else if (msg.indexOf("survive 5V") != -1) {
        delay(2000);
        ChatSerial.println("No! I will fry");
      }

      // TURN 14: Response to "tougher"
      else if (msg.indexOf("tougher") != -1) {
        delay(2000);
        ChatSerial.println("Fine. Bye!");
      }
    }
  }
}