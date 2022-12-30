#ifndef __MQTTBROKER_H__
#define __MQTTBROKER_H__

#include <Arduino.h>
#include <PubSubClient.h>
#include "NetworkCredentials.h"

// ------------------------------------------------
// MACROS
// ------------------------------------------------
#define MQTT_SERVER     "192.168.18.100"    // change this    
#define MQTT_USERNAME   "pibroker"          // change this
#define MQTT_PASSWORD   "fmifmifmi"         // change this
#define MQTT_CLIENT     "ESP32Client"
#define MQTT_PORT       1883

#endif /* __MQTTBROKER_H__ */