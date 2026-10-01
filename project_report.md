# Smart Energy Meter with IoT Monitoring — Project Report

## 1. Objective
Develop an ESP32-based system for monitoring electrical parameters and presenting them locally and remotely.

## 2. Parameters
- Voltage (V)
- Current (A)
- Power (W)
- Energy (kWh)

## 3. Methodology
The ESP32 samples the voltage and current sensor outputs through its ADC channels. Power is calculated as voltage multiplied by current. Energy is accumulated over time and displayed on an SSD1306 OLED. Wi-Fi connectivity is used to upload readings to an IoT dashboard such as ThingSpeak.

## 4. Technologies
C/C++, ESP32, ADC, I2C, OLED, sensor interfacing, Wi-Fi, HTTP and IoT monitoring.

## 5. Results
The prototype software provides continuous local readings and periodic cloud updates. The sample CSV in `data/` demonstrates the format used for logged measurements.

## 6. Limitations
The calibration constants are examples and must be adjusted for the exact sensor hardware. Power factor and non-sinusoidal loads are not accounted for in the simple P = V × I calculation.

## 7. Safety
Mains-voltage measurement requires appropriate isolation, insulation, fusing, enclosures and qualified electrical work. Do not build or test mains circuits on an ordinary breadboard.

## 8. Future Scope
Add power-factor measurement, current/voltage RMS calculation, mobile notifications, daily/monthly reports, non-volatile energy storage, and overload alerts.
