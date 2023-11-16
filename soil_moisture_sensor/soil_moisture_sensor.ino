/* #include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C */
#include <Arduino.h>
#include <SoftwareSerial.h>

#define LED_PIN 8

#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to (DHT11)
dht DHT;

SoftwareSerial port(9, 10);  // RX, TX

const int sensor_pin = A1;	/* Soil moisture sensor O/P pin */

bool LED_ON = false;

void setup() {

  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);	/* Define baud rate for serial communication */
  port.begin(9600); 
  // bool status;
  
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  /* status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }  */

}

void loop() {

  if (port.available() > 0) {
    char receivedChar = port.read();
    Serial.print(receivedChar);

    if (receivedChar == 'Y') {
      LED_ON = true;
    } else {
      LED_ON = false;
    }
  }

  if (LED_ON) {
    digitalWrite(LED_PIN, HIGH);  // Lámpa felvillan
    delay(500);
    } else {
    digitalWrite(LED_PIN, LOW);  // Lámpa felvillan
    delay(500);
  } 

  DHT.read11(dht_apin);
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Talajnedvesség = ");
  Serial.print(moisture_percentage);
  Serial.print("%  ");
  Serial.print("Páratartalom = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("Hőmérséklet = ");
  Serial.print(DHT.temperature); 
  Serial.println("C°  ");
 /*
  Serial.print("Légnyomás = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa ");
  Serial.print("Tengerszint feletti magasság = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print(" m");
*/
  Serial.print("\n");
  delay(1000);
}