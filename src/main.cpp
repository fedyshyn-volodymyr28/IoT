#include <Arduino.h>

const int LED_PIN = 2; // built-in LED on ESP32 DevKit V1

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
