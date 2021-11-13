/**
 * ***************************************************************************************************
 * @file config.h
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * ***************************************************************************************************
 */

#define ID "Weather" // Add unique name for this sensor
#define INTERVAL 60  // Add interval (e.g. 1 min)

/* Variables for ThingSpeak */
#define CHANNEL_ID 1540710
#define CHANNEL_API_KEY "C3MWNJUOTW5095ZC"

/* Variables for WiFI */
#define WIFI_TIMEOUT_MS 20000
#define WIFI_SSID "AndroidAP_note8"
#define WIFI_PASSWORD "sensor123"

/* Variables for InfluxDB */
#define INFLUX_HOST "https://eu-central-1-1.aws.cloud2.influxdata.com" // Influx host (e.g. eu-central-1-1.aws.cloud2.influxdata.com)
#define INFLUX_ORG_ID "5abdc36e1de4a515" // Org id
#define INFLUX_TOKEN "6f-ur6WueGwzxoMHz0dYm77v0CyMiR3mG1bFEGZMtVvOjk9gJw86t33OtiCSFj5qbAPi3aXMY9zz_efhvSZq1Q==" // Influx token
#define INFLUX_BUCKET "Weather_station" // Influx bucket that we set up for this host

#define LOKI_USER "124624" // Hosted Loki user
#define LOKI_API_KEY "eyJrIjoiZDA5MTNjN2Q2YmU5MjE1Mzg0MWM4ZDA4MjIzNTY4ODU3MDQ5M2ZlZiIsIm4iOiJXZWF0aGVyX3N0YXRpb24iLCJpZCI6NTY0MjE5fQ==" // Hosted Loki API key

#define GRAPHITE_USER "251307" // Graphite user
#define GRAPHITE_API_KEY "eyJrIjoiNzI2ZDBjNjYxNzBhOTZkZjFjYzMwMmMzMGRjNTBjNzk0MGM5Njc4NyIsIm4iOiJXZWF0aGVyX3N0YXRpb25fR3JhcGhpdGUiLCJpZCI6NTY0MjE5fQ==" // Graphite API Key

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/
