<div align="center">

# 🔧 Arduino Projects

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![STM32](https://img.shields.io/badge/STM32-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Embedded](https://img.shields.io/badge/Embedded%20Systems-555555?style=for-the-badge&logo=embarcadero&logoColor=white)

A collection of **9 embedded systems projects** built with real hardware and sensors —
covering security systems, parking automation, real-time clocks, relay control, LED effects, shift registers, and more.

**👨‍💻 Author:** Marnissi Ahmed Mustapha &nbsp;|&nbsp; **📅 Last Updated:** May 2026

[![GitHub](https://img.shields.io/badge/GitHub-AhmedMustaphaMarnissi-181717?style=flat-square&logo=github)](https://github.com/AhmedMustaphaMarnissi)

</div>

---

## ⚡ TL;DR

**9 standalone embedded sketches** — each project is fully self-contained with its own wiring logic, targeting real embedded use cases: sensor reading, output control, LCD display, keypad input, RTC timekeeping, relay automation, SPI shift registers, and 7-segment displays.

> All code written in **C++ (Arduino framework)**. No simulation — built for real hardware.

---

## 📋 Projects Overview

| # | Project | Sensors / Components | Description |
|---|---|---|---|
| 1 | [DangerDetecting](#1-dangerdetecting) | Ultrasonic, Buzzer, LEDs | Proximity danger alert system |
| 2 | [LCDRelayApp](#2-lcdrelayapp) | LCD, Relay, Push Button | Relay control with LCD status display |
| 3 | [LcdSwitchDateManage](#3-lcdswitchdatemanage) | LCD, RTC, Switch | Date/time display with switch navigation |
| 4 | [LedDancing](#4-leddancing) | LEDs | Sequenced LED animation patterns |
| 5 | [MultiScreenValues](#5-multiscreenvalues) | LCD, Multiple Sensors | Multi-screen sensor value display |
| 6 | [Parking](#6-parking) | Ultrasonic, Servo, LCD, LEDs | Smart parking slot management system |
| 7 | [PasswordLock](#7-passwordlock) | Keypad, LCD, Servo/LED | Keypad-based password security lock |
| 8 | [RTC_LcdTimer](#8-rtc_lcdtimer) | RTC DS1307/DS3231, LCD | Real-time clock display with LCD |
| 9 | [Système Capteur de Stationnement](#9-système-capteur-de-stationnement) | STM32 Nucleo L031K6, HC-SR04, 2× 74HC595, 2× 7-Segment, LEDs, Buzzer, Switch | STM32-based parking distance sensor with 7-segment display |

---

## Projects

---

### 1. DangerDetecting

**Folder:** `DangerDetecting/`

A proximity-based danger detection system using an **HC-SR04 ultrasonic sensor**. As an object gets closer, the system escalates its alert: LEDs change color/state and a **buzzer** sounds with increasing frequency. Useful as a collision warning, obstacle detection, or safety boundary alert.

**Components:** Arduino UNO, HC-SR04 Ultrasonic Sensor, Buzzer, LEDs (Red/Yellow/Green), Resistors

**How it works:**
```
Object detected
      ↓
Measure distance (HC-SR04)
      ↓
Distance > threshold  →  Green LED ON  |  Buzzer OFF
Distance = warning    →  Yellow LED ON |  Buzzer slow beep
Distance = danger     →  Red LED ON    |  Buzzer fast beep
```

**Key concepts:** `pulseIn()`, distance calculation with sound speed, threshold-based alerting, PWM buzzer tone

---

### 2. LCDRelayApp

**Folder:** `LCDRelayApp/`

A relay control application with real-time **LCD feedback**. A push button or sensor input toggles a relay module ON/OFF, and the LCD displays the current relay state. Useful for controlling high-voltage devices (lights, fans, motors) from Arduino with a visual status indicator.

**Components:** Arduino UNO, 16×2 LCD (I2C or parallel), Relay Module, Push Button, Resistors

**How it works:**
```
Button pressed
      ↓
Toggle relay state (ON / OFF)
      ↓
LCD updates → "Relay: ON" / "Relay: OFF"
      ↓
Relay pin drives connected device
```

**Key concepts:** Digital output control, relay switching, LCD display with `LiquidCrystal` library, debounce logic

---

### 3. LcdSwitchDateManage

**Folder:** `LcdSwitchDateManage/`

A date and time management system combining an **RTC module**, **LCD display**, and a **switch** for navigation. The switch cycles through different display screens (date, time, day of week) or allows manual adjustment of the stored date/time values.

**Components:** Arduino UNO, RTC Module (DS1307/DS3231), 16×2 LCD, Slide/Toggle Switch, Resistors

**How it works:**
```
RTC keeps time independently of Arduino power
          ↓
LCD displays current date / time
          ↓
Switch press → cycle through screens or adjust values
          ↓
Updated values written back to RTC
```

**Key concepts:** I2C communication, `RTClib` / `Wire` library, switch state machine, multi-screen LCD navigation

---

### 4. LedDancing

**Folder:** `LedDancing/`

A visual LED sequencing project that creates animated lighting patterns across multiple LEDs. Different patterns (wave, blink, chase, fade) are programmed and cycle automatically, demonstrating timing control and creative output sequencing.

**Components:** Arduino UNO, Multiple LEDs (4–8+), Resistors

**How it works:**
```
Loop begins
      ↓
Pattern 1: Sequential chase  (left to right)
Pattern 2: All blink together
Pattern 3: Alternate odd/even
Pattern 4: Reverse chase
      ↓
Repeat with configurable delays
```

**Key concepts:** `digitalWrite()`, `delay()` / `millis()` timing, array-based pin management, pattern sequencing

---

### 5. MultiScreenValues

**Folder:** `MultiScreenValues/`

A multi-screen LCD display system that reads values from **multiple sensors** and shows each on a separate screen, cycling automatically or on button press. Demonstrates how to manage a single LCD display across multiple data sources cleanly.

**Components:** Arduino UNO, 16×2 LCD, Multiple sensors (temperature, distance, light, etc.), Push Button (optional)

**How it works:**
```
Read all sensor values
          ↓
Screen 1: Sensor A value + label
          ↓  (auto cycle / button press)
Screen 2: Sensor B value + label
          ↓
Screen 3: Sensor C value + label
          ↓
Loop back to Screen 1
```

**Key concepts:** LCD screen management, `lcd.clear()` transitions, multi-sensor reading, state-based display switching

---

### 6. Parking

**Folder:** `Parking/`

A smart parking slot management system — one of the more complete projects in this collection. Uses **ultrasonic sensors** to detect whether parking slots are occupied or free, displays slot status on an **LCD**, uses **LEDs** (red = occupied, green = free) per slot, and a **servo motor** acts as a barrier gate that opens when a free slot is available.

**Components:** Arduino UNO, HC-SR04 Ultrasonic Sensor(s), Servo Motor, 16×2 LCD, Red/Green LEDs, Resistors

**How it works:**
```
Ultrasonic sensors scan each parking slot
              ↓
Slot occupied  →  Red LED ON  |  LCD shows "SLOT X: FULL"
Slot free      →  Green LED ON |  LCD shows "SLOT X: FREE"
              ↓
Car approaches entrance sensor
              ↓
Free slot available  →  Servo opens gate
No free slots        →  Servo stays closed | LCD: "PARKING FULL"
```

**Key concepts:** Multiple ultrasonic sensors, servo motor control, slot state management, gate automation logic

---

### 7. PasswordLock

**Folder:** `PasswordLock/`

A keypad-based password security lock. The user enters a password on a **4×4 matrix keypad**, the input is shown (masked) on an **LCD**, and if the password matches the stored value, the lock opens (LED turns green / servo motor rotates). After a configurable number of wrong attempts, the system enters a lockout mode.

**Components:** Arduino UNO, 4×4 Matrix Keypad, 16×2 LCD, Servo Motor or LED (lock indicator), Buzzer (optional)

**How it works:**
```
User presses keys on keypad
          ↓
LCD shows: "Enter Password: ****"
          ↓
Enter key pressed
          ↓
Password correct  →  Green LED / Servo opens  |  LCD: "ACCESS GRANTED"
Password wrong    →  Red LED / Buzzer beep    |  LCD: "WRONG PASSWORD"
          ↓
3 wrong attempts  →  Lockout mode  |  LCD: "LOCKED - WAIT"
```

**Key concepts:** `Keypad` library, password comparison, `Servo` library, lockout counter, masked input display

---

### 8. RTC_LcdTimer

**Folder:** `RTC_LcdTimer/`

A real-time clock display using an **RTC DS1307 or DS3231 module** and a **16×2 LCD**. The RTC maintains accurate time independently of Arduino power (battery-backed), and the LCD displays the current time and date in a clean, readable format. The RTC retains time even after the Arduino is powered off.

**Components:** Arduino UNO, RTC Module (DS1307 or DS3231), 16×2 LCD (I2C), CR2032 Battery (for RTC backup)

**How it works:**
```
Arduino powers on
      ↓
Read time from RTC via I2C
      ↓
LCD Line 1: HH:MM:SS
LCD Line 2: DD/MM/YYYY  Day
      ↓
Update display every second
      ↓
RTC continues keeping time even when Arduino is off
```

**Key concepts:** I2C protocol, `RTClib` library, `Wire.h`, time formatting, battery-backed timekeeping

---

### 9. Système Capteur de Stationnement

**Folder:** `systeme-capteur-de-stationement/`

> ⚠️ **This project uses an STM32 Nucleo L031K6**, not Arduino UNO. It is programmed via the Arduino framework with STM32duino support.

A complete **STM32-based parking distance sensor system** simulated in Wokwi. An **HC-SR04** ultrasonic sensor measures the distance between a vehicle and a wall, and the measured distance (in cm) is displayed in real time on **two 7-segment displays** driven by **two 74HC595 SPI shift registers**. Three **LEDs** (green / yellow / red) give an instant color-coded proximity warning, and a **buzzer** beeps with increasing frequency as the vehicle gets closer. A **slide switch** enables or disables the system entirely.

**Components:** STM32 Nucleo L031K6, HC-SR04 Ultrasonic Sensor, 2× 74HC595 Shift Register, 2× 7-Segment Display (common cathode), Red LED, Yellow LED, Green LED, Buzzer, Slide Switch, Resistors, Breadboard

**Circuit diagram:**

![Circuit](circuit.png)

**How it works:**
```
Slide switch ON
        ↓
HC-SR04 triggers ultrasonic pulse (TRIG pin)
        ↓
Measure echo pulse width (ECHO pin) → pulseIn()
        ↓
Calculate distance = (duration × 0.034) / 2  (cm)
        ↓
Send 2-digit value to 74HC595 shift registers via SPI
        ↓
7-Segment displays show distance in cm (e.g. "42")
        ↓
Distance > 40 cm  →  Green LED ON   | Buzzer OFF
Distance 20–40 cm →  Yellow LED ON  | Buzzer slow beep
Distance < 20 cm  →  Red LED ON     | Buzzer fast beep
        ↓
Slide switch OFF  →  All outputs OFF | Displays blank
```

**Key concepts:** STM32 Nucleo L031K6, SPI shift register chaining (`SPI.transfer()`), 7-segment digit encoding, `pulseIn()` distance calculation, hardware SPI pin mapping, threshold-based LED + buzzer alerting, switch-controlled system enable/disable

**Board setup in Arduino IDE:**
```
Board:   STM32 Nucleo-32 (STM32duino)
Variant: Nucleo L031K6
Port:    COMX (ST-Link)
```

---

## 🔩 Hardware & Libraries Used

### Common Hardware

| Component | Used In |
|---|---|
| Arduino UNO | DangerDetecting, LCDRelayApp, LcdSwitchDateManage, LedDancing, MultiScreenValues, Parking, PasswordLock, RTC_LcdTimer |
| STM32 Nucleo L031K6 | Système Capteur de Stationnement |
| HC-SR04 Ultrasonic Sensor | DangerDetecting, Parking, Système Capteur de Stationnement |
| 16×2 LCD Display | LCDRelayApp, LcdSwitchDateManage, MultiScreenValues, Parking, PasswordLock, RTC_LcdTimer |
| 74HC595 Shift Register | Système Capteur de Stationnement |
| 7-Segment Display | Système Capteur de Stationnement |
| RTC DS1307 / DS3231 | LcdSwitchDateManage, RTC_LcdTimer |
| 4×4 Matrix Keypad | PasswordLock |
| Servo Motor | Parking, PasswordLock |
| Relay Module | LCDRelayApp |
| Buzzer | DangerDetecting, PasswordLock, Système Capteur de Stationnement |
| Slide Switch | Système Capteur de Stationnement |
| LEDs (Red / Green / Yellow) | DangerDetecting, LedDancing, Parking, PasswordLock, Système Capteur de Stationnement |

### Libraries

| Library | Purpose |
|---|---|
| `LiquidCrystal` / `LiquidCrystal_I2C` | LCD display control |
| `RTClib` | RTC DS1307 / DS3231 communication |
| `Wire` | I2C communication |
| `Keypad` | Matrix keypad reading |
| `Servo` | Servo motor control |
| `SPI` | SPI communication for 74HC595 shift registers |

---

## 🚀 Getting Started

### Prerequisites

- **Arduino UNO** (or compatible board) for most projects
- **STM32 Nucleo L031K6** for `Système Capteur de Stationnement`
- **Arduino IDE** 1.8.x or 2.x
- Required hardware components per project (see each project section)
- Required libraries installed via **Library Manager**

### Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ahmedmustaphamarnissi/ArduinoProjects.git
   ```

2. **Open Arduino IDE** and open the `.ino` file from the desired project folder.

3. **Install required libraries** via `Sketch → Include Library → Manage Libraries`:
   - `LiquidCrystal_I2C` by Frank de Brabander
   - `RTClib` by Adafruit
   - `Keypad` by Mark Stanley & Alexander Brevig
   - `Servo` (built-in)
   - `SPI` (built-in)

4. **For STM32 projects** — install STM32duino board support:
   - Go to `File → Preferences → Additional Board Manager URLs`
   - Add: `https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json`
   - Then `Tools → Board → Board Manager` → search **STM32** → install

5. **Wire up the components** according to the pin definitions at the top of each `.ino` file.

6. **Select your board and port:**
   - Arduino projects: `Tools → Board → Arduino UNO`
   - STM32 project: `Tools → Board → STM32 Nucleo-32 → Nucleo L031K6`

7. **Upload:** Click the Upload button or press `Ctrl + U`.

---

## 💡 Skills Demonstrated

| Skill | Projects |
|---|---|
| Ultrasonic distance measurement | DangerDetecting, Parking, Système Capteur de Stationnement |
| SPI shift register control (74HC595) | Système Capteur de Stationnement |
| 7-segment display digit encoding | Système Capteur de Stationnement |
| STM32 Nucleo (STM32duino) | Système Capteur de Stationnement |
| LCD display management (parallel + I2C) | LCDRelayApp, LcdSwitchDateManage, MultiScreenValues, Parking, PasswordLock, RTC_LcdTimer |
| RTC / real-time timekeeping (I2C) | LcdSwitchDateManage, RTC_LcdTimer |
| Servo motor control | Parking, PasswordLock |
| Relay switching | LCDRelayApp |
| Keypad matrix input | PasswordLock |
| Multi-state / state machine logic | PasswordLock, LcdSwitchDateManage, Parking, Système Capteur de Stationnement |
| LED sequencing & timing | LedDancing |
| Multi-sensor data display | MultiScreenValues |
| Buzzer / PWM audio | DangerDetecting, PasswordLock, Système Capteur de Stationnement |

---

## 🧠 What I Learned

- Reading and processing data from ultrasonic, RTC, and keypad modules
- Driving 7-segment displays via **74HC595 shift registers** using SPI (`SPI.transfer()`)
- Chaining multiple shift registers to control multiple digit displays
- Working with **STM32 Nucleo L031K6** via the Arduino/STM32duino framework
- Managing the I2C bus with multiple devices (`Wire.h`)
- Building **state machines** for multi-screen navigation and security lockout logic
- Controlling external actuators (servo motors, relays) from sensor inputs
- Designing complete embedded workflows: **sense → process → actuate → display**
- Structuring clean, readable Arduino C++ across multi-component projects
- Debugging hardware circuits and resolving SPI timing and wiring issues

---

<div align="center">

Built with ❤️ in Bizerte, Tunisia 🇹🇳

[![GitHub](https://img.shields.io/badge/GitHub-AhmedMustaphaMarnissi-181717?style=for-the-badge&logo=github)](https://github.com/AhmedMustaphaMarnissi)

</div>
