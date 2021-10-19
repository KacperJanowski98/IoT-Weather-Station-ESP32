#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>

#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "AndroidAP_note8"
#define WIFI_PASSWORD "sensor123"

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

void setup() 
{
  
}

void loop() 
{

}
