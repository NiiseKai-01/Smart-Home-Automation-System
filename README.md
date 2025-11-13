# Smart-Home-Automation-System
A smart home automation system using ESP32 and Blynk integration

This project is a basic home automation system built using an ESP32 board. It uses the Blynk IoT platform to control appliances and monitor sensors remotely. The system includes temperature and humidity monitoring, gas detection, servo door control, LED control, a buzzer, and a 16x2 I2C LCD display.

This README explains everything you need to run the project.

1. Features

Control three lights using the Blynk mobile app

Control a servo-based door lock using the app

DHT22 sensor for temperature and humidity

MQ2 sensor for gas leakage detection

LCD display for live temperature and gas status

Automatic safety response during a gas leak

Buzzer alarm when gas level is high

Periodic sensor data updates sent to the Blynk app

2. Hardware Required

ESP32 Development Board

DHT22 Temperature and Humidity Sensor

MQ2 Gas Sensor

16x2 I2C LCD Display (0x27)

Servo Motor (SG90 or similar)

Buzzer

Three LEDs (or three relays)

Jumper wires

Breadboard

Power supply or USB cable

3. Pin Connections
Component	ESP32 Pin
Light 1 (LED/Relay)	GPIO 2
Light 2 (LED/Relay)	GPIO 5
Light 3 (LED/Relay)	GPIO 23
MQ2 Gas Sensor	GPIO 34
Servo Motor	GPIO 19
Buzzer	GPIO 18
DHT22 Sensor	GPIO 4
LCD (I2C)	SDA/SCL pins of ESP32
4. Blynk Setup

Create an account on the Blynk IoT app

Create a new Template

Copy your Template ID, Template Name, and Blynk Auth Token

Add the following Widgets in the Web or Mobile Dashboard:

Widget	Virtual Pin
Switch for Light 1	V1
Switch for Light 2	V2
Switch for Light 3	V3
Switch for Door	V0
Temperature Display	V4
Humidity Display	V5
Gas Level Display	V6

Go to Automations → Create a new Event named:
gas_leakage_alert

5. Software Setup

Install Arduino IDE

Install ESP32 Board Support

Open Boards Manager

Search "ESP32"

Install "ESP32 by Espressif Systems"

Install these libraries from Library Manager:

Blynk

ESP32Servo

DHT sensor library

LiquidCrystal_I2C

Wire

Open the code file (.ino)

Replace these placeholders with your real values:

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";


Select board:
Tools → Board → ESP32 Dev Module

Upload the code to the ESP32.

6. How the System Works

ESP32 connects to your Wi-Fi and Blynk cloud

Sensor readings (temperature, humidity, gas) are sent every second

You can turn lights on or off through the app

You can open or close the door using the app

When gas levels exceed the safe limit:

Buzzer turns on

Door opens automatically

LCD displays a warning

Blynk notification is triggered

7. File Description

sketch.ino
Contains the full ESP32 program with LCD display control, sensor reading, Blynk communication, and gas safety logic.

8. Notes

Ensure your Wi-Fi network is 2.4 GHz.

Make sure the MQ2 sensor has warmed up for a few seconds before reading values.

Servo requires stable power; avoid powering it directly from USB if it glitches.
