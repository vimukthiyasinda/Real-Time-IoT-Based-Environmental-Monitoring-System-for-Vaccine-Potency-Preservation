# Real-Time Environmental Monitoring System for Vaccine Potency Preservation

A real-time IoT-based environmental monitoring system designed to ensure vaccine potency during storage and transportation. The system continuously monitors critical environmental conditions such as temperature, humidity, CO₂ concentration, motion, tilt, impact, container security, and geographic location.

Built around the ESP32 microcontroller, the solution integrates multiple sensors and communication modules to detect abnormal conditions and provide instant SMS alerts to authorized personnel. By monitoring CO₂ levels generated from dry ice sublimation, the system offers an innovative approach to identifying dry ice depletion before temperature excursions occur, helping maintain cold-chain integrity.

## Key Features

* Real-time temperature monitoring using DHT22 and DS18B20 sensors
* Humidity monitoring for optimal vaccine storage conditions
* CO₂ concentration monitoring to detect dry ice depletion
* Motion, vibration, tilt, and impact detection using MPU6050
* Unauthorized container opening detection using LDR
* GPS-based real-time location tracking with Neo-6M
* Instant SMS alert notifications via SIM800L GSM module
* Automated threshold-based decision making using ESP32
* Portable and low-power design suitable for cold-chain logistics

## Technologies Used

* ESP32 Microcontroller
* Arduino IDE
* Embedded C/C++
* DHT22, DS18B20, SGP30, MPU6050 Sensors
* SIM800L GSM Module
* Neo-6M GPS Module
* I2C, UART, OneWire Communication Protocols

## Objective

To enhance vaccine cold-chain reliability by providing continuous monitoring, early fault detection, and rapid alerting mechanisms that help preserve vaccine potency throughout transportation and storage.
