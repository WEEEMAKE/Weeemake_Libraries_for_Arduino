
#ifndef _WEPORT_H_
#define _WEPORT_H_

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "WeOneWire.h"
#include "WeSensor.h"


typedef struct
{
  uint8_t s1;
  uint8_t s2;
} WePort_TwoSig;

//extern uint8_t WeonePort[17];  
extern WePort_TwoSig WetwoPort[12];  
extern void setfastPWM();

#define NC (0)  //use UART RX for NULL port




#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif


#endif // MEPORT_H_
