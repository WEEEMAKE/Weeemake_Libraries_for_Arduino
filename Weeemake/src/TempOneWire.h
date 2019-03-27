
#ifndef TempOneWire_H
#define TempOneWire_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "WeConfig.h"


class TempOneWire
{
public:
	
  TempOneWire(void);
  TempOneWire(uint8_t pin);
  bool readIO(void);
  void reset(uint8_t pin);
  uint8_t reset(void);
  void select(const uint8_t rom[8]);
  void skip(void);
  void write(uint8_t v, uint8_t power = 0);
  void write_bytes(const uint8_t *buf, uint16_t count, bool power = 0);
  uint8_t read(void);
  void read_bytes(uint8_t *buf, uint16_t count);
  void write_bit(uint8_t v);
  uint8_t read_bit(void);
  void depower(void);
  void reset_search(void);
  void target_search(uint8_t family_code);
  uint8_t search(uint8_t *newAddr);
  
  
 private:
	 WeIO_REG_TYPE   bitmask;
  	 volatile WeIO_REG_TYPE *baseReg;

 	 uint8_t ROM_NO[8];
   	 uint8_t LastDiscrepancy;
 	 uint8_t LastFamilyDiscrepancy;
  	 uint8_t LastDeviceFlag;

};

#endif

