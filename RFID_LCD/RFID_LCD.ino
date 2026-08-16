#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* 
Connections for RFID:
SDA (SS): Digital Pin 10
SCK:      Digital Pin 13
MOSI:     Digital Pin 11
MISO:     Digital Pin 12
IRQ:      Leave unconnected
GND:      GND
RST:      Digital Pin 9
3.3V:     3.3V pin 

Connections for LCD:
SDA:      A4
SCL/SCK:  A5
VCC:      5V
GND:      GND
*/

// Pins for the RFID reader
#define SS_PIN 10
#define RST_PIN 9

// Initialize RFID and LCD objects
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // try 0x3F if it doesn't work.

// Replace this with your card's actual UID 
byte authorizedUID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // just a placeholder UID

void setup() {
  Serial.begin(9600);
  SPI.begin();        // Initialize SPI bus
  mfrc522.PCD_Init(); // Initialize MFRC522 reader
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Display standby message
  lcd.setCursor(0, 0);
  lcd.print("Scan your tag...");
  Serial.println("Scan your tag...");
}

void loop() {
  // Wait until new RFID card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Read the card data
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print the scanned UID to the Serial Monitor
  Serial.print("Scanned UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Compare scanned UID with the authorized UID
  bool accessGranted = true;
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedUID[i]) {
      accessGranted = false;
      break;
    }
  }

  // Update the LCD based on the result
  lcd.clear();
  lcd.setCursor(0, 0);

  if (accessGranted) {
    lcd.print("Access Granted");
    Serial.println("Access Granted");
  } else {
    lcd.print("Access Denied");
    Serial.println("Access Denied");
  }

  // Keep the message on screen for 2 seconds
  delay(2000); 

  // Reset the LCD back to standby mode
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your tag...");

  // Stop reading to avoid multiple triggers from one scan
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}