#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // SDA --> 21 , SCL --> 20

// WiFi credentials
const char* ssid = "The OHM Lab";
const char* password = "dlm%15^9bx";

// Weather API key
String apiKey = "00d787951676440c818164957261906";

// City
String city = "Mumbai";
String countryCode = "IN";

// Weather variables
float temperature = 0;
int humidity = 0;
float windSpeed = 0;
String condition = "";

unsigned long screenTimer = 0;
unsigned long weatherTimer = 0;

const unsigned long SCREEN_INTERVAL = 4000;   // 4 sec (4000 ms)
const unsigned long WEATHER_INTERVAL = 300000; // 5 min (300000 ms)

int screenIndex = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Connecting...");
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");

  delay(2000);

  getWeatherData();
  showScreen(0);
}

void loop() {
  
  // update weather after 5 min
  if(millis() - weatherTimer > WEATHER_INTERVAL){
    getWeatherData();
    weatherTimer = millis();
  }

  // update screen every 4s
  if(millis() - screenTimer > SCREEN_INTERVAL){
    screenTimer = millis();

    screenIndex++;

    if(screenIndex > 3)
      screenIndex = 0;

    showScreen(screenIndex);
  }
}

void getWeatherData() {
  if(WiFi.status() != WL_CONNECTED)
    return;

  HTTPClient http;

  String url =
    "http://api.weatherapi.com/v1/current.json?key=" +
    apiKey +
    "&q=" + city +
    "&aqi=no";

  http.begin(url);

  int httpCode = http.GET(); // ESP32 is sending request to api

  if(httpCode > 0)
  {
    // received response from api
    String payload = http.getString(); 

    DynamicJsonDocument doc(2048);

    DeserializationError error =
      deserializeJson(doc, payload);

    if(!error)
    {
      // fetching data
      temperature = doc["current"]["temp_c"];
      humidity = doc["current"]["humidity"];
      windSpeed = doc["current"]["wind_kph"];
      condition = doc["current"]["condition"]["text"].as<String>();
      Serial.println("Weather Updated");
    }
  }

  http.end();
}

void showScreen(int screen) {
  lcd.clear();

  switch(screen) {
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print(temperature,1);
      lcd.print((char)223);
      lcd.print("C");

      lcd.setCursor(0,1);
      lcd.print("Humidity:");
      lcd.print(humidity);
      lcd.print("%");
      break;

    case 1:
      lcd.setCursor(0,0);
      lcd.print("Wind Speed:");

      lcd.setCursor(0,1);
      lcd.print(windSpeed,1);
      lcd.print(" m/s");
      break;

    case 2:
      lcd.setCursor(0,0);
      lcd.print("Condition:");

      lcd.setCursor(0,1);
      lcd.print(condition);
      break;

    case 3:
      lcd.setCursor(0,0);
      lcd.print(city);

      lcd.setCursor(0,1);
      lcd.print("Weather Info");
      break;
  }
}