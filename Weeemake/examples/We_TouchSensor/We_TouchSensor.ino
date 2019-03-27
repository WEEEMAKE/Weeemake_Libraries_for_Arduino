#include "WeELF328P.h"

WeTouchSensor touchSensor(PORT_A);
int t_count=0;
void setup()
{  
   touchSensor.setMode(0);
   Serial.begin(9600);
}
void loop() 
{ 
    if(touchSensor.touched()==1)
    {
       t_count++;
       Serial.print("Pressed: ");
       Serial.println(t_count); 
       delay(100);
     }
}
