#include "MQTTBroker.h"
#include "PubSubClient.h"
#include "WiFiConnect.h"

void mqttBrokerInit(PubSubClient& brokerClientObj)
{
    brokerClientObj.setServer(MQTT_SERVER, MQTT_PORT);
    // brokerClientObj.setCallback(callback);
}

bool reconnectClientToBroker(PubSubClient& brokerClientObj)
{
  if (brokerClientObj.connect(MQTT_CLIENT, MQTT_USERNAME, MQTT_PASSWORD))          // check id
  {
    // Once connected, publish data if needed
    // client.publish(PUBLISH_TOPIC1, "hello world");
    // ... and resubscribe
    brokerClientObj.subscribe(SUBSCRIBE_TOPIC1);
  }
  else
  {
    Serial.print("failed, rc=");
    Serial.print(brokerClientObj.state());
  }
  return brokerClientObj.connected();
}

bool isClientConnected(PubSubClient& brokerClientObj)
{
  // Other logic to check MQTT only when WiFi connection is checked
  if (!brokerClientObj.connected())
  {
    brokerClientObj.disconnect();
    // Attempt to reconnect
    // reconnectClientToBroker(brokerClientObj);
    if(reconnectClientToBroker(brokerClientObj))
    {
      return true;
    }
    
  }
  // else
  // {
  //   // Client connected
  //   // brokerClientObj.loop();
  //   return false;
  // }
  return false;
}

/*void callbackHandler(PubSubClient &brokerObj, char *topic, uint8_t *message, uint16_t length)
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
  if (String(topic) == topic)
  {
    if (messageTemp == "Did you received??")
    {
      brokerObj.publish("esp32/dummy", "Data received!!!");
    }
  }
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
  if (String(topic) == SUBSCRIBE_TOPIC1)    //"esp32/output"
  {
    if (messageTemp == "Did you received??")
    {
      // client.publish("esp32/dummy", "Data received!!!");
    }
  }
}*/