#include "WeELF328P.h"

WeOLED oled(PORT_A);

void setup()
{  
   oled.setdigits(2); //   0.01
   oled.setSize(8);  //    8or16
   oled.clearScreen();
}
char *s ="WeeeMake";
void loop() 
{
  oled.showString(0,0,s);
  oled.showNum(0,2,123);
  oled.showChar(0,4,0xff);  
  delay(1000);
}

