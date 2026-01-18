#include <WiFi.h>
#include <ESP32Servo.h>

// ---------------- SERVO ----------------
Servo myservo;
static const int servoPin = 13;


// ---------------- WIFI ----------------
const char* ssid = "Redmi Note 11";
const char* password = "abcd1234";

WiFiServer server(80);

// --------------- VARIABLES -----------------
String header; // store http request sent by browser
String valueString = "90";
int pos1 = 0;
int pos2 = 0;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);
  myservo.write(valueString.toInt());

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

// ---------------- LOOP ----------------
void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    String currentLine = "";

    Serial.println("New Client");

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();

      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {

            // ---------- HTTP RESPONSE ----------
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // ---------- HTML ----------
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>ESP32 Servo Control</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            client.println("<style>");
            client.println("body { background:#111; font-family:Arial; text-align:center; color:white; }");
            client.println(".box { margin:40px auto; padding:30px; width:90%; max-width:400px;");
            client.println("border:4px solid red; border-radius:20px }");
            client.println("h1 { margin-bottom:40px; }");
            client.println(".slider { width:100%; }");
            client.println(".value { margin-top:20px; font-size:22px; }");
            client.println("</style>");

            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
            client.println("</head>");

            client.println("<body>");
            client.println("<div class=\"box\">");
            client.println("<h1>ESP32 Servo Control</h1>");

            client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"" + valueString + "\" class=\"slider\" id=\"servoSlider\">");
            client.println("<div class=\"value\">Angle: <span id=\"servoPos\">" + valueString + "</span></div>");

            client.println("</div>");

            client.println("<script>");
            client.println("var slider = document.getElementById('servoSlider');");
            client.println("var pos = document.getElementById('servoPos');");
            client.println("slider.oninput = function(){");
            client.println("pos.innerHTML = this.value;");
            client.println("$.get('/?value=' + this.value + '&');");
            client.println("}");
            client.println("</script>");

            client.println("</body></html>");

            // ---------- SERVO CONTROL ----------
            if (header.indexOf("GET /?value=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1 + 1, pos2);
              myservo.write(valueString.toInt());
              Serial.print("Servo angle: ");
              Serial.println(valueString);
            }

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected\n");
  }
}