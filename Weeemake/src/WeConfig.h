#ifndef WeConfig_H
#define WeConfig_H

#include <utility/Servo.h>
#include <utility/Wire.h>
#include <utility/EEPROM.h>
#include <utility/SoftwareSerial.h>
#include <utility/SPI.h>

#define WE_PORT_DEFINED

#if defined(__AVR__)
#define WePIN_TO_BASEREG(pin)               ( portInputRegister (digitalPinToPort (pin) ) )
#define WePIN_TO_BITMASK(pin)               ( digitalPinToBitMask (pin) )
#define WeIO_REG_TYPE                       uint8_t
#define WeIO_REG_ASM                        asm ("r30")
#define WeDIRECT_READ(base, mask)           ( ( (*(base) ) & (mask) ) ? 1 : 0)
#define WeDIRECT_MODE_INPUT(base, mask)     ( (*( (base) + 1) ) &= ~(mask) ), ( (*( (base) + 2) ) |= (mask) ) // INPUT_PULLUP
#define WeDIRECT_MODE_OUTPUT(base, mask)    ( (*( (base) + 1) ) |= (mask) )
#define WeDIRECT_WRITE_LOW(base, mask)      ( (*( (base) + 2) ) &= ~(mask) )
#define WeDIRECT_WRITE_HIGH(base, mask)     ( (*( (base) + 2) ) |= (mask) )
#endif // __AVR__

#endif // MeConfig_H

