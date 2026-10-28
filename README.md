# IoT

[![Build](https://github.com/fedyshyn-volodymyr28/IoT/actions/workflows/build.yml/badge.svg)](https://github.com/fedyshyn-volodymyr28/IoT/actions/workflows/build.yml)

Personal microcontroller sketches: Arduino, ESP32 and more.

## Structure

```
IoT/
├── .github/
│   └── workflows/
│       └── build.yml    # GitHub Actions: compiles the sketch on every push and PR
├── examples/
│   └── main.ino         # traffic-light sketch (button + 3 LEDs)
└── README.md
```

## Continuous integration

The `Build` workflow compiles `examples/main.ino` for the ESP32 DevKit V1
(`esp32doit-devkit-v1`, Arduino framework) with PlatformIO. A green check in
the **Actions** tab means the sketch compiles.

To run the same build locally:

```
pio ci examples/main.ino --board esp32doit-devkit-v1
```
