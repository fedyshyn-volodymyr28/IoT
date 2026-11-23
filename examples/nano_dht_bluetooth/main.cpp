// Arduino Nano + DHT11: temperature and humidity -> USB Serial (9600)
// and -> ESP32 over SoftwareSerial (D10=RX, D11=TX, 9600).
// Wiring: DHT11 S -> D2, VCC -> 5V, GND -> GND
//   Nano D11 (TX) -> 1k -> ESP32 GPIO16 (RX2) -> 2k -> GND  (5V -> 3.3V)
//   Nano D10 (RX) <- ESP32 GPIO17 (TX2)
//   Nano GND -- ESP32 GND
#include <Arduino.h>
#include <DHT.h>
#include <SoftwareSerial.h>

constexpr uint8_t DHT_PIN = 2;
DHT dht(DHT_PIN, DHT11);
SoftwareSerial link(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  link.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);  // DHT11 can be read at most once per ~1-2 s
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT read error - check wiring");
    return;
  }
  char line[40];
  char ts[8];
  dtostrf(t, 4, 1, ts);
  snprintf(line, sizeof(line), "temp=%s C  hum=%d %%", ts, (int)(h + 0.5f));
  Serial.println(line);
  link.println(line);
}
