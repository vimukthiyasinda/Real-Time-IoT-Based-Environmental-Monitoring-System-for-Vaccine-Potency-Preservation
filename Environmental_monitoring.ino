#include <Wire.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


#define DHTPIN 4
#define DHTTYPE DHT22
#define LDR_DIGITAL_PIN 34 

DHT dht(DHTPIN, DHTTYPE);
TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

HardwareSerial sim800(1); // TX=17, RX=16
HardwareSerial neogps(2); // TX=27, RX=26

const float TEMP_MAX = 8.0; 
unsigned long lastAlertTime = 0;
const unsigned long alertInterval = 60000; 

void setup() {
  Serial.begin(115200);
  
  sim800.begin(9600, SERIAL_8N1, 16, 17);
  neogps.begin(9600, SERIAL_8N1, 26, 27); 
  
  dht.begin();
  pinMode(LDR_DIGITAL_PIN, INPUT); 
  
  if (!mpu.begin(0x68)) {
    Serial.println("Warning: MPU chip not identified, but attempting to continue...");
  }

  Serial.println("Vaccine System Initialized...");
}

void loop() {
  float temp = dht.readTemperature();
  int ldrStatus = digitalRead(LDR_DIGITAL_PIN); 
  
  sensors_event_t a, g, temp_mpu;
  mpu.getEvent(&a, &g, &temp_mpu);

  // GPS Data Reading
  while (neogps.available()) {
    gps.encode(neogps.read());
  }

  bool isError = false;
  String alertMsg = "VACCINE ALERT! ";

  // Temperature Logic
  if (temp > TEMP_MAX) {
    alertMsg += "High Temp: " + String(temp) + "C. ";
    isError = true;
  }
  
  // LDR Logic (Door Open)
  if (ldrStatus == LOW) { 
    alertMsg += "Box Opened! ";
    isError = true;
  }

  if (abs(a.acceleration.x) > 15 || abs(a.acceleration.y) > 15 || abs(a.acceleration.z) > 20) {
    alertMsg += "Heavy Impact! ";
    isError = true;
  }

  // SMS Logic
  if (isError && (millis() - lastAlertTime > alertInterval)) {
    if (gps.location.isValid()) {
      alertMsg += " Loc: http://maps.google.com/?q=" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    } else {
      alertMsg += " Loc: GPS Searching...";
    }
    sendSMS(alertMsg);
    lastAlertTime = millis();
  }

  delay(2000);
}

void sendSMS(String text) {
  Serial.println("Sending SMS...");
  sim800.println("AT+CMGF=1");
  delay(500);
  sim800.println("AT+CMGS=\"+94768915939\""); 
  delay(500);
  sim800.print(text);
  delay(100);
  sim800.write(26);
  delay(1000);
}