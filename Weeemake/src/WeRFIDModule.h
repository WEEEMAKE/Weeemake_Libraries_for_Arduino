
#ifndef _WeRFIDModule_H
#define _WeRFIDModule_H

#include "WePort.h"

class WeRFIDModule
{
public:

    WeRFIDModule(uint8_t port=0);
    void reset(uint8_t port=0);
    
    bool read(void);
    uint32_t ID_Number;
    String ID_String;
  
private:
    WeOneWire _WeRFIDModule;
    uint8_t rx_buffer[13]={0};
    void getID(void);
};

#endif
