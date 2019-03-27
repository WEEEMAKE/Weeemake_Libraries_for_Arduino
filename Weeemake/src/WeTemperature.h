
#ifndef WeTemperature_H
#define WeTemperature_H

#include "TempOneWire.h"
#include "WePort.h"

/* DS18B20 commands */
#define STARTCONVO       0x44    // Tells device to take a temperature reading and put it on the scratchpad
#define COPYSCRATCH      0x48    // Copy EEPROM
#define READSCRATCH      0xBE    // Read EEPROM
#define WRITESCRATCH     0x4E    // Write to EEPROM
#define RECALLSCRATCH    0xB8    // Reload from last known
#define READPOWERSUPPLY  0xB4    // Determine if device needs parasite power
#define ALARMSEARCH      0xEC    // Query bus for devices with an alarm condition



class WeTemperature
{
public:

  WeTemperature(uint8_t port=0);
  void reset(uint8_t port=0);
  float temperature(void);
  private:
	  TempOneWire _ts;
	  volatile uint8_t	_DataPin;

};

#endif

