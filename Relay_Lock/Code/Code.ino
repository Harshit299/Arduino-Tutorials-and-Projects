#include <WiFi.h>

#define relay 4

const char* ssid = "Redmi Note 11";
const char* password = "abcd1234";

WiFiServer server(80);

bool lockState = false;

String htmlPage(bool state){

  String page = R"====(
  <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">

      <style>
        body{
          background:#121212;
          color:white;
          font-family:Arial;
          text-align:center;
          padding-top:40px;
        }
        
        .switch{
          position:relative;
          display:inline-block;
          width:160px;
          height:80px;
        }

        .switch input{
          opacity:0;
          width:0;
          height:0;
        }

        .slider{ 
          position:absolute;
          cursor:pointer;
          top:0;
          left:0;
          right:0;
          bottom:0;
          background-color:#ccc;
          transition:.4s;
          border-radius:80px;
        }

        .slider:before{
          position:absolute;
          content:"";
          height:60px;
          width:60px;
          left:10px;
          bottom:10px;
          background-color:white;
          transition:.4s;
          border-radius:50%;
        }

        input:checked + .slider{
          background-color:#4CAF50;
        }

        input:checked + .slider:before{
          transform:translateX(80px);
        }

        .status{
          font-size:32px;
          margin:25px;
        }
      </style>

    </head>

    <body>

      <h2>ESP32 Relay LOCK</h2>

      <div class="status">STATUS_TEXT</div>

      <label class="switch">
      <input type="checkbox" TOGGLE_STATE onchange="toggleLock(this)">
      <span class="slider"></span>
      </label>

      <script>
      function toggleLock(el){
        if(el.checked){
          fetch('/H');
          document.querySelector('.status').innerHTML="Locked";
        }else{
          fetch('/L');
          document.querySelector('.status').innerHTML="Unlocked";
        }
      }
      </script>

    </body>
    </html>
  )====";

  if(state){ // if locked
    page.replace("STATUS_TEXT","Locked");
    page.replace("TOGGLE_STATE","checked");
  }
  else{ // if unlocked
    page.replace("STATUS_TEXT","Unlocked");
    page.replace("TOGGLE_STATE","");
  }

  return page;
}

void setup(){

  Serial.begin(9600);

  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);

  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop(){

  WiFiClient client = server.available();

  if(client){

  String req = client.readStringUntil('\r');
  client.flush();

  if(req.indexOf("GET /H")!=-1){
    digitalWrite(relay,HIGH);
    lockState = true;
  }

  if(req.indexOf("GET /L")!=-1){
    digitalWrite(relay,LOW);
    lockState = false;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print(htmlPage(lockState));

  client.stop();
  }
}