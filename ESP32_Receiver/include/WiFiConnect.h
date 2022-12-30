#ifndef __WIFICONNECT_H__
#define __WIFICONNECT_H__

#include <Arduino.h>
#include <NetworkCredentials.h>
#include "WiFi.h"

// ------------------------------------------------
// MACROS
// ------------------------------------------------
#define WIFI_TIMEOUT_MS         10000
#define WIFI_STATUS_CHECK       5000

// ------------------------------------------------
// Global functions
// ------------------------------------------------
void connectToWiFi(void);


#endif /* __WIFICONNECT_H__ */