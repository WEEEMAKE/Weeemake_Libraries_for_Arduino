#include "WeELF328P.h"

WeLEDPanelModuleMatrix7_21 ledPanel(PORT_C);

void setup()
{  
  ledPanel.setBrightness(3);     // Brightness:0-7
  ledPanel.clearScreen();
}
char *s ="ABC";

void loop() 
{
  ledPanel.showChar(0,0,s);
  delay(2000);
  ledPanel.showNum(123.5);
  delay(2000);
  ledPanel.showClock(12,00,1);
  delay(2000); 
}

