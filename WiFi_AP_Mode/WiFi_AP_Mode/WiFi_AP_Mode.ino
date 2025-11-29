#include <WiFi.h>
#include <WiFiAP.h>

// http://192.168.4.1/

#define LED 12

const char *ssid = "ESP32 WiFi";
const char *password = "12345678";

WiFiServer server(80);

String htmlPage = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {
  background: #121212;
  color: white;
  font-family: Arial;
  text-align: center;
  padding-top: 40px;
}

.card {
  background: #1e1e1e;
  padding: 25px;
  border-radius: 15px;
  width: 300px;
  margin: auto;
  box-shadow: 0 0 20px rgba(0,0,0,0.5);
}

h2 {
  margin-bottom: 25px;
}

.switch {
  position: relative;
  display: inline-block;
  width: 70px;
  height: 34px;
}

.switch input {display: none;}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0; left: 0;
  right: 0; bottom: 0;
  background-color: #555;
  transition: .4s;
  border-radius: 34px;
}

.slider:before {
  position: absolute;
  content: "";
  height: 26px; width: 26px;
  left: 4px; bottom: 4px;
  background-color: white;
  transition: .4s;
  border-radius: 50%;
}

input:checked + .slider {
  background-color: #4CAF50;
}

input:checked + .slider:before {
  transform: translateX(36px);
}

.status {
  margin-top: 20px;
  font-size: 20px;
}
</style>

<script>
function toggleLED() {
  let state = document.getElementById("ledToggle").checked ? "H" : "L";
  fetch("/" + state);
}

setInterval(() => {
  fetch("/status")
    .then(response => response.text())
    .then(data => {
      document.getElementById("ledStatus").innerHTML = 
        data == "1" ? "LED is ON" : "LED is OFF";
      document.getElementById("ledToggle").checked = (data == "1");
    });
}, 1000);
</script>

</head>
<body>

<div class="card">
  <h2>ESP32 LED Control</h2>

  <label class="switch">
    <input type="checkbox" id="ledToggle" onchange="toggleLED()">
    <span class="slider"></span>
  </label>

  <p class="status" id="ledStatus">Checking...</p>
</div>

</body>
</html>
)=====";

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  Serial.println("Creating Access Point...");

  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();

    if (req.indexOf("GET /H") != -1) digitalWrite(LED, HIGH);
    if (req.indexOf("GET /L") != -1) digitalWrite(LED, LOW);

    if (req.indexOf("GET /status") != -1) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println();
      client.print(digitalRead(LED));
      return;
    }

    // Serve main UI page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print(htmlPage);

    delay(1);
    client.stop();
  }
}
