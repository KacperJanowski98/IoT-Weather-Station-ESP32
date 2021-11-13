/**
 * ***************************************************************************************************
 * @file config.h
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * ***************************************************************************************************
 */

/* Variables for ThingSpeak */
#define CHANNEL_ID 1540710
#define CHANNEL_API_KEY "C3MWNJUOTW5095ZC"

/* Variables for WiFI */
#define WIFI_TIMEOUT_MS 20000
#define WIFI_SSID "AndroidAP_note8"
#define WIFI_PASSWORD "sensor123"

/* Variables for InfluxDB */
#define INFLUX_HOST "https://eu-central-1-1.aws.cloud2.influxdata.com/" // Influx host (e.g. eu-central-1-1.aws.cloud2.influxdata.com)
#define INFLUX_ORG_ID "5abdc36e1de4a515" // Org id
#define INFLUX_TOKEN "6f-ur6WueGwzxoMHz0dYm77v0CyMiR3mG1bFEGZMtVvOjk9gJw86t33OtiCSFj5qbAPi3aXMY9zz_efhvSZq1Q==" // Influx token
#define INFLUX_BUCKET "Weather_station" // Influx bucket that we set up for this host

#define LOKI_USER "124624" // Hosted Loki user
#define LOKI_API_KEY "eyJrIjoiZDA5MTNjN2Q2YmU5MjE1Mzg0MWM4ZDA4MjIzNTY4ODU3MDQ5M2ZlZiIsIm4iOiJXZWF0aGVyX3N0YXRpb24iLCJpZCI6NTY0MjE5fQ==" // Hosted Loki API key

// How to get the Root CA cert:
// https://techtutorialsx.com/2017/11/18/esp32-arduino-https-get-request/

#define ROOT_CA "-----BEGIN CERTIFICATE-----" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexampleexampleexampleexampleexampleexampleexampleexamplee" \
"exampleexample" \
"-----END CERTIFICATE-----"

/********************************** (C) COPYRIGHT Kacper Janowski 2021 *********** END OF FILE ******/
