# 🌐 Sand Cleaning Machine Dashboard (ESP32 + Firebase)

A **real-time IoT dashboard** for monitoring and controlling a **Sand Cleaning Machine** powered by **ESP32** and integrated with **Firebase Realtime Database**.

This project provides a modern, responsive web interface for viewing system status, sensor data, charging analytics, and sending remote commands.

---

## 🚀 Features

### 📊 Dashboard Overview

* Real-time machine monitoring
* Battery level and power status
* Session time and cleaned area
* System health (CPU temp, motor load, WiFi, etc.)

### 🔋 Charging Analytics

* Live charging status (Voltage, Current, Power)
* Time-to-full estimation
* Daily and lifetime charging stats
* Weekly charging visualization

### 📈 Usage Monitoring

* Session and lifetime usage tracking
* Battery consumption analytics
* Efficiency metrics (m² per Wh)

### 🌡 Sensor Monitoring

* Temperature & humidity
* Sand moisture detection
* Motor RPM and temperature
* Distance sensors (obstacle detection)
* GPS location tracking
* Bin fill level & vacuum pressure

### ⚙ Remote Controls

* Start / Stop cleaning
* Return to charging dock
* Sensor calibration
* Emergency stop

### 🔧 Settings & Configuration

* Feature toggles (Auto-return, Turbo mode, etc.)
* Firebase connection setup
* Threshold monitoring

### 📜 Logs System

* Real-time system logs
* Event tracking (commands, updates, alerts)

### 🧪 Demo Mode

* Built-in simulated data (no hardware required)

---

## 🛠 Tech Stack

### Hardware

* ESP32 Microcontroller

### Software

* HTML, CSS, JavaScript (Frontend Dashboard)
* Firebase Realtime Database
* Arduino (ESP32 firmware)

---

## 📂 Project Structure

```
📦 project-root
 ┣ 📜 html.h              # Embedded web dashboard (served by ESP32)
 ┣ 📜 iot_dashboard.ino   # ESP32 firmware (IoT logic + Firebase)
 ┗ 📜 README.md           # Project documentation
```

---

## ⚡ Setup Instructions

### 1. Upload Code to ESP32

* Open `iot_dashboard.ino` in Arduino IDE
* Install required ESP32 board support
* Configure WiFi credentials
* Upload to your ESP32

---

### 2. Configure Firebase

1. Go to Firebase Console
2. Create a new project
3. Enable **Realtime Database**
4. Copy your config credentials

In the dashboard UI:

* Enter:

  * API Key
  * Auth Domain
  * Database URL
  * Project ID

---

### 3. Run the Dashboard

* ESP32 hosts the web interface
* Open browser:

```
http://<ESP32-IP-ADDRESS>
```

---

## 🔌 Firebase Data Structure (Example)

```json
sandbot: {
  battery: {
    percentage: 85,
    health: 92
  },
  power: {
    watts: 18,
    voltage: 12.6,
    current: 1.4,
    charging: true
  },
  sensors: {
    air_temp: 28,
    humidity: 70,
    sand_moisture: 20
  },
  state: "cleaning"
}
```

---

## 🎮 Commands (Remote Control)

Commands are sent to:

```
sandbot/commands
```

Examples:

* `start`
* `stop`
* `return_to_charge`
* `calibrate`
* `emergency_stop`

---

## 🧠 How It Works

1. ESP32 collects sensor data
2. Data is pushed to Firebase
3. Web dashboard listens in real-time
4. UI updates instantly
5. Commands are sent back to ESP32 via Firebase

---

## 📱 Responsive Design

* Works on desktop, tablet, and mobile
* Adaptive grid layout
* Clean modern UI with dark theme

---

## 🧪 Demo Mode

If Firebase is not configured:

* Click **"Continue with Demo Data"**
* Simulated real-time data will run automatically

---

## ⚠️ Notes

* Ensure stable WiFi connection for ESP32
* Firebase rules should allow read/write access (for testing)
* Optimize security rules before production use

---

## 📌 Future Improvements

* Authentication system
* Historical data charts
* Mobile app integration
* AI-based cleaning optimization

---

## 👨‍💻 Author

Developed for IoT and embedded systems project.

---

## 📄 License

This project is for educational purposes. You may modify and use it freely.

---

✨ *Real-time monitoring meets smart automation.*
