🏡 Smart Home Automation System
📌 Project Overview
This project is an IoT-based Home Automation System using ESP32, allowing users to control home appliances (lights, fan, and door lock) via a mobile app. The system supports real-time monitoring and features automatic door locking after a set time.

🔥 Features
✔️ Remote Control – Manage lights, fan, and door lock via a mobile app.
✔️ Wi-Fi Connectivity – ESP32 enables seamless IoT integration.
✔️ Real-time Monitoring – Get live updates on device status.
✔️ Automated Door Locking – Enhances security by auto-locking after a set time.
✔️ Scalable & Modular – Can be expanded with additional devices.

🛠️ Hardware & Software Requirements
🔌 Hardware Components:
ESP32 – Microcontroller with Wi-Fi
DHT22 – Temperature & humidity sensor
PIR Sensor – Motion detection
Relay Module – Controls appliances
Servo Motor – Door lock mechanism
LEDs – Representing light and fan
🖥️ Software & Tools:
Arduino IDE – For programming ESP32
Flask – Laptop server setup for communication
Wokwi Simulator – Testing and simulation
Mobile App – Custom-built for user control
🔗 How It Works
1️⃣ The ESP32 connects to Wi-Fi and communicates with the Flask server on a laptop.
2️⃣ The mobile app sends control signals to the server.
3️⃣ The server processes the request and forwards commands to ESP32.
4️⃣ The ESP32 controls the fan, light, and door lock accordingly.
5️⃣ The system also monitors temperature, humidity, and motion detection for automation.

📷 Circuit Diagram & Demo
📌 (Add a circuit diagram screenshot and demo GIF here)

🔧 Setup & Installation
Connect the hardware components as per the circuit diagram.
Upload the ESP32 firmware using Arduino IDE.
Set up the Flask server on your laptop.
Configure the mobile app to communicate with the server.
Start the system and control devices remotely!
