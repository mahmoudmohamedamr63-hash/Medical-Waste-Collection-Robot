# Smart Autonomous Medical Waste Collection Robot

## Overview
An IoT-enabled, autonomous line-following robot designed for hospitals to safely transport hazardous medical waste. Built with ESP32, this robot minimizes human exposure to dangerous materials, improving workplace safety and supporting sustainable healthcare environments.

## Key Features
- Smart Activation: Starts moving automatically when the internal waste bin is full (detected via an internal Ultrasonic sensor).
- Autonomous Navigation: Uses IR sensors for precise line following across hospital corridors.
- Dynamic Obstacle Avoidance: Prevents collisions using front-facing ultrasonic distance measurement.
- Auto-Dumping Sequence: Automatically dumps the waste using a servo mechanism upon reaching the destination, signaled by visual (LED) and audio (Buzzer) indicators.
- IoT Integration: Connected via WiFi and the Blynk platform for real-time monitoring.

## Hardware Components
- Microcontroller: ESP32
- Motor Driver: L298N (Controlled via ESP32 Hardware PWM ledcWrite)
- Sensors: 
  - 2x IR Sensors (Line Tracking)
  - 2x Ultrasonic Sensors (HC-SR04) - Bin capacity & Obstacle detection.
- Actuators: DC Motors, Servo Motor (Dumping mechanism)
- Indicators: LED, Active Buzzer

## Tech Stack & Software
- Language: C++ 
- Framework: Arduino IDE
- Libraries Used: WiFi.h, WiFiClient.h, BlynkSimpleEsp32.h, ESP32Servo.h

## Project Assets
Make sure to check out the uploaded Presentation PDF for:
- Full system Flowchart.
- Complete Hardware Circuit & Wiring Diagrams.
- Cost analysis & Business feasibility.
