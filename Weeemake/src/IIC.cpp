#include "IIC.h"
#include "Arduino.h"

IIC::IIC(uint8_t scl, uint8_t sda)
{
	_scl_pin = scl;
	_sda_pin = sda;
}

void IIC::iic_start()
{
	SCL_HIGH;
	SDA_HIGH;
	SDA_LOW;
}

void IIC::iic_stop()
{
	SCL_LOW;
	SDA_LOW;
	SCL_HIGH;
	SDA_HIGH;
}

uint8_t IIC::iic_ack()
{
	uint8_t ackFlag;
	//SCL_LOW;
	SDA_INPUT;
	SCL_HIGH;
	ackFlag = SDA_READ;
	SCL_LOW;
	return ackFlag;
}

void IIC::iic_noAck()
{
	SCL_LOW;
	SDA_INPUT;
	SCL_HIGH;
	SCL_LOW;
}

void IIC::iic_write_byte(uint8_t byteWrite)
{
	uint8_t index;
	for (index = 0; index < 8; ++index){
		SCL_LOW;
		if (byteWrite&0x80){
			SDA_HIGH;
		}else{
			SDA_LOW;
		}
		SCL_HIGH;
		byteWrite <<= 1;
	}
	SCL_LOW;
}

uint8_t IIC::iic_read_byte()
{
	uint8_t byteRead,index;
	for (index = 0; index < 8; ++index){
		byteRead <<= 1;
		SCL_LOW;
		SDA_INPUT;
		SCL_HIGH;
		if (SDA_READ){
			byteRead |= 0x01;
		}
		SCL_LOW;
	}
	return byteRead;
}