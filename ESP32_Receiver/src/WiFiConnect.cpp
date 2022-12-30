#include "WiFiConnect.h"


//old working
/*void connectToWiFi(void)
{
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK_1, WIFI_PASSWORD_1);

  unsigned long startAttemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed");
    static uint8_t connectWiFiFailedCount = 0;
    if(++connectWiFiFailedCount == 6)
    {
      connectWiFiFailedCount = 0;
      ESP.restart();    // added
    }    
  }
  
  else
  {
    Serial.print("Connected to ");
    Serial.println(WiFi.localIP());
  }
}*/

void connectToWiFi(void)
{
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long connectAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - connectAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  // if conenction failed
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed");
    static uint8_t connectWiFiFailedCount = 0;
    if(++connectWiFiFailedCount == 6)
    {
      connectWiFiFailedCount = 0;
      ESP.restart();    // restart ESP after 120sec if not connected on setup
    }
  }
  else
  {
    Serial.print("Connected to ");
    Serial.println(WiFi.localIP());
  }
}