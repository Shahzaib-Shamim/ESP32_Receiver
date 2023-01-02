#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <Arduino.h>
#include "DataFields.h"

// ------------------------------------------------
// Data types
// ------------------------------------------------
typedef enum
{
  RX_HEADER_LSB,
  RX_HEADER_MSB,
  RX_DATA,
  RX_FOOTER_LSB,
  RX_FOOTER_MSB,
  RX_DATA_GET
} rxState_e;

extern Packet1_t packet1;
extern Packet2_t packet2;

// ------------------------------------------------
// Global functions
// ------------------------------------------------
void processSerial(void);

#endif /* __SERIAL_H__ */