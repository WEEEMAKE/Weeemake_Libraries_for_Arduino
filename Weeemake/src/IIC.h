#ifndef IIC_H
#define IIC_H
#include "Arduino.h"

#define SCL_HIGH  pinMode(_scl_pin,OUTPUT);digitalWrite(_scl_pin,HIGH)
#define SCL_LOW   pinMode(_scl_pin,OUTPUT);digitalWrite(_scl_pin,LOW)
#define SDA_HIGH  pinMode(_sda_pin,OUTPUT);digitalWrite(_sda_pin,HIGH)
#define SDA_LOW   pinMode(_sda_pin,OUTPUT);digitalWrite(_sda_pin,LOW)
#define SDA_INPUT pinMode(_sda_pin,INPUT)
#define SDA_READ  digitalRead(_sda_pin)

class IIC
{
public:
	IIC(uint8_t scl, uint8_t sda);

	void iic_start(void);
	void iic_stop(void);
	uint8_t iic_ack(void);
	void iic_noAck(void);
	void iic_write_byte(uint8_t byteWrite);
	uint8_t iic_read_byte(void);

private:
	uint8_t _scl_pin;
	uint8_t _sda_pin;
};

#endif