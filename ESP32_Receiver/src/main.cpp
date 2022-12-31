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
#define INTERVAL                1000
#define BROKER_STATUS_CHECK     5000

/////////////////////////////
// Global variables
/////////////////////////////
bool isConnected = false;
uint8_t counter = 0;
unsigned long lastTimeWiFiStatusCheck = 0;
unsigned long prevBrokerReconnectTime = 0;
unsigned long prevBrokerStatusCheck = 0;
unsigned long prevTask1Time = 0;
const uint16_t msgLength = 2048;
char charData[msgLength] = {0};
uint8_t countBroker = 0;

WiFiClient espClient;
PubSubClient client(espClient);

bool reconnectClientToBroker(void)
{
  if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD))          // check id
  {
    // Once connected, publish an announcement...
    // client.publish(PUBLISH_TOPIC1, "hello world");
    
    // ... and resubscribe
    client.subscribe(SUBSCRIBE_TOPIC1);
  }

  else
  {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    // Serial.println(" try again in 5 seconds");

    // Wait 5 seconds before retrying
    // delay(5000);
  }
  return client.connected();
}

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
  if (String(topic) == "esp32/output")
  {
    // do some stuff
    /*if (messageTemp == "sendMoreData")
    {
      client.publish("esp32/dummy", "Here is more data");
    }*/
    
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
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  // mqttBrokerInit()
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






  // Some random task
  unsigned long currentTask1Time = millis();
  if(currentTask1Time - prevTask1Time > 2000)
  {
    countBroker++;
    // const char* charData = String("Hello World").c_str();
    
    client.publish(PUBLISH_TOPIC1, String(countBroker).c_str());    // third parameter was 150
    // publishtoBroker(PUBLISH_TOPIC1, countBroker);


    prevTask1Time = currentTask1Time;
  }

  // Checking broker conenction status
  unsigned long currentBrokerStatusCheck = millis();
  if(currentBrokerStatusCheck - prevBrokerStatusCheck > 1000)
  {
    if (!client.connected())
    {
      long currentBrokerConnectTime = millis();
      if (currentBrokerConnectTime - prevBrokerReconnectTime > 5000)
      {
        prevBrokerReconnectTime = currentBrokerConnectTime;

        // Attempt to reconnect
        if (reconnectClientToBroker())
        {
          prevBrokerReconnectTime = 0; // ?
        }
      }
    }
    else
    {
      // Client connected
      client.loop();
    }
    prevBrokerStatusCheck = currentBrokerStatusCheck;
  }

} // end loop()


