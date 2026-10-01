#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "secrets.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int VOLTAGE_PIN = 34;
const int CURRENT_PIN = 35;

// Starting calibration values only. Calibrate against your sensor/reference.
const float VOLTAGE_SCALE = 0.250f;
const float CURRENT_SCALE = 0.185f;
const float CURRENT_OFFSET = 2.5f;

const char* THINGSPEAK_SERVER = "http://api.thingspeak.com/update";
unsigned long lastUpload = 0;
const unsigned long UPLOAD_INTERVAL_MS = 15000;
unsigned long lastEnergyUpdate = 0;
float energyKWh = 0.0f;

float readVoltage() {
  int raw = analogRead(VOLTAGE_PIN);
  return raw * VOLTAGE_SCALE;
}

float readCurrent() {
  int raw = analogRead(CURRENT_PIN);
  float sensorVoltage = (raw / 4095.0f) * 3.3f;
  float current = (sensorVoltage - CURRENT_OFFSET) / CURRENT_SCALE;
  if (current < 0) current = -current;
  return current;
}

void showValues(float voltage, float current, float power, float energy) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("Voltage: %.1f V", voltage);
  display.setCursor(0, 16);
  display.printf("Current: %.2f A", current);
  display.setCursor(0, 32);
  display.printf("Power:   %.1f W", power);
  display.setCursor(0, 48);
  display.printf("Energy:  %.3f kWh", energy);
  display.display();
}

void uploadToThingSpeak(float voltage, float current, float power, float energy) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = String(THINGSPEAK_SERVER) +
               "?api_key=" + THINGSPEAK_API_KEY +
               "&field1=" + String(voltage, 2) +
               "&field2=" + String(current, 3) +
               "&field3=" + String(power, 2) +
               "&field4=" + String(energy, 4);

  http.begin(url);
  int response = http.GET();
  Serial.print("ThingSpeak response: ");
  Serial.println(response);
  http.end();
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  lastEnergyUpdate = millis();
}

void loop() {
  float voltage = readVoltage();
  float current = readCurrent();
  float power = voltage * current;

  unsigned long now = millis();
  float hours = (now - lastEnergyUpdate) / 3600000.0f;
  energyKWh += (power * hours) / 1000.0f;
  lastEnergyUpdate = now;

  showValues(voltage, current, power, energyKWh);

  Serial.printf("Voltage: %.2f V | Current: %.3f A | Power: %.2f W | Energy: %.4f kWh\n",
                voltage, current, power, energyKWh);

  if (now - lastUpload >= UPLOAD_INTERVAL_MS) {
    lastUpload = now;
    uploadToThingSpeak(voltage, current, power, energyKWh);
  }

  delay(1000);
}
