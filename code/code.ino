#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// PIN CONFIGURATION
#define DHTPIN PA0       // DHT11 DATA pin
#define DHTTYPE DHT11    // Sensor type
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  dht.begin();
  delay(1000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 not found!");
    while (1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("DHT11 + OLED");
  display.println("STM32 Blue Pill");
  display.display();
  delay(2000);
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if reading failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("DHT11 ERROR!");
    display.display();
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C  Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  display.clearDisplay();
  display.setTextSize(2);

  display.setCursor(0, 0);
  display.print("T: ");
  display.print(t, 1);
  display.print("C");

  display.setCursor(0, 30);
  display.print("H: ");
  display.print(h, 1);
  display.print("%");

  display.display();
  
  delay(2000);
}
