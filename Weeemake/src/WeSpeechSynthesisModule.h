#ifndef We_Speech_Synthesis_Module_H
#define We_Speech_Synthesis_Module_H

#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h>

class WeSpeechSynthesisModule
{
public:
  WeSpeechSynthesisModule(uint8_t port);
  void speek(uint8_t *data_in, uint8_t len);
  void playSound(uint8_t *data_in, uint8_t len, uint16_t t_ms);
  void speekForFlash(uint8_t *data_in, uint8_t len);

private:
  uint16_t _tx_delay;
  uint16_t _inverse_logic:1;
  uint8_t _transmitBitMask;
  volatile uint8_t *_transmitPortRegister;
  void setTX(uint8_t transmitPin);
  void begin(long speed);
  virtual size_t write(uint8_t byte);
  static uint16_t subtract_cap(uint16_t num, uint16_t sub);
  static inline void tunedDelay(uint16_t delay);
};

#endif