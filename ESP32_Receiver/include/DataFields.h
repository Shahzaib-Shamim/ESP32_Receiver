#ifndef __DATA_FIELDS_H__
#define __DATA_FIELDS_H__

#include <Arduino.h>

// ------------------------------------------------
// Data types
// ------------------------------------------------
typedef struct
{
    char        cellID;
    uint16_t    cellVoltage;
    int16_t     cellTemp;
    int16_t     cellSOC;
} __attribute__((packed, aligned(1))) cellData_t;

typedef struct
{
    char        slaveID;
    int16_t     slaveCPUTemp;
    cellData_t  cells[4];
} __attribute__((packed, aligned(1))) slaveData_t;

typedef struct
{
    // trigger 1
    char        packetType;
    char        batterySerialNo[20];
    char        batteryID[15];
    int16_t     batteryType;
    char        batteryStatus;
    char        chargerStatus;
    float       minVolt;
    float       maxVolt;
    float       packVolt;
    float       packMeasureVolt;
    float       measuredSOC;
    float       minTemp;
    float       maxTemp;
    // trigger 2
    float       batteryCurrent;
    int16_t     batterySOC;
    int16_t     batterySOH;
    float       currentShunt;
    int16_t     socShunt;
    int16_t     error;
    int16_t     error2;
    char        balancingError;
    int16_t     balancingErrorCells[10];
    int16_t     balancingErrorPacks[5];
    // trigger 3
    float       rectifierPowerIn;
    float       rectifierPowerOut;
    float       rectifierCurrentIn;
    float       rectifierCurrentOut;
    float       rectifierVoltagePhA;
    float       rectifierVoltagePhB;
    float       rectifierVoltagePhC;
    float       rectifierVoltageOut;
    float       rectifierAmbientTemeperature;
    char        rectifierError1;
    char        rectifierError2;
    uint16_t    inverterCurrent;
    uint16_t    inverterVoltage;
    uint16_t    inverterError;
    uint16_t    inverterTempAmbient;
    uint16_t    inverterTempHeatSink;
    float       bCycle;
    double      partialDischargeAH; // 64 bit double precision
    // trigger 4
    uint16_t    restoredErrorBMS1;
    uint16_t    restoredErrorBMS2;
    uint16_t    restoredErrorInverter;
    uint16_t    restoredErrorRectifier1;
    uint16_t    restoredErrorRectifier2;
    float       lastDCCurrentErrorValue;
} __attribute__((packed, aligned(1))) Packet1_t;

typedef struct
{
    // trigger 25
    char packetType;
    char batterySerialNo[20];
    char batteryID[15];
    // trigger 26 - 53
    slaveData_t slaves[27];
} __attribute__((packed, aligned(1))) Packet2_t;



// ------------------------------------------------
// Global functions
// ------------------------------------------------
/**
 * @brief Global function to update struct members.
 * 
 */
void updatePacket1(Packet1_t *, uint8_t *);

void updatePacket2(Packet2_t *, uint8_t *);

/**
 * @brief Calculate checksum by adding all the bytes of buffer.
 * 
 * @return true is equals else return false.
 */
bool calculateChecksum(uint8_t *buffer, uint16_t packetSize, uint16_t index);


#endif /* __DATA_FIELDS_H__ */