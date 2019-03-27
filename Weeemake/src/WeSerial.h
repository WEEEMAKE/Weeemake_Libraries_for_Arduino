
#ifndef WeSerial_H
#define WeSerial_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <utility/SoftwareSerial.h>

class WeSerial : public SoftwareSerial
{
public:

  WeSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
  void setHardware(bool mode);
  void begin(long baudrate);
  size_t write(uint8_t byte);
  int read();
  int available();
  int16_t poll(void);
  void end(void);
  bool listen(void);
  bool isListening(void);
  void sendString(char *str);

  void printf(char *fmt,...);

  boolean dataLineAvailable(void);
  String readDataLine(void);
  String concatenateWith(String s1,String s2);
  char letterOf(int i,String s);
  int stringLength(String s);
  boolean equalString(String s1,String s2);
  float getValue(String key);

protected:
  bool _hard;
  bool _polling;
  bool _scratch;
  int16_t _bitPeriod;
  int16_t _byte;
  long _lastTime;
  char buffer[64];
  String lastLine;
  int bufferIndex;

private:
  volatile uint8_t _RxPin;
  volatile uint8_t _TxPin; 
};
#endif

