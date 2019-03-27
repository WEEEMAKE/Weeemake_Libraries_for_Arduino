
#ifndef WeOLED_H
#define WeOLED_H

#include "WePort.h"


class WeOLED
{
public:

  WeOLED(uint8_t port=0);
  void reset(uint8_t port=0);
  
  void clearScreen(void);
  void setSize(uint8_t size);
  void fullScreen(void);
  void setdigits(uint8_t mun);
  void show8dot(uint8_t X_position,uint8_t Y_position,uint8_t buffer);
  void showString(uint8_t X_position, uint8_t Y_position, char *str);
  void sendNum(uint8_t X_position, uint8_t Y_position, uint8_t Num);
  void showNum(uint8_t X_position, uint8_t Y_position, double Num);
  void showChineseCharacters(uint8_t X_position,uint8_t Y_position,uint8_t (*zh_str)[16], uint8_t no);
  void showBMP(uint8_t X_position,uint8_t Y_position,uint8_t p[]);

private:
	WeOneWire _WeOLED;
	uint8_t charSize=8;
	uint8_t digits_num=2;
};

#endif

