#ifndef WeOneWire_H
#define WeOneWire_H

#include <WeConfig.h>


class WeOneWire
{
private:
	uint8_t WePIN;
	uint8_t   bitmask;
    volatile WeIO_REG_TYPE *baseReg;

public:
    WeOneWire(uint8_t pin);
    WeOneWire();
   void reset(uint8_t pin);
   
   uint8_t reset(void);
   uint8_t respond(void);
   void write_byte(uint8_t v);
   
   uint8_t read_byte(void);
   bool send(uint8_t id);
   bool send(uint8_t id, uint8_t dataLen, byte* data);
   bool recv(uint8_t id, uint8_t dataLen, byte* data);
   bool write(uint8_t id, uint8_t dataLen, byte* data, long time=0, uint8_t writeDataLen=0, byte* writeData=0);

private:
  uint8_t read_bit(void);
  void write_bit(uint8_t value);
};

#endif



