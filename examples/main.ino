#include <Arduino.h>

const int BUTTON_PIN = 2;
const int RED_PIN = 11;
const int YELLOW_PIN = 10;
const int GREEN_PIN = 9;

const unsigned long INTERVAL = 1000;

unsigned long lastSwitchTime = 0;
unsigned int ledsState = 0; // 0 - none, 1 - red, 2 - yellow, 3 - green;

void showLeds()
{
  digitalWrite(RED_PIN, ledsState == 1 ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, ledsState == 2 ? HIGH : LOW);
  digitalWrite(GREEN_PIN, ledsState == 3 ? HIGH : LOW);
}

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while (digitalRead(BUTTON_PIN) == LOW)
  {
    unsigned long now = millis();

    if (now - lastSwitchTime >= INTERVAL)
    {
      lastSwitchTime = now;

      if (ledsState == 3)
        ledsState = 1;
      else
        ledsState++;

      showLeds();
    }
  }

  ledsState = 0;
  showLeds();
}
