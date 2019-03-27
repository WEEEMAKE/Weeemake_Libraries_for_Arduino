
#ifndef _WeMP3_H
#define _WeMP3_H

#include "WeOneWire.h"

class WeMP3
{
public:

  WeMP3(uint8_t port=0);
  void reset(uint8_t port=0);
  
  void appointMusic(uint16_t num); 
  void appointVolume(uint8_t num); //0-30
  void nextMusic(void);
  void pause(void);
  void play(void);
  void appointDevice(uint8_t devtype);  //2-TF; 4-FLASH
  uint8_t isOver(void);
  void prevMusic(void);

  
private:
	WeOneWire _WeMP3;
    volatile uint8_t  _data1;
};

#endif

