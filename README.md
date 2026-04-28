# 🧅 Onion Storage System

## 📌 Overview
The Onion Storage System is an IoT-based solution designed to monitor and maintain optimal storage conditions for onions. It helps reduce post-harvest losses by tracking environmental factors like temperature and humidity.

This project is useful for farmers, warehouses, and agricultural storage facilities.

---

## 🚀 Features
- Real-time Temperature Monitoring  
- Humidity Detection  
- Alert System for abnormal conditions  
- IoT-based monitoring  
- Low-cost and efficient design  

---

## 🛠️ Components Used
- ESP32 / Arduino Microcontroller  
- DHT Sensor (Temperature & Humidity)  
- Power Supply  
- Connecting Wires  
- Breadboard / PCB  
- Buzzer (optional)  

---

## ⚙️ Working Principle
The system continuously reads temperature and humidity using a sensor.  
The microcontroller processes this data and compares it with predefined thresholds.

- If conditions are normal → System continues monitoring  
- If conditions exceed limits → Alert is triggered  

This ensures proper storage conditions and prevents onion spoilage.

---

## 📂 Project Structure

Onion_Storage_Sys/
│── Onion_Storage/
│ └── Onion_Storage.ino
│── Onion storage Crt.png
│── README.md

---

## ▶️ How to Run
1. Install Arduino IDE  
2. Open `Onion_Storage.ino`  
3. Connect ESP32/Arduino  
4. Select correct board and port  
5. Upload the code  
6. Open Serial Monitor  

---

## 📊 Applications
- Agricultural storage monitoring  
- Smart warehouses  
- Cold storage systems  
- Supply chain monitoring  

---

## ⚠️ Limitations
- Sensor accuracy may vary  
- Requires stable power supply  
- Basic alert system  

---

## 🔮 Future Scope
- Mobile app integration  
- Cloud storage and analytics  
- AI-based prediction system  
- Automated ventilation control  

---
