/**
 * ***************************************************************************************************
 * @file main.cpp
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include "DhtSensor.h"

#define CHANNEL_ID 1540710
#define CHANNEL_API_KEY "C3MWNJUOTW5095ZC"

WiFiClient client;
DHT dht11(DHTPIN, DHTTYPE);
DHT dht22(DHT22PIN, DHT22TYPE);

DHTCore Dht11Sensor(std::make_shared<DHT>(dht11), 0.0f, 0.0f, 0.0f);

DHTCore Dht22Sensor(std::make_shared<DHT>(dht22), 0.0f, 0.0f, 0.0f);

#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "AndroidAP_note8"
#define WIFI_PASSWORD "sensor123"

void connectToWiFi();

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  connectToWiFi();
  ThingSpeak.begin(client);
  Dht11Sensor.DhtInit();
  Dht22Sensor.DhtInit();
}

void loop() 
{
  Dht11Sensor.DhtReadData();
  Dht22Sensor.DhtReadData();

  // Check if any reads failed and exit early (to try again).
  if (isnan(Dht11Sensor.getHumidity()) || isnan(Dht11Sensor.getTemperature()))
  {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(Dht22Sensor.getHumidity()) || isnan(Dht22Sensor.getTemperature()))
  {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  Dht11Sensor.calculatedTemperature();

  Dht22Sensor.calculatedTemperature();

  // Serial display
  Serial.println("Inside measure:");
  Dht11Sensor.displayParameter();
  Serial.println("Outside measure:");
  Dht22Sensor.displayParameter();

  // Writing to only one field.
  // ThingSpeak.writeField(CHANNEL_ID, 1, counter, CHANNEL_API_KEY);

  // Writing to multiple fields.
  ThingSpeak.setField(1, Dht11Sensor.getComputeHeat());
  ThingSpeak.setField(2, Dht11Sensor.getHumidity());
  ThingSpeak.setField(3, Dht22Sensor.getComputeHeat());
  ThingSpeak.setField(4, Dht22Sensor.getHumidity());

  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  // A delay of 15s is required between consecutive data sent to ThingSpeak.
  delay(15000);
}

void connectToWiFi()
{
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  // Keep looping while we're not connected and haven't reached the timeout
  while (WiFi.status() != WL_CONNECTED &&
          millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  // Make sure we're actually connected, otherwise go to deep sleep
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(" Failed!");
    ESP.restart();  // Restrart ESP
  }
  else
  {
    Serial.print(" Connected!");
    Serial.println(WiFi.localIP());
  }
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/