#ifndef WeSmartIRModule_H
#define WeSmartIRModule_H

#include "WePort.h"

class WeSmartIRModule
{
public:
  WeSmartIRModule(uint8_t port=0);
  void reset(uint8_t port);

  void send(uint8_t num);
  void receiver(uint8_t num);
  
private:
  WeOneWire _WeSmartIRModule;
};

#endif