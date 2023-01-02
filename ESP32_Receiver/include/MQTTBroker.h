#ifndef __MQTTBROKER_H__
#define __MQTTBROKER_H__

#include <Arduino.h>
#include <PubSubClient.h>
#include "NetworkCredentials.h"

// ------------------------------------------------
// MACROS
// ------------------------------------------------
// -- Office broker ----------
#define MQTT_SERVER     "192.168.18.100"
#define MQTT_USERNAME   "pibroker"
#define MQTT_PASSWORD   "fmifmifmi"
// -- Home broker ----------
// #define MQTT_SERVER     "192.168.0.103"     // const char* mqtt_server = "192.168.0.103"
// #define MQTT_USERNAME   "shahzaibshamim"
// #define MQTT_PASSWORD   "Shazb_74292"

#define MQTT_CLIENT             "ESP32_Client"
#define MQTT_PORT               1883

#define PUBLISH_TOPIC1          "esp32/dummy"
#define SUBSCRIBE_TOPIC1        "esp32/output"

#define MQTT_RECONNECT_TIMEOUT  1000


// ------------------------------------------------
// Global functions
// ------------------------------------------------
/**
 * @brief Initialize MQTT broker
*/
void mqttBrokerInit(PubSubClient& brokerClientObj);

/**
 * @brief Reconnect client to broker
*/
bool reconnectClientToBroker(PubSubClient& brokerClientObj);

/**
 * @brief Checks broker connection
*/
bool isClientConnected(PubSubClient& brokerClientObj);

/**
 * Callback to publish a message or when message is received
*/
// void callback(char *, uint8_t *, uint16_t);

#endif /* __MQTTBROKER_H__ */