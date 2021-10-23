/**
 * ***************************************************************************************************
 * @file main.cpp
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * ***************************************************************************************************
 */
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include "DhtSensor.h"
#include "SoilMoisture.h"

#define CHANNEL_ID 1540710
#define CHANNEL_API_KEY "C3MWNJUOTW5095ZC"

WiFiClient client;

DHTCore Dht11Sensor;

DHT dht(DHTPIN, DHTTYPE);
std::shared_ptr<DHT> pDht = std::make_shared<DHT>(dht);

DhtOutput_t Dht11OutputData;

// test :TODO remove 
int counter = 0;

#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "AndroidAP_note8"
#define WIFI_PASSWORD "sensor123"

void connectToWiFi();

void setup() 
{
  Serial.begin(9600);
  // connectToWiFi();
  // ThingSpeak.begin(client);
  Dht11Sensor.DhtInit(pDht);
}

void loop() 
{
  // counter++;

  // Writing to only one field.
  // ThingSpeak.writeField(CHANNEL_ID, 1, counter, CHANNEL_API_KEY);

  // Writing to multiple fields.

  // ThingSpeak.setField(1, counter);
  // ThingSpeak.setField(2, WiFi.RSSI());

  // ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  // A delay of 15s is required between consecutive data sent to ThingSpeak.
  // delay(15000);

  delay(2000);

  Dht11Sensor.DhtReadData(&Dht11OutputData, pDht);

  // Check if any reads failed and exit early (to try again).
  if (isnan(Dht11OutputData.humidity) || isnan(Dht11OutputData.temperatur))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(Dht11OutputData.temperatur, Dht11OutputData.humidity, false);

  Serial.print(F("Humidity: "));
  Serial.print(Dht11OutputData.humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Dht11OutputData.temperatur);
  Serial.print(F("°C "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print("\n");
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