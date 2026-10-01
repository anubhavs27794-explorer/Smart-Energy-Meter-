# Smart Energy Meter with IoT Monitoring

An ESP32-based smart energy monitoring system designed to measure and track **voltage, current, power, and energy consumption** in real time. The project uses voltage/current sensing, an OLED display for local readings, and Wi-Fi-based IoT communication for remote monitoring.

> **Note:** The hardware images included in this repository are illustrative generated visuals for documentation/demo purposes. Replace them with photos of your actual prototype before presenting the project as a physical build.

## Features

- Real-time voltage measurement
- Current measurement using a current sensor
- Power calculation (V × I)
- Energy accumulation in kWh
- OLED display for local monitoring
- ESP32 Wi-Fi connectivity
- IoT data upload using ThingSpeak
- Serial Monitor output for debugging
- Modular sensor-based design

## Hardware

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller and Wi-Fi communication |
| ZMPT101B / isolated voltage sensor module | Voltage sensing |
| ACS712 current sensor | Current sensing |
| 0.96-inch SSD1306 OLED | Local display |
| Load | Test electrical load |
| 5V USB supply | Low-voltage electronics supply |
| Jumper wires / breadboard | Prototype connections |

## Software & Technologies

- C/C++
- ESP32 Arduino framework
- ADC / analog sensor interfacing
- I2C OLED interfacing
- Wi-Fi
- HTTP / ThingSpeak API
- Embedded systems

## System Flow

```text
Voltage Sensor ─┐
                ├──> ESP32 ADC ──> Voltage/Current Processing ──> OLED
Current Sensor ─┘                         │
                                         └──> Wi-Fi ──> ThingSpeak

Power = Voltage × Current
Energy (kWh) = Power (W) × Time (h) / 1000
```

## Pin Configuration

| Function | ESP32 Pin |
|---|---:|
| Voltage sensor ADC | GPIO 34 |
| Current sensor ADC | GPIO 35 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

## Arduino Libraries

Install these libraries through Arduino IDE:

- WiFi (included with ESP32 board package)
- Adafruit GFX Library
- Adafruit SSD1306

## Setup

1. Install the ESP32 board package in Arduino IDE.
2. Install the OLED libraries listed above.
3. Open `src/smart_energy_meter.ino`.
4. Edit `src/secrets.h` with your Wi-Fi and ThingSpeak API credentials.
5. Adjust the voltage/current calibration constants for your specific sensors.
6. Select your ESP32 board and COM port.
7. Upload the program.
8. Open Serial Monitor at **115200 baud**.

## IoT Monitoring

The example firmware sends measured values to ThingSpeak using HTTP. The suggested fields are:

- Field 1: Voltage (V)
- Field 2: Current (A)
- Field 3: Power (W)
- Field 4: Energy (kWh)

## Calibration

Sensor modules vary by model, supply voltage, burden/resistor network, and calibration. The constants in the example code are therefore **starting values only**. Calibrate the voltage and current readings against a suitable reference instrument before relying on the measurements.

## Safety

**Do not connect mains electricity directly to an ESP32, breadboard, GPIO pin, or non-isolated sensor circuit.** Use appropriately rated isolated sensing modules, fusing, enclosures, connectors, and professional electrical practices. For a student demonstration, a low-voltage isolated AC source or simulated sensor signals are safer choices. Work on mains circuits only if you are qualified and following applicable electrical safety requirements.

## Repository Structure

```text
smart-energy-meter-iot/
├── README.md
├── LICENSE
├── .gitignore
├── src/
│   ├── smart_energy_meter.ino
│   └── secrets.h.example
├── circuit/
│   └── wiring_diagram.svg
├── images/
│   ├── project_showcase_illustrative.png
│   ├── project_setup_illustrative.jpg
│   ├── circuit_diagram_illustrative.jpg
│   ├── iot_dashboard_illustrative.jpg
│   └── oled_output_illustrative.jpg
├── data/
│   └── sample_energy_readings.csv
└── docs/
    └── project_report.md
```

## Future Improvements

- Mobile/web dashboard
- Automatic load control
- Daily and monthly energy reports
- Over-current alerts
- Non-volatile energy storage
- Improved sensor calibration and filtering

## Author

**Anubhav S.**

Electronics & Communication Engineering
