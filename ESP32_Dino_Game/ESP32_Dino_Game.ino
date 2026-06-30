#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Settings 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi Settings
const char* ssid = "ESP32-Dino-Game";
const char* password = ""; // Open network

// Web Server & WebSocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Game Variables
bool gameOver = false;
int score = 0;

// 16x16 Pixel Dinosaur Sprite
const int dinoWidth = 16;
const int dinoHeight = 16;
static const unsigned char PROGMEM dino_bmp[] = {
  0x00, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xFC, 0x01, 0xFE,
  0x01, 0xC0, 0x1F, 0xC0, 0x3F, 0x80, 0x3F, 0x80, 0x1F, 0x00, 0x0F, 0x00, 0x09, 0x00, 0x0B, 0x00
};

// 8x16 Pixel Cactus Sprite
const int cactusWidth = 8;
const int cactusHeight = 16;
static const unsigned char PROGMEM cactus_bmp[] = {
  0x30, 0x30, 0x30, 0xB4, 0xB4, 0xFC, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30
};

// Physics Settings 
const int groundY = 54;
float dinoX = 15;
float dinoY = groundY - dinoHeight;
float velocityY = 0;
float gravity = 0.8;
float jumpStrength = -7.5;
bool isJumping = false;

// Obstacle Settings
float cactusX = 128;
float cactusSpeed = 3.0;

// Trigger flag from WebSockets
volatile bool jumpTriggered = false;

// HTML Frontend 
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Dino Controller</title>
  <style>
    body { margin: 0; padding: 0; background-color: #2c3e50; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; overflow: hidden; }
    h1 { color: #ecf0f1; margin-bottom: 10px; font-size: 3rem; letter-spacing: 2px; }
    p { color: #bdc3c7; font-size: 1.5rem; margin-bottom: 40px; }
    b { color: #e74c3c; }
    button { padding: 20px 50px; font-size: 1.2rem; font-weight: bold; background: #e74c3c; color: white; border: none; border-radius: 8px; box-shadow: 0 6px #c0392b; cursor: pointer; user-select: none; transition: transform 0.1s, box-shadow 0.1s; }
    button:active, button.active-state { box-shadow: 0 2px #922b21; transform: translateY(4px); }
  </style>
</head>
<body>
  <h1>ESP32 DINO ARCADE</h1>
  <p>Press <b>SPACEBAR</b> or <b>UP ARROW</b> to Jump</p>
  <button id="jumpBtn" onmousedown="jump()">OR CLICK HERE</button>
  
  <script>
    var gateway = `ws://${window.location.hostname}/ws`;
    var websocket;
    window.addEventListener('load', onLoad);
    
    function onLoad(event) { initWebSocket(); }
    
    function initWebSocket() {
      websocket = new WebSocket(gateway);
      websocket.onclose = function(event) { setTimeout(initWebSocket, 2000); };
    }
    
    function jump() {
      if (websocket.readyState == 1) {
        websocket.send('JUMP');
      }
    }

    // --- LAPTOP KEYBOARD LISTENER ---
    window.addEventListener('keydown', function(e) {
      if (e.code === 'Space' || e.code === 'ArrowUp') {
        e.preventDefault(); 
        jump();
        
        let btn = document.getElementById('jumpBtn');
        btn.classList.add('active-state');
        setTimeout(() => btn.classList.remove('active-state'), 100);
      }
    });
  </script>
</body>
</html>
)rawliteral";

// WebSocket Event Handler
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      data[len] = 0;
      if (strcmp((char*)data, "JUMP") == 0) {
        jumpTriggered = true;
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize OLED (If screen stays black, try changing 0x3C to 0x3D)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.print("Starting Game...");
  display.display();

  // Setup Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  
  // Setup Web Server
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.begin();
}

void resetGame() {
  gameOver = false;
  score = 0;
  cactusX = 128;
  cactusSpeed = 3.0;
  dinoY = groundY - dinoHeight;
  velocityY = 0;
}

void loop() {
  // 1. Handle Input
  if (jumpTriggered) {
    jumpTriggered = false; 
    
    if (gameOver) {
      resetGame(); 
    } else if (!isJumping) {
      velocityY = jumpStrength; 
      isJumping = true;
    }
  }

  // 2. Game Physics & Logic
  if (!gameOver) {
    velocityY += gravity;
    dinoY += velocityY;

    if (dinoY >= groundY - dinoHeight) {
      dinoY = groundY - dinoHeight;
      velocityY = 0;
      isJumping = false;
    }

    cactusX -= cactusSpeed;
    if (cactusX < -cactusWidth) {
      cactusX = 128; 
      score++;
      if (score % 5 == 0) cactusSpeed += 0.5; 
    }

    // Hitbox Collision Detection (Adjusted for sprites)
    // We add a tiny bit of "forgiveness" margin to the hitbox so clipping the edge of a pixel doesn't kill you instantly.
    int forgiveness = 2; 
    if (dinoX + forgiveness < cactusX + cactusWidth &&
        dinoX + dinoWidth - forgiveness > cactusX &&
        dinoY + forgiveness < groundY && 
        dinoY + dinoHeight - forgiveness > groundY - cactusHeight) {
      gameOver = true;
    }
  }

  // 3. Render Graphics
  display.clearDisplay();

  if (gameOver) {
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.print("GAME OVER");
    display.setTextSize(1);
    display.setCursor(20, 45);
    display.print("Press SPACE Retry");
  } else {
    // Draw Ground Line
    display.drawLine(0, groundY, 128, groundY, SSD1306_WHITE);
    
    // Draw Score
    display.setCursor(90, 5);
    display.print("Pts:");
    display.print(score);
    
    // Draw Dinosaur and Cactus Bitmaps (x, y, array, width, height, color)
    display.drawBitmap((int)dinoX, (int)dinoY, dino_bmp, dinoWidth, dinoHeight, SSD1306_WHITE);
    display.drawBitmap((int)cactusX, groundY - cactusHeight, cactus_bmp, cactusWidth, cactusHeight, SSD1306_WHITE);
  }

  display.display();
  delay(25);
}