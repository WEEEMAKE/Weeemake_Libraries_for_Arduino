#include "WeELF328P.h"

We7SegmentDisplay Display(PORT_A);
int8_t NumTab[] = {0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x20,0x21,0x22,0x40};   //A,B,C,D,E,F,-,0.,1.,2.,NULL
int i=0;
void setup()
{  
}

void loop() 
{
 
  Display.showNumber(i);
  delay(100);
  i++;
  if(i>200)
  { 
      for(unsigned char j=0;j<6;j++)
      {
         Display.showChar(1,NumTab[j]);
         Display.showChar(2,NumTab[j]);
         Display.showChar(3,NumTab[j]);
         Display.showChar(4,NumTab[j]);
         delay(1000);
      }  
      i=0;   
  }
}
