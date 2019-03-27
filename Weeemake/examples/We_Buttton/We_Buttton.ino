#include "WeELF328P.h"
WeButton button(OnBoard_Button);
int value = 0; 
void setup() 
{
    Serial.begin(9600);
}
void loop()
{
  value = button.read();
  if (value == 0)
  {
     Serial.println("Button Pressed");
   }
  if (value == 1)
  {
     Serial.println("Button Loosen");
   } 
   delay(100);
}
