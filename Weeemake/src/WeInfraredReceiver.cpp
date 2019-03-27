#include "WeInfraredReceiver.h"
#include <avr/interrupt.h>

volatile irparams_t irparams;
volatile uint8_t _RxPin;

bool MATCH(uint8_t measured_ticks, uint8_t desired_us)
{
  // Serial.print(measured_ticks);Serial.print(",");Serial.println(desired_us);
  return(measured_ticks >= desired_us - (desired_us>>2)-1 && measured_ticks <= desired_us + (desired_us>>2)+1);//判断前后25%的误差
}


ISR(TIMER_INTR_NAME)
{
  uint8_t irdata = (uint8_t)digitalRead(_RxPin);
  irparams.timer++; // One more 50us tick
  if (irparams.rawlen >= RAWBUF)
  {
    // Buffer overflow
    irparams.rcvstate = STATE_STOP;
  }
  switch(irparams.rcvstate)
  {
    case STATE_IDLE: // In the middle of a gap
      if (irdata == MARK)
      {
        irparams.rawlen = 0;
        irparams.timer = 0;
        irparams.rcvstate = STATE_MARK;
      }
      break;
    case STATE_MARK: // timing MARK
      if (irdata == SPACE)
      {
        // MARK ended, record time
        irparams.rawbuf[irparams.rawlen++] = irparams.timer;
        irparams.timer = 0;
        irparams.rcvstate = STATE_SPACE;
      }
      break;
    case STATE_SPACE: // timing SPACE
      if (irdata == MARK)
      {
        // SPACE just ended, record it
        irparams.rawbuf[irparams.rawlen++] = irparams.timer;
        irparams.timer = 0;
        irparams.rcvstate = STATE_MARK;
      }
      else
      { // SPACE
        if (irparams.timer > GAP_TICKS)
        {
        
		   irparams.rcvstate = STATE_STOP;
				  irparams.lastTime = millis();
				} 
			  }
			  break;
			case STATE_STOP: // waiting, measuring gap
			  if(millis() - irparams.lastTime > 200)
			  {
				irparams.rawlen = 0;
				irparams.timer = 0;
				irparams.rcvstate = STATE_IDLE;
			  }
			  else if (irdata == MARK)
			  { 
				// reset gap timer
				irparams.timer = 0;
			  }
			  break;
   }
		  // irparams.lastTime = new_time;
}

WeInfraredReceiver::WeInfraredReceiver(uint8_t port)
{
  _RxPin=port;
  pinMode(_RxPin,INPUT);
  irparams.recvpin = _RxPin;
}

void WeInfraredReceiver::reset(uint8_t port)
{
  if(_RxPin == port)
    return;
  _RxPin=port;
  pinMode(_RxPin,INPUT);
  irparams.recvpin = _RxPin;
}

ErrorStatus WeInfraredReceiver::loop()
{
	static unsigned long timestamp = 0;
  ErrorStatus result = decode();
	if(result){
		timestamp = millis();
		IR_VALUE = (value >> 16) & 0xFF;
	}else if(millis() - timestamp > 200){
		IR_VALUE = 0;
	}
  return result;
}
bool WeInfraredReceiver::isKeyPressed(uint8_t key)
{
	return IR_VALUE == key;
}

uint8_t WeInfraredReceiver::getValue(void)
{
  return IR_VALUE;
}


void WeInfraredReceiver::begin(void)
{
   cli();
   TIMER_CONFIG_NORMAL();
   TIMER_ENABLE_INTR;
   sei();
   irparams.rawlen = 0;
   irparams.rcvstate = STATE_IDLE;
  
}

ErrorStatus WeInfraredReceiver::decode()
{
  rawbuf = irparams.rawbuf;
  rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP)
  {
    return ERROR;
  }

  if (decodeNEC())
  {
    begin();
    return SUCCESS;
  }
  begin();
  return ERROR;
}

ErrorStatus WeInfraredReceiver::decodeNEC()
{
  uint32_t data = 0;
  int offset = 0; // Skip first space
  // Initial mark
  if (!MATCH(rawbuf[offset], NEC_HDR_MARK/50)) 
  {
    return ERROR;
  }
  offset++;
  // Check for repeat
  if (rawlen == 3 &&
    MATCH(rawbuf[offset], NEC_RPT_SPACE/50) &&
    MATCH(rawbuf[offset+1], NEC_BIT_MARK/50)) 
  {
    bits = 0;
    // results->value = REPEAT;
    // Serial.println("REPEAT");
    decode_type = NEC;
    return SUCCESS;
  }
  if (rawlen < (2 * NEC_BITS + 3)) 
  {
    return ERROR;
  }
  // Initial space  
  if (!MATCH(rawbuf[offset], NEC_HDR_SPACE/50)) 
  {
    return ERROR;
  }
  offset++;
  for (int i = 0; i < NEC_BITS; i++)
  {
    if (!MATCH(rawbuf[offset], NEC_BIT_MARK/50)) 
    {
      return ERROR;
    }
    offset++;
    if (MATCH(rawbuf[offset], NEC_ONE_SPACE/50))
    {		
			  //data = (data << 1) | 1;
			  data = (data >> 1) | 0x80000000;
			} 
			else if (MATCH(rawbuf[offset], NEC_ZERO_SPACE/50))
			{
			  //data <<= 1;
			  data >>= 1;
			} 
			else 
			{
			  return ERROR;
			}
			offset++;
		  }
		  // Success
     bits = NEC_BITS;
	 value = data;
	decode_type = NEC;
    return SUCCESS;
}


