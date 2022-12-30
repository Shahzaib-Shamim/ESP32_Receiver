/**
 * Receives data packet via UART. (29-12-2022, from Home)
 */

#include <Arduino.h>
#include "main.h"
#include "DataFields.h"
#include "Serial.h"
#include "WiFiConnect.h"
#include "MQTTBroker.h"

/////////////////////////////
// MACROS
/////////////////////////////
// #define WIFI_STATUS_CHECK_INTERVAL_MS    5000    // old
#define INTERVAL                1000
#define BROKER_STATUS_CHECK     5000

/////////////////////////////
// Global variables
/////////////////////////////
// unsigned long prevTimeWiFiStatusCheck = 0; //old working
// bool isWiFiConnected = false;              // old working
bool isConnected = false;
uint8_t counter = 0;
unsigned long lastTimeWiFiStatusCheck = 0;
unsigned long prevBrokerReconnectTime = 0;
unsigned long prevTask1Millis = 0;


// ------------------------------------------------
// Data types
// ------------------------------------------------
// typedef enum
// {
//   PACKET1 = 0,
//   PACKET2
// } PacketNumber_e;

// Packet1_t packet1;
// Packet2_t packet2;

// typedef enum
// {
//   RX_HEADER_LSB,
//   RX_HEADER_MSB,
//   RX_DATA,
//   RX_FOOTER_LSB,
//   RX_FOOTER_MSB,
//   RX_DATA_GET
// } rxState_e;

// rxState_e rxState = RX_HEADER_LSB;

// uint8_t readData[1100] = {0}; // receive buffer
// uint8_t count = 0;
// uint32_t checksumPacket1Rx = 0;
// uint8_t *pRxChecksumPacket1;
// uint32_t checksumPacket2Rx = 0;
// uint8_t *pRxChecksumPacket2;

// Functions
/*void processSerial(void)
{
  uint8_t data = Serial2.read();
  readData[count++] = data;

  switch (rxState)
  {
  case RX_HEADER_LSB:
    if (data == '*')
    {
      rxState = RX_HEADER_MSB;
      // count = 1;    //0
    }
    break;

  case RX_HEADER_MSB:
    if (data == '#')
    {
      memset(&packet1, 0, sizeof(packet1));
      rxState = RX_DATA;
    }
    else
    {
      rxState = RX_HEADER_LSB;
      count = 0;
    }
    break;

  case RX_DATA:
    if (data == '@')
    {
      rxState = RX_FOOTER_LSB;
    }
    break;

  case RX_FOOTER_LSB:
    if (data == '$')
    {
      readData[count] = '\0';

      // Checking which data packet is received
      uint16_t dataLength = (readData[3] << 8) | readData[2];

      if (dataLength == sizeof(packet1))
      {
        if (calculateChecksum(readData, sizeof(packet1), count))
        {
          updatePacket1(&packet1, readData);
        }
      }

      else if (dataLength == sizeof(packet2))
      {
        if (calculateChecksum(readData, sizeof(packet1), count))
        {
          updatePacket1(&packet1, readData);
        }
      }

      else
      {
        Serial.println("Invalid data");
      }

      memset(readData, 0, sizeof(readData));
      count = 0;
      rxState = RX_HEADER_LSB;
    }
    // else
    // {
    //   rxState = RX_DATA;
    // }
    break;
  } // end switch(rxState)
}*/

void setup()
{
  // Debug Serial
  Serial.begin(115200);

  // Hardware Serial for Receiver
  Serial2.begin(115200, SERIAL_8N1, RX2, TX2);

  Serial.println("Start...");

  connectToWiFi();
}

void loop()
{
  if (Serial2.available())
  {
    processSerial();
  }

  // Checks WiFi connection after every 5000ms (old working code)
  /*unsigned long timeWiFiStatusCheck = millis();
  if ((timeWiFiStatusCheck - prevTimeWiFiStatusCheck) >= WIFI_STATUS_CHECK_INTERVAL_MS)
  {
    Serial.println("------------------WiFi status checked!------------------");
    if (WiFi.status() == WL_CONNECTED && !isWiFiConnected)
    {
      Serial.println("Still connected!");
      isWiFiConnected = true;
    }

    if (WiFi.status() != WL_CONNECTED)
    {
      connectToWiFi();
      isWiFiConnected = false;
    }
    prevTimeWiFiStatusCheck = timeWiFiStatusCheck;
  }*/

  // unsigned long task1Millis = millis();
  // if ((task1Millis - prevTask1Millis) >= INTERVAL)
  // {
  //   Serial.println("Hello World!  " + String(counter++));
  //   prevTask1Millis = task1Millis;
  // }

  // checking WiFi status
  unsigned long timeWiFiStatusCheck = millis();
  if ((timeWiFiStatusCheck - lastTimeWiFiStatusCheck) >= WIFI_STATUS_CHECK)
  {
    static uint8_t lostWiFiCount = 0;
    if (WiFi.status() == WL_CONNECTED && !isConnected)
    {
      Serial.println("Connected");
      isConnected = true;
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      ++lostWiFiCount;
      Serial.println("Lost WiFi " + String(lostWiFiCount) + ", reconnecting...");
      connectToWiFi();
      isConnected = false;
    }
    lastTimeWiFiStatusCheck = timeWiFiStatusCheck;
  }
}