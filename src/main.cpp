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
#include <NTPClient.h>
#include <HTTPClient.h>
#include "ThingSpeak.h"
#include "DhtSensor.h"
#include "config.h"

WiFiUDP ntpUDP;                       /**< WiFiUDP class object */
NTPClient ntpClient(ntpUDP);          /**< NTPClient class object */

HTTPClient httpInflux;                /**< HTTPClient class object for Influx */
HTTPClient httpLoki;                  /**< HTTPClient class object for Loki */
HTTPClient httpGraphite;              /**< HTTPClient class object for Graphite */

WiFiClient client;                    /**< WiFiClient class object to support internet connection */
DHT dht11(DHTPIN, DHTTYPE);           /**< DHT class object to support DHT11 sensor */
DHT dht22(DHT22PIN, DHT22TYPE);       /**< DHT class object to support DHT22 sensor */

/**
 * @brief Sensor initialization
 * 
 */
DHTCore Dht11Sensor(std::make_shared<DHT>(dht11), 0.0f, 0.0f, 0.0f);

DHTCore Dht22Sensor(std::make_shared<DHT>(dht22), 0.0f, 0.0f, 0.0f);

/**
 * @brief Function declarations
 * 
 */
void connectToWiFi();
void submitToInflux(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside);
void submitToLoki(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside, String message);
void submitToGraphite(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside);

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  connectToWiFi();
  /** Initialize a NTPClient to get time */
  ntpClient.begin();
  /** Initialize a ThingSpeak client */
  ThingSpeak.begin(client);
  /** Initialize DHT sensors */
  Dht11Sensor.DhtInit();
  Dht22Sensor.DhtInit();
}

void loop() 
{
  Dht11Sensor.DhtReadData();
  Dht22Sensor.DhtReadData();

  /** Check if any reads failed and exit early (to try again). */
  if (isnan(Dht11Sensor.getHumidity()) || isnan(Dht11Sensor.getTemperature()))
  {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  /** Check if any reads failed and exit early (to try again). */
  if (isnan(Dht22Sensor.getHumidity()) || isnan(Dht22Sensor.getTemperature()))
  {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  /** Update time via NTP if required */
  while (!ntpClient.update()) {
    yield();
    ntpClient.forceUpdate();
  }

  /** Get current timestamp for HTTP */
  unsigned long ts = ntpClient.getEpochTime();

  /** Get measure */
  Dht11Sensor.calculatedTemperature();
  Dht22Sensor.calculatedTemperature();

  /** Serial display */
  Serial.println("Inside measure:");
  Dht11Sensor.displayParameter();
  Serial.println("Outside measure:");
  Dht22Sensor.displayParameter();

  /** Writing to only one field. */
  /** ThingSpeak.writeField(CHANNEL_ID, 1, counter, CHANNEL_API_KEY); */

  /** Writing to multiple fields. */
  ThingSpeak.setField(1, Dht11Sensor.getComputeHeat());
  ThingSpeak.setField(2, Dht11Sensor.getHumidity());
  ThingSpeak.setField(3, Dht22Sensor.getComputeHeat());
  ThingSpeak.setField(4, Dht22Sensor.getHumidity());

  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  String message = "Ok";

  /** Send data to Graphana */
  submitToInflux(ts, Dht11Sensor.getComputeHeat(), Dht11Sensor.getHumidity(), Dht22Sensor.getComputeHeat(), Dht22Sensor.getHumidity());
  submitToGraphite(ts, Dht11Sensor.getComputeHeat(), Dht11Sensor.getHumidity(), Dht22Sensor.getComputeHeat(), Dht22Sensor.getHumidity());
  submitToLoki(ts, Dht11Sensor.getComputeHeat(), Dht11Sensor.getHumidity(), Dht22Sensor.getComputeHeat(), Dht22Sensor.getHumidity(), message);

  /** A delay of 15s is required between consecutive data sent to ThingSpeak. */
  delay(15000);
}

void connectToWiFi()
{
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  /** Keep looping while we're not connected and haven't reached the timeout */
  while (WiFi.status() != WL_CONNECTED &&
          millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  /** Make sure we're actually connected, otherwise go to deep sleep */
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(" Failed!");
    ESP.restart();  /** Restrart ESP */
  }
  else
  {
    Serial.print(" Connected!");
    Serial.println(WiFi.localIP());
  }
}

/** Function to submit metrics to Influx */
void submitToInflux(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside)
{
  String influxClient = String("https://") + INFLUX_HOST + "/api/v2/write?org=" + INFLUX_ORG_ID + "&bucket=" + INFLUX_BUCKET + "&precision=s";
  String body = String("temperature inside value=") + tempInside + " " + ts + "\n" + "humidity inside value=" + humInside + " " + ts + "\n" + "temperature outside value=" + tempOutSide + " " + ts + "\n" + "humidity outside value=" + humOutside + " " + ts;

  /** Submit POST request via HTTP */
  httpInflux.begin(influxClient);
  httpInflux.addHeader("Authorization", INFLUX_TOKEN);
  int httpCode = httpInflux.POST(body);
  Serial.printf("Influx [HTTPS] POST...  Code: %d\n", httpCode);
  httpInflux.end();
}

/** Function to submit logs to Loki */
void submitToLoki(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside, String message)
{
  String lokiClient = String("https://") + LOKI_USER + ":" + LOKI_API_KEY + "@logs-prod-us-central1.grafana.net/loki/api/v1/push";
  String body = String("{\"streams\": [{ \"stream\": { \"plant_id\": \"2021_11_13\", \"monitoring_type\": \"weather\"}, \"values\": [ [ \"") + ts + "000000000\", \"" + "temperatureInside=" + tempInside + " humidityInside=" + humInside + " temperatureOutside=" + tempOutSide + " humidityOutside=" + humOutside + " status=" + message + "\" ] ] }]}";

  /** Submit POST request via HTTP */
  httpLoki.begin(lokiClient);
  httpLoki.addHeader("Content-Type", "application/json");
  int httpCode = httpLoki.POST(body);
  Serial.printf("Loki [HTTPS] POST...  Code: %\n", httpCode);
  httpLoki.end();
}

/** Function to submit logs to Graphite */
void submitToGraphite(unsigned long ts, float tempInside, float humInside, float tempOutSide, float humOutside) {
  /** Build hosted metrics json payload */
  String body = String("[") +
    "{\"name\":\"temperatureInside\",\"interval\":" + INTERVAL + ",\"value\":" + tempInside + ",\"mtype\":\"gauge\",\"time\":" + ts + "}," +
    "{\"name\":\"humidityInside\",\"interval\":" + INTERVAL + ",\"value\":" + humInside + ",\"mtype\":\"gauge\",\"time\":" + ts + "}," +
    "{\"name\":\"temperatureOutside\",\"interval\":" + INTERVAL + ",\"value\":" + tempOutSide + ",\"mtype\":\"gauge\",\"time\":" + ts + "}," +
    "{\"name\":\"humidityOutside\",\"interval\":" + INTERVAL + ",\"value\":" + humOutside + ",\"mtype\":\"gauge\",\"time\":" + ts + "}]";

  /** Submit POST request via HTTP */
  httpGraphite.begin("https://graphite-prod-01-eu-west-0.grafana.net/graphite/metrics");
  httpGraphite.setAuthorization(GRAPHITE_USER, GRAPHITE_API_KEY);
  httpGraphite.addHeader("Content-Type", "application/json");

  int httpCode = httpGraphite.POST(body);
  Serial.printf("Graphite [HTTPS] POST...  Code: %\n", httpCode);
  httpGraphite.end();
}

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/