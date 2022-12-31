#include "DataFields.h"

void updatePacket1(Packet1_t *obj, uint8_t *buffer)
{
    memcpy(obj, &buffer[4], sizeof(*obj));

    /*Serial.print((uint8_t)obj->packetType);     Serial.print(",");
    Serial.print(obj->batterySerialNo);         Serial.print(",");
    Serial.print(obj->batteryID);               Serial.print(",");
    Serial.print(obj->batteryType);             Serial.print(",");
    Serial.print((uint8_t)obj->batteryStatus);  Serial.print(",");
    Serial.print((uint8_t)obj->chargerStatus);  Serial.print(",");
    Serial.print(obj->minVolt);                 Serial.print(",");
    Serial.print(obj->maxVolt);                 Serial.print(",");
    Serial.print(obj->packVolt);                Serial.print(",");
    Serial.print(obj->packMeasureVolt);         Serial.print(",");
    Serial.print(obj->measuredSOC);             Serial.print(",");
    Serial.print(obj->minTemp);                 Serial.print(",");
    Serial.print(obj->maxTemp);                 Serial.print(",");
    Serial.print(obj->batteryCurrent);          Serial.print(",");
    Serial.print(obj->batterySOC);              Serial.print(",");
    Serial.print(obj->batterySOH);              Serial.print(",");
    Serial.print(obj->currentShunt);            Serial.print(",");
    Serial.print(obj->socShunt);                Serial.print(",");
    Serial.print(obj->error);                   Serial.print(",");
    Serial.print(obj->error2);                  Serial.print(",");
    Serial.print((uint8_t)obj->balancingError); Serial.print(",");
    for (uint8_t i = 0; i < 10; i++)
    {
        Serial.print(obj->balancingErrorCells[i]);
        Serial.print(",");
    }
    for (uint8_t i = 0; i < 5; i++)
    {
        Serial.print(obj->balancingErrorPacks[i]);
        Serial.print(",");
    }
    Serial.print(obj->rectifierPowerIn);                Serial.print(",");
    Serial.print(obj->rectifierPowerOut);               Serial.print(",");
    Serial.print(obj->rectifierCurrentIn);              Serial.print(",");
    Serial.print(obj->rectifierCurrentOut);             Serial.print(",");
    Serial.print(obj->rectifierVoltagePhA);             Serial.print(",");
    Serial.print(obj->rectifierVoltagePhB);             Serial.print(",");
    Serial.print(obj->rectifierVoltagePhC);             Serial.print(",");
    Serial.print(obj->rectifierVoltageOut);             Serial.print(",");
    Serial.print(obj->rectifierAmbientTemeperature);    Serial.print(",");
    Serial.print((uint8_t)obj->rectifierError1);        Serial.print(",");
    Serial.print((uint8_t)obj->rectifierError2);        Serial.print(",");
    Serial.print(obj->inverterCurrent);                 Serial.print(",");
    Serial.print(obj->inverterVoltage);                 Serial.print(",");
    Serial.print(obj->inverterError);                   Serial.print(",");
    Serial.print(obj->inverterTempAmbient);             Serial.print(",");
    Serial.print(obj->inverterTempHeatSink);            Serial.print(",");
    Serial.print(obj->bCycle);                          Serial.print(",");
    Serial.print(obj->partialDischargeAH);              Serial.print(",");
    Serial.print(obj->restoredErrorBMS1);               Serial.print(",");
    Serial.print(obj->restoredErrorBMS2);               Serial.print(",");
    Serial.print(obj->restoredErrorInverter);           Serial.print(",");
    Serial.print(obj->restoredErrorRectifier1);         Serial.print(",");
    Serial.print(obj->restoredErrorRectifier2);         Serial.print(",");
    Serial.print(obj->lastDCCurrentErrorValue);
    Serial.println("\n");*/

    Serial.println("Packet1 received and processed!");
}

void updatePacket2(Packet2_t *obj, uint8_t *buffer)
{
    memcpy(obj, &buffer[4], sizeof(*obj));

    /*Serial.print((uint8_t)obj->packetType); Serial.print(",");
    Serial.print(obj->batteryID);           Serial.print(",");
    Serial.print(obj->batterySerialNo);     Serial.print(",");
    
    // iterate all 27 slaves
    for (uint8_t i = 0; i < 27; i++)     // 27 slaves
    {
        Serial.print("Slave# " + String(i + 1)); Serial.print("->");
        Serial.print((uint8_t)obj->slaves[i].slaveID);        Serial.print(",");
        Serial.print(obj->slaves[i].slaveCPUTemp);            Serial.print(",\n");
        
        // iterate all 4 cells in each slave
        for(uint8_t j = 0; j < 4; j++)
        {
            Serial.print("Cell# " + String(j + 1)); Serial.print("->");
            Serial.print((uint8_t)obj->slaves[i].cells[j].cellID);  Serial.print(",");
            Serial.print(obj->slaves[i].cells[j].cellVoltage);      Serial.print(",");
            Serial.print(obj->slaves[i].cells[j].cellTemp);         Serial.print(",");
            Serial.print(obj->slaves[i].cells[j].cellSOC);          Serial.print("\n");
        }        
        Serial.print("\n");
    }

    // Serial.print((uint8_t)obj->packetType);
    // Serial.print(",");
    // Serial.print(obj->batteryID);
    // Serial.print(",");
    // Serial.print(obj->batterySerialNo);
    // Serial.print(",");
    // Serial.print((uint8_t)obj->slaves[0].slaveID);
    // Serial.print(",");
    // Serial.print(obj->slaves[0]->slaveCPUTemp);
    // Serial.print(",");
    // Serial.print((uint8_t)obj->slaves[0].cells[0].cellID);
    // Serial.print(",");
    // Serial.print(obj->slaves[0]->cells[0].cellVoltage);
    // Serial.print(",");
    // Serial.print(obj->slaves[0]->cells[0].cellTemp);
    // Serial.print(",");
    // Serial.print(obj->slaves[0]->cells[0].cellSOC);
    // Serial.print("\n");
    // Serial.print("\n");*/

    Serial.println("Packet2 received and processed!");
}

bool calculateChecksum(uint8_t *buffer, uint16_t packetSize, uint16_t index)
{
    uint32_t checksumPacketRx = 0;     // received with data buffer
    uint8_t *pRxChecksumPacket;

    pRxChecksumPacket = (uint8_t *)&checksumPacketRx;
    *pRxChecksumPacket++ = buffer[index - 6];
    *pRxChecksumPacket++ = buffer[index - 5];
    *pRxChecksumPacket++ = buffer[index - 4];
    *pRxChecksumPacket   = buffer[index - 3];

    // find from reecived data bytes
    uint32_t sumPacket = 0;
    uint8_t *pPacket = (uint8_t *)&buffer[4];    // 1st data byte is at index-3
    for (uint16_t i = 0; i < packetSize; i++)
    {
        sumPacket += *(pPacket);
        pPacket++;
    }
    
    if (sumPacket == checksumPacketRx)
    {
        return true;
    }
    else
    {
        return false;
    }
}