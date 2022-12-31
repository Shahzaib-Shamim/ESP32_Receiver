#ifndef __MQTTBROKER_H__
#define __MQTTBROKER_H__

#include <Arduino.h>
#include <PubSubClient.h>
#include "NetworkCredentials.h"

// ------------------------------------------------
// MACROS
// ------------------------------------------------
// -- Office broker ----------
/*#define MQTT_SERVER     "192.168.18.100"
#define MQTT_USERNAME   "pibroker"
#define MQTT_PASSWORD   "fmifmifmi"
#define MQTT_CLIENT     "ESP32Client"
#define MQTT_PORT       1883*/
// -- Home broker ----------
#define MQTT_SERVER     "192.168.0.103"         // const char* mqtt_server = "192.168.0.103"
#define MQTT_USERNAME   "shahzaibshamim"
#define MQTT_PASSWORD   "Shazb_74292"
#define MQTT_CLIENT     "ESP32Client"
#define MQTT_PORT       1883

#define PUBLISH_TOPIC1          "esp32/dummy"
#define SUBSCRIBE_TOPIC1        "esp32/output"


// ------------------------------------------------
// Global functions
// ------------------------------------------------
/**
 * @brief Initialize MQTT broker
*/
void mqttBrokerInit(void);

/**
 * @brief Reconnect client to broker
*/
bool reconnectClientToBroker(void);

/**
 * Callback to publish a message or when message is received
*/
void callback(char *, uint8_t *, uint16_t);

/**
 * @brief Publish message to broker
*/
void publishtoBroker(char *, uint8_t);

/**
 * @brief Checks broker connection
*/
void isClientConnected(void);

#endif /* __MQTTBROKER_H__ */