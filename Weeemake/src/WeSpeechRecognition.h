
#ifndef WeSpeechRecognition_H
#define WeSpeechRecognition_H

#include "WePort.h"

class WeSpeechRecognition
{
public:

   WeSpeechRecognition(uint8_t port);
   void reset(uint8_t port);
   //void setKeyword(String str);
   void setKeyword( const char *str);
   void setPassword(int8_t list,const char *str);
   uint8_t read(void);
   void setTriggerMode(uint8_t mode);
   void setResponseRate(uint8_t rate);
   void beginTrigger(void);
   void stopTrigger(void);
   
 private:
	WeOneWire _WeSpeechRecognition;
	volatile uint8_t DATA_A=40;
};

#endif

