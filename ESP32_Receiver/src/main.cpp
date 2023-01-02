/**
 * Receives data packet via UART. (29-12-2022, from Home)
 */

#include <Arduino.h>
#include "main.h"
#include "DataFields.h"
#include "Serial.h"
#include "WiFiConnect.h"
#include "MQTTBroker.h"
#include <ArduinoJson.h>
#include <JSON.h>

// -----------------------------------
// MACROS
// -----------------------------------
#define INTERVAL                1000
#define BROKER_STATUS_CHECK     5000

// ----------------------------------
// Global variables
// ----------------------------------
bool isWiFiConnected = false;
bool isBrokerConnected = false;
uint8_t counter = 0;
unsigned long lastTimeWiFiStatusCheck = 0;
unsigned long prevBrokerStatusCheck = 0;
unsigned long prevTask1Time = 0;
const uint16_t msgLength = 2048;
char charData[msgLength] = {0};
uint8_t countBroker = 0;
bool packState = false;


WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, uint8_t *message, uint16_t length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == SUBSCRIBE_TOPIC1)
  {
    // if (messageTemp == "sendMoreData")
    // {
    //   // client.publish("esp32/dummy", "Data received!!!");
    // }
    Serial.println("Data received!!!");
    client.publish("esp32/dummy", "Data received!!!");
  }
}

void setup()
{
  // Debug Serial
  Serial.begin(115200);

  // Hardware Serial for Receiver
  Serial2.begin(115200, SERIAL_8N1, RX2, TX2);

  Serial.println("Start...");

  // WiFi setup
  connectToWiFi();

  // MQTT broker setup
  mqttBrokerInit(client);
  client.setCallback(callback);

  memset(&packet1, 0, sizeof(packet1));
  memset(&packet2, 0, sizeof(packet2));

  delay(2000);
}

void loop()
{
  // Waiting for serial data from MASTER
  if (Serial2.available())
  {
    processSerial();
  }

  // Checking WiFi status
  unsigned long timeWiFiStatusCheck = millis();
  if ((timeWiFiStatusCheck - lastTimeWiFiStatusCheck) >= WIFI_STATUS_CHECK)
  {
    static uint8_t lostWiFiCount = 0;
    if (WiFi.status() == WL_CONNECTED && !isWiFiConnected)
    {
      Serial.println("Connected");
      isWiFiConnected = true;
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      ++lostWiFiCount;
      Serial.println("Lost WiFi " + String(lostWiFiCount) + ", reconnecting...");
      connectToWiFi();
      // isClientConnected(client);  // added to test new mqtt code
      reconnectClientToBroker(client);
      Serial.println("Broker connection remade");
      isWiFiConnected = false;
    }
    lastTimeWiFiStatusCheck = timeWiFiStatusCheck;
  }

  // Some random task to send data on MQTT
  unsigned long currentTask1Time = millis();
  if(currentTask1Time - prevTask1Time > 1000)
  {
    if(isBrokerConnected == true && isWiFiConnected == true)
    {
      // countBroker++;
      // const char* charData = String("Hello World").c_str();
      // client.publish(PUBLISH_TOPIC1, String(countBroker).c_str());    // third parameter was 150
      // client.publish(PUBLISH_TOPIC1, String(packet1.batterySerialNo).c_str());

      if (packet1Flag == true && packet2Flag == false)
      {
        createJSONpacket(client, 1);
      }
      else if (packet1Flag == false && packet2Flag == true)
      {
        createJSONpacket(client, 2);
      }
    }
    prevTask1Time = currentTask1Time;
  }

  unsigned long currentBrokerStatusCheck = millis();
  if(currentBrokerStatusCheck - prevBrokerStatusCheck > MQTT_RECONNECT_TIMEOUT)
  {
    if(isClientConnected(client))
    {
      Serial.println("Broker reconnected!");
      isBrokerConnected = false;
    }
    else
    {
      isBrokerConnected = true;
      client.loop();
    }
    prevBrokerStatusCheck = currentBrokerStatusCheck;
  }

} // end loop()


