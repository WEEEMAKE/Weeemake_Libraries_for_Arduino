#ifndef OLED_H
#define OLED_H
#include "IIC.h"

class OLED:public IIC
{
public:
	OLED(uint8_t _scl_pin,uint8_t _sda_pin):IIC(_scl_pin,_sda_pin)
	{
		init();
		screenClear();
	};
	void writeCommand(uint8_t cmdByte);
	void writeData(uint8_t dataByte);
	void init(void);
	void screenClear(void);
	void showString(uint8_t row,uint8_t col,uint8_t (*str)[16],uint8_t stringSize);
	void showCharacterOfChinese(uint8_t row,uint8_t col,uint8_t (*characterChinese)[32],uint8_t characterSize);
	void showImage(uint8_t (*oledImageTable)[128]);
	void showDot(uint8_t x, uint8_t y);
};

#endif