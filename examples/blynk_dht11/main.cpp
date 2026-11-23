// ESP32 DevKit + DHT11 -> Blynk Cloud, temperature and humidity once per 10 minutes.
//
// Wiring (DHT11 module): S -> GPIO32, V -> 3V3, G -> GND
//
// Blynk template datastreams:
//   V0 "Temperature" (Double, 0..50)   V1 "Humidity" (Integer, 0..100)
//
// Message budget: the free plan allows 30,000 messages per month.
// 2 datastreams x 144 sends per day = ~8,600 messages per month, so it fits.
#include <Arduino.h>
#define BLYNK_PRINT Serial  // print Blynk connection log to the serial monitor
#include "blynk_secrets.h"  // defines BLYNK_* and WIFI_* (must come before BlynkSimpleEsp32.h)
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

constexpr uint8_t DHT_PIN = 32;
constexpr uint32_t SEND_INTERVAL_MS = 10UL * 60UL * 1000UL;  // 10 minutes

DHT dht(DHT_PIN, DHT11);
BlynkTimer timer;

void sendReadings() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT read error, skipping this send");
    return;
  }
  Blynk.virtualWrite(V0, t);  // 1 message
  Blynk.virtualWrite(V1, h);  // 1 message
  Serial.printf("temp=%.1f C hum=%.0f %% (sent to V0, V1)\n", t, h);
}

// Send once right after the connection is up, then every 10 minutes.
BLYNK_CONNECTED() {
  sendReadings();
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);  // DHT11 needs a moment before the first read
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(SEND_INTERVAL_MS, sendReadings);
}

void loop() {
  Blynk.run();
  timer.run();
}
