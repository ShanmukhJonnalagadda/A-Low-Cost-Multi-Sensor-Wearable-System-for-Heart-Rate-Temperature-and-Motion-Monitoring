# Requirements and wiring

Arduino IDE, Arduino AVR Boards, OneWire, DallasTemperature and PulseSensor Playground. Exact original library versions are unknown; record installed versions after compilation. Target: classic Arduino Uno (ATmega328P), subject to confirmation of actual board.

| Signal | Pin |
|---|---|
| DS18B20 data | D4 |
| Optical pulse analog out | A0 |
| MMA7361L X | A1 |
| MMA7361L Y | A2 |
| MMA7361L Z | A3 |

Pin assignments come from original firmware, not an inspected physical schematic. Use common ground and verify each module datasheet, supply, signal levels and pinout before applying power. A bare DS18B20 in externally powered mode typically requires a 4.7 kOhm data pull-up to its appropriate supply; this sketch assumes external power, not parasite power. The bare MMA7361L is a low-voltage device; do not connect its supply to 5 V unless the specific breakout documentation explicitly permits it. Verify sleep and range-select pins and reference voltage. Confirm pulse module voltage ratings. Disconnect power before changing connections. For early tests use bench fixtures, not a person connected to mains-powered equipment.
