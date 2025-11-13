#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "REPLACE_WITH_YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Your_Project_Name"
#define BLYNK_AUTH_TOKEN "REPLACE_WITH_YOUR_BLYNK_AUTH_TOKEN"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// defining pin macros for easy use later
#define lpin1 2
#define lpin2 5
#define lpin3 23
#define gpin 34
#define spin 19
#define bpin 18
#define maxgas 2000

DHT dht(4, DHT22);         // temp + humidity sensor on pin 4
Servo door;               // servo object for the door
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD with I2C
int dk = 1;               // just a flag for door control

// WiFi + Blynk credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* auth = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// sends temp/humidity/gas data to Blynk every second
void sendSensor(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float g = analogRead(gpin);

  Blynk.virtualWrite(V4,t);  // temp to app
  Blynk.virtualWrite(V5,h);  // humidity to app
  Blynk.virtualWrite(V6,g);  // gas to app

  // if gas crosses danger limit, send alert
  if (g > maxgas) {
    Blynk.logEvent("gas_leakage_alert", "Gas Leakage Detected! Take immediate action.");
  }
}

// door control from Blynk switch
BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  if (pinValue == 1){
    dk = 0;          // disable default door closed if user manually opened it as interrupt
    door.write(0);   // open the door
  }
  else { dk = 1; }   // enable default door closed mode
}

// light 1 control
BLYNK_WRITE(V1){
  int pinValue = param.asInt();
  if (pinValue == 1){ digitalWrite(lpin1,HIGH); }
  else { digitalWrite(lpin1,LOW); }
}

// light 2 control
BLYNK_WRITE(V2){
  int pinValue = param.asInt();
  if (pinValue == 1){ digitalWrite(lpin2,HIGH); }
  else { digitalWrite(lpin2,LOW); }
}

// light 3 control
BLYNK_WRITE(V3){
  int pinValue = param.asInt();
  if (pinValue == 1){ digitalWrite(lpin3,HIGH); }
  else { digitalWrite(lpin3,LOW); }
}

void setup() {

  Serial.begin(115200);
  dht.begin(); // start temp sensor
  pinMode(lpin1,OUTPUT);
  pinMode(lpin2,OUTPUT);
  pinMode(lpin3,OUTPUT);
  pinMode(bpin,OUTPUT);
  door.attach(spin); // attach servo to pin

  Serial.println("All devices are connected");

  // fake startup animation on LCD
  lcd.init();
  lcd.backlight();
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Starting");
  delay(1000);

  // fake loading dots for loading effect
  lcd.setCursor(0,1);
  lcd.print(".");
  delay(700);
  lcd.print(".");
  delay(700);
  lcd.print(".");
  delay(700);
  lcd.print(".");
  delay(700);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome Home");
  delay(1000);
  lcd.clear();

  // connect to Blynk
  Blynk.begin(auth,ssid,pass);

  // send sensor data every 1 second
  timer.setInterval(1000L, sendSensor);
}

void loop() {

  Blynk.run(); // keeps Blynk running
  timer.run(); // handles timed functions

  float temp = dht.readTemperature();
  float gas = analogRead(gpin);

  // gas leak safety mechanism
  if(gas > maxgas){
    door.write(0);            // open the door automatically
    digitalWrite(bpin, HIGH); // beep/buzzer ON

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("!!! ALERT !!!");
    lcd.setCursor(0,1);
    lcd.print("GasLeak Detected");
  }
  else {
    digitalWrite(bpin, LOW); // safe, so buzzer off

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temp, 2);
    lcd.print((char)223); // degree symbol
    lcd.print("C  ");

    lcd.setCursor(0,1);
    lcd.print("Gas: Safe");

    if (dk){        // default door closed mode ON
      door.write(90); // keep door closed
    }
  }

  delay(1000); // small delay to avoid spam
}
