#ifndef __JSON_H__
#define __JSON_H__

#include <Arduino.h>
#include <PubSubClient.h>

// -----------------------------
// MACROS
// -----------------------------
#define MSG_LENGTH          5000

// -----------------------------
// Datatypes
// -----------------------------

// -----------------------------
// Global functions
// -----------------------------
/**
 * @brief Make JSON for received packet 1 and 2.
 * 
 */
void createJSONpacket(PubSubClient& brokerObj, uint8_t packetNumber);


#endif /* __JSON_H__ */