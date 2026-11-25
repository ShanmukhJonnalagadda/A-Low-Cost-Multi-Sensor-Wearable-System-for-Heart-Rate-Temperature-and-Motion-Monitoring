# Sensor processing and calibration

## Temperature
The revision requests a 12-bit DS18B20 conversion asynchronously and waits at least 750 ms before reading it. Disconnected readings and values outside the sensor's nominal -55 to 125 C range are flagged. Fahrenheit = Celsius x 1.8 + 32. Compare readings with a suitable reference under controlled conditions; this is not a core body temperature measurement. A sensor can return plausible but incorrect readings; range checks alone do not establish accuracy.

## Pulse
The original threshold is 550 ADC counts. The library estimates BPM; the sketch reports a new estimate when available, without applying a medical normal/abnormal label. Threshold suitability, motion artifacts, contact and optical interference require testing. No new estimate does not imply absence of a heartbeat.

## Accelerometer
Each axis is reported as a raw 10-bit ADC code and approximate voltage = code x nominal 5 V / 1024. Measure actual ADC reference for better voltage estimates. To estimate acceleration, characterize each axis zero-g offset and sensitivity at the actual range setting and supply. A calibrated axis estimate is (voltage - offset)/sensitivity. No calibration values or acceleration thresholds are assumed. One-second reports are insufficient evidence for fall detection; sampling rate, algorithm and validation would need separate design.

## Scheduling
The main loop checks pulse events frequently and schedules temperature conversion and serial reporting with millis(). This reduces explicit blocking delays, but is not a hard real-time guarantee. Interrupt interactions, serial throughput and sensor timing must be verified on the selected hardware.
