# 🏡 Smart Home Automation System  

## 📖 Table of Contents  
- [Overview](#-overview)  
- [Technologies Used](#-technologies-used)  
- [Features](#-features)  
- [Circuit Diagram](circuit.png)  
- [Setup & Installation](#-setup--installation)  
- [How It Works](#-how-it-works)  
  

## 🔍 Overview  
This **Smart Home Automation System** is designed to remotely control household appliances using an **ESP32** with **Wi-Fi connectivity**. The system integrates **RTOS and IoT** to efficiently manage a **fan, light, and door lock**. The automation is enhanced by **sensor-based controls and a mobile app interface**, making the system user-friendly and scalable.  

## 🛠️ Technologies Used  
- **Microcontroller:** ESP32  
- **Sensors:** DHT22 (temperature & humidity), PIR sensor  
- **Actuators:** Relay Module (for appliances), Servo Motor (for door lock)  
- **Software:** Arduino IDE, Flask (Python for server), Wokwi Simulator  

## 🚀 Features  
- ✅ **Remote Control:** Manage home appliances via a mobile app  
- ✅ **Real-time Monitoring:** Get live updates on room temperature and motion detection  
- ✅ **Wi-Fi Integration:** ESP32 communicates with a **Flask-based laptop server**  
- ✅ **Automatic Door Locking:** The door locks itself after a predefined time  
- ✅ **User-Friendly UI:** Easily control devices through an intuitive interface  
- ✅ **Modular & Expandable:** Add more sensors or appliances as needed  



## 🔧 Setup & Installation  
1. **Hardware Setup:** Connect the ESP32, sensors, relay module, and servo motor as per the circuit diagram.  
2. **Firmware Upload:** Install the required **ESP32 board package** in **Arduino IDE**, then upload the firmware.  
3. **Flask Server Setup:**  
   - Install Python and Flask on your laptop.  
   - Run the Flask server to manage communication between ESP32 and the mobile app.  
4. **Mobile App Configuration:** Configure the app to send and receive control commands via Wi-Fi.  
5. **Run the System:** Power on the ESP32, connect it to Wi-Fi, and start managing appliances remotely.  

## ⚙️ How It Works  
1. **User sends a command via a mobile app.**  
2. **ESP32 receives the command through Wi-Fi** and activates/deactivates the respective appliance.  
3. **Flask server acts as a bridge**, processing commands and updating the UI.  
4. **Sensor data is sent back** to the mobile app for real-time monitoring.  
5. **Door lock automation ensures security** by auto-locking after a set time.  