#include "WeELF328P.h"

We4LEDButton LEDButton(PORT_A);
uint8_t count = 0;
uint8_t lednum = 0;
uint8_t keyPressed=0;

void setup()
{  
  Serial.begin(9600);
  randomSeed(analogRead(A6));
}
void loop() 
{
  LEDButton.openLED(1);
  LEDButton.openLED(2);
  LEDButton.openLED(3);
  LEDButton.openLED(4);
  delay(1000);
  LEDButton.closeLED(1); 
  LEDButton.closeLED(2); 
  LEDButton.closeLED(3); 
  LEDButton.closeLED(4); 
  delay(1000);   
  for(int i=0;i<20;i++)
  {
     lednum=random(1, 5);
     LEDButton.openLED(lednum);
     delay(100);
     LEDButton.closeLED(lednum); 
     delay(100);
     for(int j=0;j<5;j++)
     {
         keyPressed=LEDButton.readKey();
         if (keyPressed==lednum)
         {
            count++;
            break;
          }
          delay(50);
     }
     delay(500);   
  }
  Serial.println(count);
  count=0;
  delay(2000);
  
}
