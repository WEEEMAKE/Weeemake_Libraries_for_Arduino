#include "WeBuzzer.h"
#include <avr/wdt.h>

WeBuzzer::WeBuzzer(uint8_t port)
{
  buzzer_pin=port;
}

void WeBuzzer::reset(uint8_t port)
{
  buzzer_pin = port;
}


void WeBuzzer::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    wdt_reset();
  }
}
void WeBuzzer::tone2(uint16_t frequency, uint32_t duration)
{
  cli();
  tone(frequency,duration);
  sei();
}

void WeBuzzer::noTone()
{
   pinMode(buzzer_pin, OUTPUT);
   digitalWrite(buzzer_pin, LOW);

}

void WeBuzzer::buzzerOn(uint16_t delaytime)
{
  for(int i=0;i<delaytime;i++)
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(500);
  }
}




