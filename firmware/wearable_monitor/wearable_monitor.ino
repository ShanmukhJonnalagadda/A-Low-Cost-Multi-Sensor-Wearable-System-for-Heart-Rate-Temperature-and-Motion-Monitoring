#define USE_ARDUINO_INTERRUPTS true
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PulseSensorPlayground.h>

// Arduino Uno (ATmega328P), original sensor pin assignments.
constexpr uint8_t TEMP_PIN = 4;
constexpr uint8_t PULSE_PIN = A0;
constexpr uint8_t AXIS_PINS[] = {A1, A2, A3};
constexpr int PULSE_THRESHOLD = 550;
constexpr float ADC_REFERENCE_V = 5.0f; // Nominal; measure actual reference for calibration.
constexpr unsigned long TEMP_CONVERSION_MS = 750;
constexpr unsigned long REPORT_MS = 1000;

OneWire oneWire(TEMP_PIN);
DallasTemperature temperature(&oneWire);
PulseSensorPlayground pulse;
bool pulseReady = false;
unsigned long conversionStart = 0, lastReport = 0;
float tempC = DEVICE_DISCONNECTED_C;
int latestBpm = 0;
bool newBeat = false;

void setup() {
  Serial.begin(9600);
  temperature.begin();
  temperature.setResolution(12);
  temperature.setWaitForConversion(false);
  temperature.requestTemperatures();
  conversionStart = millis();
  pulse.analogInput(PULSE_PIN);
  pulse.setThreshold(PULSE_THRESHOLD);
  pulse.blinkOnPulse(LED_BUILTIN);
  pulseReady = pulse.begin();
  if (!pulseReady) Serial.println(F("Pulse sensor initialization failed"));
}

void loop() {
  unsigned long now = millis();
  if (pulseReady && pulse.sawStartOfBeat()) {
    latestBpm = pulse.getBeatsPerMinute();
    newBeat = true;
  }
  if (now - conversionStart >= TEMP_CONVERSION_MS) {
    tempC = temperature.getTempCByIndex(0);
    temperature.requestTemperatures();
    conversionStart = millis();
  }
  if (now - lastReport < REPORT_MS) return;
  lastReport = now;
  Serial.println(F("=== SENSOR READINGS ==="));
  if (tempC == DEVICE_DISCONNECTED_C || !(tempC >= -55.0f && tempC <= 125.0f)) {
    Serial.println(F("Temperature unavailable"));
  } else {
    Serial.print(F("Temperature C: ")); Serial.println(tempC, 2);
    Serial.print(F("Temperature F: ")); Serial.println(tempC * 1.8f + 32.0f, 2);
  }
  if (newBeat && latestBpm > 0) {
    Serial.print(F("Latest detected beat BPM: ")); Serial.println(latestBpm);
  } else {
    Serial.println(F("No new BPM estimate"));
  }
  newBeat = false;
  for (uint8_t i = 0; i < 3; ++i) {
    int raw = analogRead(AXIS_PINS[i]);
    Serial.print(char('X' + i)); Serial.print(F(" ADC: ")); Serial.print(raw);
    Serial.print(F(" Approx V: "));
    Serial.println(raw * ADC_REFERENCE_V / 1024.0f, 3);
  }
  Serial.println(F("-----------------------------"));
}
