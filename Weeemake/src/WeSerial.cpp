
#include "WeSerial.h"
#include <stdio.h>
#include <stdarg.h>


WeSerial::WeSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic)\
                   : SoftwareSerial(receivePin, transmitPin, inverse_logic)
{
  _scratch = false;
  _hard = false;
  _polling = false;
  _RxPin = receivePin;
  _TxPin = transmitPin;
}

void WeSerial::setHardware(bool mode)
{
  _hard = mode;
}

void WeSerial::begin(long baudrate)
{
  _bitPeriod = 1000000 / baudrate;
  if (_hard)
  {
  }
  else
  {
    SoftwareSerial::begin(baudrate);
  }
}

void WeSerial::end(void)
{
  if (_hard)
  {
  }
  else
  {
    SoftwareSerial::end();
  }
}

size_t WeSerial::write(uint8_t byte)
{
  if (_hard)
  {
  }
  else
  {
    return (SoftwareSerial::write(byte) );
  }
}

int16_t WeSerial::read(void)
{
  if (_polling)
  {
    int16_t temp = _byte;
    _byte = -1;
    return (temp > -1 ? temp : poll() );
  }
  if (_hard)
  {
  }
  else
  {
    return (SoftwareSerial::read() );
  }
}

int16_t WeSerial::available(void)
{
  if (_polling)
  {
    _byte = poll();
    return (_byte > -1 ? 1 : 0);
  }
  if (_hard)
  {
  }
  else
  {
    return (SoftwareSerial::available() );
  }
}

bool WeSerial::listen(void)
{
  if (_hard)
  {
    return (true);
  }
  else
  {
    return (SoftwareSerial::listen() );
  }
}

bool WeSerial::isListening(void)
{
  if (_hard)
  {
    return (true);
  }
  else
  {
    return (SoftwareSerial::isListening() );
  }
}

int16_t WeSerial::poll(void)
{
  int16_t val = 0;
  int16_t bitDelay = _bitPeriod - clockCyclesToMicroseconds(50);
  if (digitalRead(_RxPin) == LOW)
  {
    for (int16_t offset = 0; offset < 8; offset++)
    {
      delayMicroseconds(bitDelay);
      val |= digitalRead(_RxPin) << offset;
    }
    delayMicroseconds(bitDelay);
    return (val & 0xff);
  }
  return (-1);
}

void WeSerial::sendString(char *str)
{
  while(*str)
  {
    write(*str++);
  }
}

void WeSerial::printf(char *fmt,...)
{
  va_list ap;
  char string[128];
  va_start(ap,fmt);
  vsprintf(string,fmt,ap);
  sendString(string);
  va_end(ap);
}

boolean WeSerial::dataLineAvailable(void)
{
  if(available())
  {
    char c = read();
    if(c=='\n')
    {
      buffer[bufferIndex] = 0;
      return true;
    }
    else
    {
      buffer[bufferIndex]=c;
      bufferIndex++;
    }
  }
  return false;
}

String WeSerial::readDataLine(void)
{
  if(bufferIndex>0)
  {
    lastLine = buffer;
  }
  bufferIndex = 0;
  memset(buffer,0,64);
  return lastLine;
}

float WeSerial::getValue(String key)
{
  String s = readDataLine();
  if(stringLength(s)>2)
  {
    char * tmp;
    char * str;
    str = strtok_r((char*)s.c_str(), "=", &tmp);
    if(str!=NULL && strcmp(str,key.c_str())==0)
    {
      float v = atof(tmp);
      return v;
    }
  }
  return 0;
}

boolean WeSerial::equalString(String s1,String s2)
{
  return s1.equals(s2);
}

String WeSerial::concatenateWith(String s1,String s2)
{
  return s1+s2;
}

char WeSerial::letterOf(int i,String s)
{
  return s.charAt(i);
}

int WeSerial::stringLength(String s)
{
  return s.length();
}
