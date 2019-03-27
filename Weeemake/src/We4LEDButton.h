
#ifndef _We4LEDButton_H
#define _We4LEDButton_H

#include "WePort.h"

class We4LEDButton
{
public:

  We4LEDButton(uint8_t port=0);
  void reset(uint8_t port=0);
  void openLED(uint8_t value);
  void closeLED(uint8_t value);
  void setLed(uint8_t index, bool isOn);
  uint8_t readKey(void);
  uint8_t readValue(void);
  
private:
	WeOneWire _We4LEDButton;
    volatile uint8_t  _Sensor1;
};

#endif

