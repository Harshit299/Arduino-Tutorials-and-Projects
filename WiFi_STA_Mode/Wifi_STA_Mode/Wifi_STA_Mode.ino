#include <WiFi.h>

#define LED 12  

const char* ssid = "Redmi Note 11";      
const char* password = "abcd1234";

WiFiServer server(80);

String htmlPage = R"====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { 
  background: #121212; color: white; 
  font-family: Arial; text-align: center; padding-top: 40px; 
}
button {
  width: 150px; padding: 15px; 
  margin: 10px;
  font-size: 20px; 
  border: none; 
  border-radius: 10px; 
  color: white; 
}
#on { background: #4CAF50; }
#off { background: #f44336; }
</style>
</head>

<body>
<h2>ESP32 STA Mode LED Control</h2>
<button id="on" onclick="fetch('/H')">LED ON</button>
<button id="off" onclick="fetch('/L')">LED OFF</button>
</body>
</html>
)====";

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.println();
  Serial.println("Connecting to WiFi…");

  WiFi.begin(ssid, password); // esp32 ask the router(my mobile phone) for an IP

  // Wait for router connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();

    // Handle LED toggle
    if (req.indexOf("GET /H") != -1) digitalWrite(LED, HIGH);
    if (req.indexOf("GET /L") != -1) digitalWrite(LED, LOW);

    // Serve webpage
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print(htmlPage);

    client.stop();
  }
}
