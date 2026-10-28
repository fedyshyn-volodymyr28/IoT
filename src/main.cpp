#include <Arduino.h>

const int LED_PIN = 2; // built-in LED on ESP32 DevKit V1
const unsigned long BLINK_INTERVAL = 500;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("IoT: blink started");
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_INTERVAL);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_INTERVAL);
}
