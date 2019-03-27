
#ifndef _We7SegmentDisplay_H
#define _We7SegmentDisplay_H

#include "WePort.h"

class We7SegmentDisplay
{
public:

  We7SegmentDisplay(uint8_t port=0);
  void reset(uint8_t port=0);
  void showNumber(float value);
  void showChar(uint8_t Addr, uint8_t Data);
private:
  void sendNumber(void);
private:
	WeOneWire _We7SegmentDisplay;
    volatile uint8_t  _number1;
	volatile uint8_t  _number2;
	volatile uint8_t  _number3;
	volatile uint8_t  _number4;
	float last_number;
  bool resetFlag;
};

#endif

