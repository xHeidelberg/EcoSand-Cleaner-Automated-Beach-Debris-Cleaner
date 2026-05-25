# ESP-NOW RC Car with Conveyor System

[cite_start]A robust, low-latency remote-controlled (RC) car system featuring precise servo steering [cite: 12, 13, 16][cite_start], a dual-bridge DC motor drive with software-controlled acceleration ramping [cite: 5, 21, 23][cite_start], and an integrated conveyor mechanism[cite: 24, 25]. [cite_start]Communication between the transmitter and receiver units is established using **ESP-NOW**[cite: 1, 33], a fast, connectionless wireless protocol developed by Espressif for ESP32 microcontrollers.

---

## System Architecture

The project consists of two distinct hardware layers, each driven by an ESP32 microcontroller:
1. [cite_start]**Transmitter Unit:** Reads inputs from a 2-axis analog joystick and a tactile pushbutton switch [cite: 39, 40, 42, 43][cite_start], processes the analog/digital inputs, and transmits state telemetry packets wirelessly[cite: 43].
2. [cite_start]**Receiver Unit:** Hosts a Wi-Fi Access Point [cite: 7][cite_start], parses incoming telemetric packets [cite: 6, 11][cite_start], controls an integrated steering servo [cite: 16][cite_start], regulates an H-bridge driver using soft-start acceleration ramping [cite: 21, 23][cite_start], and manages an auxiliary conveyor system[cite: 24, 25].

---

## Pin Configurations

### 1. Transmitter Module
| Peripheral Component | ESP32 GPIO Pin | Configuration Mode | Functional Description |
| :--- | :---: | :---: | :--- |
| **Joystick VRy** | `34` [cite: 39] | `INPUT` [cite: 39] | Analog read for longitudinal motion (Drive/Reverse) [cite: 42] |
| **Joystick VRx** | `35` [cite: 39] | `INPUT` [cite: 39] | Analog read for lateral motion (Left/Right Steering) [cite: 42] |
| **Joystick SW** | `32` [cite: 40] | `INPUT_PULLUP` [cite: 40] | Tactile digital switch for toggling conveyor system [cite: 43] |

### 2. Receiver Module
| Peripheral Subsystem | ESP32 GPIO Pin | Functional Role | Driver Type / Protocol |
| :--- | :---: | :--- | :--- |
| **Steering Servo** | `18` [cite: 2] | Hardware PWM Control Line | `ESP32Servo` Library [cite: 1, 8] |
| **Main Drive RPWM** | `25` [cite: 2] | Forward Speed Control (Right PWM) | Analog PWM [cite: 23] |
| **Main Drive LPWM** | `26` [cite: 2] | Reverse Speed Control (Left PWM) | Analog PWM [cite: 23] |
| **Main Drive R_EN** | `27` [cite: 2] | Forward Enable Line (Active HIGH) | Digital Output [cite: 8, 9] |
| **Main Drive L_EN** | `14` [cite: 2] | Reverse Enable Line (Active HIGH) | Digital Output [cite: 9] |
| **Conveyor RPWM** | `4` [cite: 2] | Forward Conveyor Speed Line | Analog PWM [cite: 24, 25] |
| **Conveyor LPWM** | `16` [cite: 2] | Reverse Conveyor Speed Line | Analog PWM [cite: 24, 25] |
| **Conveyor R_EN** | `17` [cite: 2] | Forward Conveyor Enable Line | Digital Output [cite: 9] |
| **Conveyor L_EN** | `5` [cite: 2] | Reverse Conveyor Enable Line | Digital Output [cite: 9] |
| **Status LED: Neutral**| `2` [cite: 2] | Active LOW Indicator for Drive Idle State | Digital Output [cite: 8, 21] |
| **Status LED: Center** | `15` [cite: 2] | Active LOW Indicator for Steering Idle State| Digital Output [cite: 8, 16] |

---

## Data Packet Structure

Telemetry is serialized into a structurally identical data format compiled on both architectures to maintain standard alignment over the air[cite: 3, 34]:

```cpp
typedef struct struct_message {
    int drive;       // Analog reading from 0 to 4095 (Center Deadzone: 1500 - 2500)
    int steer;       // Analog reading from 0 to 4095 (Center Deadzone: 1500 - 2500)
    int bsrButton;   // Digital state: LOW (0) = Pressed/ON, HIGH (1) = Released/OFF
} struct_message;
```