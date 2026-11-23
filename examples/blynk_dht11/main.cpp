// ESP32 + DHT11 (S -> GPIO32): sends temperature (V0) and humidity (V1) to Blynk every 10 minutes.
#include <Arduino.h>
#include "blynk_secrets.h"  // BLYNK_* and WIFI_* defines, must come before BlynkSimpleEsp32.h
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

constexpr uint8_t DHT_PIN = 32;
constexpr uint32_t SEND_INTERVAL_MS = 10UL * 60UL * 1000UL;

DHT dht(DHT_PIN, DHT11);
BlynkTimer timer;

void sendReadings() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) return;
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

BLYNK_CONNECTED() {
  sendReadings();
}

void setup() {
  dht.begin();
  delay(2000);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(SEND_INTERVAL_MS, sendReadings);
}

void loop() {
  Blynk.run();
  timer.run();
}
