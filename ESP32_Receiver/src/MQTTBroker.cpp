#include "MQTTBroker.h"
#include "PubSubClient.h"
#include "WiFiConnect.h"

// unsigned long prevBrokerReconnectTime = 0;

// WiFiClient espClient;
// PubSubClient client(espClient);

// void mqttBrokerInit(void)
// {
//     client.setServer(MQTT_SERVER, MQTT_PORT);
//     client.setCallback(callback);
// }

/*bool reconnectClientToBroker(void)
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
}*/

/*void callback(char *topic, uint8_t *message, uint16_t length)
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
    
//   }
// }*/

/*void publishtoBroker(char* topic, uint8_t payload)
{
    client.publish(topic, String(payload));    // third parameter was 150
}

void isClientConnected(void)
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
}*/