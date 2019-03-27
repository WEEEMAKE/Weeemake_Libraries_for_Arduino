#include "WeELF328P.h"

WeRelay relay(PORT_A);

void setup()
{  
}
void loop() 
{ 
    relay.openNC();
    delay(2000);
    relay.closeNC();
    delay(2000);
}
