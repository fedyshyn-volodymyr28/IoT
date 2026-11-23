// ESP32 DevKit: Nano (UART2) -> Bluetooth Classic SPP -> phone terminal.
// Also mirrors everything to the USB serial monitor, and forwards
// text typed on the phone back to the Nano.
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial bt;
HardwareSerial nano(2);  // UART2: RX=GPIO16, TX=GPIO17

void setup() {
  Serial.begin(115200);
  nano.begin(9600, SERIAL_8N1, 16, 17);
  bt.begin("ESP32_Light");
  Serial.println("Bluetooth ready: pair with 'ESP32_Light'");
}

void loop() {
  while (nano.available()) {
    char c = nano.read();
    Serial.write(c);
    bt.write(c);
  }
  while (bt.available()) {
    nano.write(bt.read());
  }
}
