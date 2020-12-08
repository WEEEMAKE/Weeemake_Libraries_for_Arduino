#include "WeELF328P.h"

WeFunnyTouchSensor funnytouch(PORT_A);
uint8_t value = 0; 
void setup() 
{
    Serial.begin(9600);
}
void loop()
{
  value = funnytouch.readValue();

  if ((value&0x01)>0)
  {
     Serial.println("Touch 1 Pressed");
  }
  if ((value&0x02)>0)
  {
     Serial.println("Touch 2 Pressed");
   }
   if ((value&0x04)>0)
  {
     Serial.println("Touch 3 Pressed");
  }
  if ((value&0x08)>0)
  {
     Serial.println("Touch 4 Pressed");
   }
   if ((value&0x10)>0)
  {
     Serial.println("Touch 5 Pressed");
  }
  if ((value&0x20)>0)
  {
     Serial.println("Touch 6 Pressed");
   } 
   delay(100);
}
