#include "WeELF328P.h"

WeWaterAtomizer atomizer(PORT_A);

void setup()
{  
}
void loop() 
{
   atomizer.start();
   delay(2000);
   atomizer.stop();
   delay(3000);
}
