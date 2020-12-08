#include "WeOneWire.h"

WeOneWire::WeOneWire(uint8_t pin)
{
  reset(pin);
}

WeOneWire::WeOneWire(void){}

void WeOneWire::reset(uint8_t pin)
{
  WePIN=pin;
  bitmask = WePIN_TO_BITMASK(pin);
  baseReg = WePIN_TO_BASEREG(pin);
}

uint8_t WeOneWire::reset(void)
{ 
	WeIO_REG_TYPE mask = bitmask;
	volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;

  uint8_t r;

  WeDIRECT_MODE_OUTPUT(reg, mask);
  WeDIRECT_WRITE_LOW(reg, mask);
  delayMicroseconds(480);
  pinMode(WePIN,INPUT);
  delayMicroseconds(50);
  r=WeDIRECT_READ(reg, mask);
  delayMicroseconds(100);

  return r;
}

uint8_t WeOneWire::respond(void)
{ 
	WeIO_REG_TYPE mask = bitmask;
	 volatile WeIO_REG_TYPE *reg WeIO_REG_ASM = baseReg;

  unsigned long time;
  time = millis();
  WeDIRECT_MODE_INPUT(reg, mask);
  while(WeDIRECT_READ(reg, mask)==1)
  {
  	if((millis()-time)>100)
	return 1;
  }
  while(WeDIRECT_READ(reg, mask)==0);
  WeDIRECT_MODE_OUTPUT(reg, mask);
  WeDIRECT_WRITE_LOW(reg, mask);
  delayMicroseconds(30);
  pinMode(WePIN,INPUT);
  return 0;
}

void WeOneWire::write_bit(uint8_t value)
{
  noInterrupts();
  digitalWrite(WePIN,LOW);
  pinMode(WePIN,OUTPUT);
  delayMicroseconds(7);
  digitalWrite(WePIN, value);
  interrupts();
  delayMicroseconds(30);
  digitalWrite(WePIN,HIGH);
  delayMicroseconds(8);
}

void WeOneWire::write_byte(uint8_t v)
{
  for(int i=0;i<8;i++){
    write_bit((v >> i) & 1);
  }
  pinMode(WePIN,INPUT);
}

uint8_t WeOneWire::read_bit(void)
{
  WeIO_REG_TYPE mask = bitmask;
  volatile uint8_t *reg WeIO_REG_ASM = baseReg;

  unsigned long time = millis();
  while(WeDIRECT_READ(reg, mask) == 1 && (millis() - time) <= 3);

  noInterrupts();
  delayMicroseconds(35);
  uint8_t r = WeDIRECT_READ(reg, mask);
  interrupts();
  delayMicroseconds(40);

  return r;
}

uint8_t WeOneWire::read_byte(void)
{
  uint8_t k = 0;
  pinMode(WePIN, INPUT);
  for(int i=0;i<8;i++){
    k |= read_bit() << i;
  }
  return k;
}

bool WeOneWire::send(uint8_t id, uint8_t dataLen, byte* data)
{
  if(reset())return false;
  write_byte(id);
  if(dataLen == 0)return true;
  if(reset())return false;
  for(int i=0; i<dataLen; ++i)
    write_byte(data[i]);
  return true;
}

bool WeOneWire::recv(uint8_t id, uint8_t dataLen, byte* data)
{
  if(reset())return false;
  write_byte(id);
  if(respond())return false;
  for(int i=0; i<dataLen; ++i)
    data[i] = read_byte();
  return true;
}

bool WeOneWire::write(uint8_t id, uint8_t dataLen, byte* data, long time, uint8_t writeDataLen, byte* writeData)
{
  if(reset())return false;
  write_byte(id);
  if(writeDataLen > 0){
    if(reset())return false;
    for(int i=0; i<writeDataLen; ++i)
      write_byte(writeData[i]);
  }
  if(dataLen == 0)return true;
  unsigned long timestamp = millis() + time;
  while(respond())
    if(millis() >= timestamp)
      return false;
  for(int i=0; i<dataLen; ++i)
    data[i] = read_byte();
  return true;
}

bool WeOneWire::send(uint8_t id)
{
  send(id, 0, 0);
}








