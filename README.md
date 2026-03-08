<div align="center">

![logo](https://img.shields.io/badge/Project-Embedded_System_Design-E8FF00?style=for-the-badge&labelColor=232626&color=ff715b)

# Smart Home Automation System

**A smart home automation system using ESP32 and Blynk integration**

<br/>

[![ESP32](https://img.shields.io/badge/Board-ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=E7352C&labelColor=0d0d0d)](https://www.espressif.com/)
[![Blynk](https://img.shields.io/badge/Platform-Blynk_IoT-23C48E?style=for-the-badge&logo=blynk&logoColor=23C48E&labelColor=0d0d0d)](https://blynk.io/)
[![Arduino](https://img.shields.io/badge/IDE-Arduino-00979C?style=for-the-badge&logo=arduino&logoColor=00979C&labelColor=0d0d0d)](https://www.arduino.cc/)

<br/>

<a href="#features"><kbd> <br> Features <br> </kbd></a>&ensp;
<a href="#hardware"><kbd> <br> Hardware <br> </kbd></a>&ensp;
<a href="#wiring"><kbd> <br> Wiring <br> </kbd></a>&ensp;
<a href="#blynk"><kbd> <br> Blynk Setup <br> </kbd></a>&ensp;
<a href="#software"><kbd> <br> Software <br> </kbd></a>&ensp;
<a href="#how-it-works"><kbd> <br> How It Works <br> </kbd></a>&ensp;
<a href="#notes"><kbd> <br> Notes <br> </kbd></a>

</div>

<br/>

---

<h2 id="gallery">// GALLERY</h2>

<div align="center">

<table>
  <tr>
    <td align="center"><img src="Project pictures/IMG_20251122_213228.jpg" width="300" alt="House model exterior"/></td>
    <td align="center"><img src="Project pictures/IMG_20251122_213235.jpg" width="300" alt="House model side with electronics"/></td>
    <td align="center"><img src="Project pictures/IMG_20251122_215212.jpg" width="300" alt="House model interior"/></td>
  </tr>
  <tr>
    <td align="center"><img src="Project pictures/IMG_20251122_215233.jpg" width="300" alt="LCD display showing temperature and gas status"/></td>
    <td align="center"><img src="Project pictures/IMG_20251122_215254.jpg" width="300" alt="ESP32 breadboard wiring"/></td>
  </tr>
</table>

</div>

---

<h2 id="features">// FEATURES</h2>

&ensp;› Control **3 lights** remotely via the Blynk mobile app

&ensp;› **Servo-based door lock** control from the app

&ensp;› **DHT22** sensor for live temperature & humidity readings

&ensp;› **MQ2** gas sensor for leakage detection with auto-safety response

&ensp;› **16x2 I2C LCD** display showing live temperature and gas status

&ensp;› **Buzzer alarm** triggered when gas levels exceed safe threshold

&ensp;› Periodic sensor data updates pushed to the Blynk cloud every second

---

<h2 id="hardware">// HARDWARE REQUIRED</h2>

&ensp;› ESP32 Development Board

&ensp;› DHT22 Temperature and Humidity Sensor

&ensp;› MQ2 Gas Sensor

&ensp;› 16x2 I2C LCD Display `(address: 0x27)`

&ensp;› Servo Motor (SG90 or similar)

&ensp;› Buzzer

&ensp;› 3× LEDs or Relay Modules

&ensp;› Jumper wires, Breadboard, Power supply / USB cable

---

<h2 id="wiring">// PIN CONNECTIONS</h2>

<br/>

<div align="center">

| Component | ESP32 Pin |
|:---|:---:|
| Light 1 (LED / Relay) | `GPIO 2` |
| Light 2 (LED / Relay) | `GPIO 5` |
| Light 3 (LED / Relay) | `GPIO 23` |
| MQ2 Gas Sensor | `GPIO 34` |
| Servo Motor | `GPIO 19` |
| Buzzer | `GPIO 18` |
| DHT22 Sensor | `GPIO 4` |
| LCD (I2C) | `SDA / SCL` |

</div>

---

<h2 id="blynk">// BLYNK SETUP</h2>

**1.** Create an account on the [Blynk IoT platform](https://blynk.io/)

**2.** Create a new **Template** and copy your `Template ID`, `Template Name`, and `Auth Token`

**3.** Add the following widgets to your Web or Mobile Dashboard:

<br/>

<div align="center">

| Widget | Virtual Pin |
|:---|:---:|
| Switch — Light 1 | `V1` |
| Switch — Light 2 | `V2` |
| Switch — Light 3 | `V3` |
| Switch — Door | `V0` |
| Temperature Display | `V4` |
| Humidity Display | `V5` |
| Gas Level Display | `V6` |

</div>

<br/>

**4.** Go to **Automations → Create a new Event** named:

```
gas_leakage_alert
```

---

<h2 id="software">// SOFTWARE SETUP</h2>

**1. Install Arduino IDE** → [arduino.cc/en/software](https://www.arduino.cc/en/software)

**2. Install ESP32 Board Support**

```
Tools → Boards Manager → Search "ESP32" → Install "ESP32 by Espressif Systems"
```

**3. Install required libraries via Library Manager:**

```
Blynk
ESP32Servo
DHT sensor library
LiquidCrystal_I2C
Wire
```

**4. Open `sketch.ino` and replace the placeholders:**

```cpp
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
```

**5. Select board and upload:**

```
Tools → Board → ESP32 Dev Module → Upload
```

---

<h2 id="how-it-works">// HOW IT WORKS</h2>

&ensp;› ESP32 connects to your **Wi-Fi** and the **Blynk cloud** on boot

&ensp;› Sensor readings (temperature, humidity, gas) are **pushed every second**

&ensp;› Lights and door can be toggled **remotely from the Blynk app**

&ensp;› When gas levels exceed the safe threshold:

```
  ├── Buzzer turns ON
  ├── Door servo opens automatically
  ├── LCD displays a WARNING message
  └── Blynk notification event is triggered
```

---

<h2 id="files">// FILE DESCRIPTION</h2>

> **`sketch.ino`** — Full ESP32 program containing LCD control, sensor reading, Blynk communication, and gas safety logic

---

<h2 id="notes">// NOTES</h2>

&ensp;› Ensure your Wi-Fi network is **2.4 GHz** (ESP32 does not support 5 GHz)

&ensp;› Allow the **MQ2 sensor to warm up** for a few seconds before readings stabilize

&ensp;› The servo may glitch on USB power — use a **dedicated power supply** if needed

---

<div align="center">

![footer](https://img.shields.io/badge/Embedded_Systems_Design_Project-ESP32_%26_Blynk-E7352C?style=flat-square&labelColor=0d0d0d)

</div>
