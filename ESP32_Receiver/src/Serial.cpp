#include "Serial.h"

// ------------------------------------------------
// Global variables
// ------------------------------------------------
uint8_t readData[1100] = {0}; // receive buffer
uint16_t count = 0;
rxState_e rxState = RX_HEADER_LSB;

Packet1_t packet1;
Packet2_t packet2;

void processSerial(void)
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
            // memset(&packet1, 0, sizeof(packet1));
            // memset(&packet2, 0, sizeof(packet2));
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
                else
                {
                    Serial.println("Invalid Packet1");
                }
            }

            if (dataLength == sizeof(packet2))
            {
                if (calculateChecksum(readData, sizeof(packet2), count))
                {
                    updatePacket2(&packet2, readData);
                }
                else
                {
                    Serial.println("Invalid Packet2");
                }
            }
            
            // else
            // {
            //     Serial.println("Invalid packets!");
            // }

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
}