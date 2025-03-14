# Pool Monitoring System - ESP-IDF

## Overview
This project is a **pool monitoring system** built using **ESP-IDF** on an **ESP-based microcontroller**. The system integrates multiple sensors to measure key water quality parameters, including:

- **pH Levels** (Estimated via sensor fusion)
- **Chlorine Levels** (Estimated via sensor fusion)
- **Turbidity** (Water clarity measurement using a light sensor)
- **Water Temperature**
- **Enclosure Humidity & Temperature** (Using a DHT sensor for system safety)

The goal is to use **sensor fusion**, combining different sensor readings to infer values for **pH and chlorine levels**, reducing the need for expensive dedicated sensors.

## Folder Structure
```
project_root/
│── application/         # High-level application logic
│   ├── src/            # C++ source files
│   ├── inc/            # Header files
│── drivers/            # Custom drivers & sensor wrappers
│   ├── src/            # C++ source files
│   ├── inc/            # Header files
│── main.cpp            # Entry point for the program
│── CMakeLists.txt      # Build configuration
│── sdkconfig           # ESP-IDF configuration file
```

### **Folder Details:**
- **application/** → Contains logic for managing data from sensors, processing measurements, and sending alerts.
- **drivers/** → Houses both **custom drivers** and **wrappers** for ESP-IDF's built-in communication protocols (e.g., I2C, SPI, UART).
- **main.cpp** → The entry point for the project, initializing sensors, handling FreeRTOS tasks, and managing data flow.

## **Sensor & Measurement Approach**
### **1. Turbidity Sensor**  
- Uses an **LED and a photodiode** to measure light transmission through water.  
- Higher **light absorption** → **Dirtier water**.

### **2. pH & Chlorine (Sensor Fusion Approach)**  
Instead of using expensive dedicated sensors, the system estimates these values by combining:
- **TDS (Total Dissolved Solids) Sensor**
- **ORP (Oxidation-Reduction Potential) Sensor**
- **Temperature & Conductivity Measurements**
- **Colorimetric Analysis (Optional for Chlorine)**  
  - Uses a **reagent-based approach** where a **specific wavelength LED** and a **photodiode** measure color change, correlating it to chlorine levels.

### **3. Enclosure Monitoring (DHT Sensor)**  
- Measures **humidity and temperature** inside the system's enclosure.
- If humidity exceeds a **critical threshold**, the system **automatically shuts down** to prevent damage.

## **Development Approach**
- **ESP-IDF** is used for core development, but **custom drivers** are implemented where possible to gain low-level control over hardware.
- Communication protocols (I2C, SPI, UART) are managed through **wrappers**, keeping the application code flexible.
- **FreeRTOS** is used to handle multitasking and efficient sensor polling.

## **Dependencies & Requirements**
### **Software**
- **ESP-IDF SDK** (Latest stable version)
- **CMake** (For ESP-IDF build system)
- **Python 3+** (For ESP-IDF tools)

### **Hardware**
- **ESP-based microcontroller** (ESP32 recommended)
- **Turbidity Sensor** (LED + Photodiode based)
- **TDS Sensor** (To estimate dissolved solids)
- **ORP Sensor** (To infer chlorine levels)
- **DHT Sensor** (For enclosure monitoring)
- **Reagent System (Optional for colorimetric analysis)**

## **Next Steps & Considerations**
- **Optimize sensor fusion algorithms** for better pH & chlorine estimation.
- **Automate reagent handling** for chlorine colorimetric analysis.
- **Integrate wireless communication (Wi-Fi/Bluetooth) for remote monitoring.**

This README will be updated as the project evolves.

