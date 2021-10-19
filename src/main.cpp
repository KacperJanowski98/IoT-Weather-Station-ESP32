#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const int LED_B = 13;

void setup() 
{
  pinMode (LED_B, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_B, HIGH);
  delay(1000);
  digitalWrite(LED_B, LOW);
  delay(1000);
}
