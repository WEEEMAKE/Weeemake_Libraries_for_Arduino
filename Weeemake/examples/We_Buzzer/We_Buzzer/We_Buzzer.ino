#include "WeELF328P.h"
WeBuzzer buzzer(OnBoard_Buzzer);

void setup() 
{
}
void loop()
{
  buzzer.buzzerOn(1000);  //1000 millseconds
  delay(1000);
 
}
