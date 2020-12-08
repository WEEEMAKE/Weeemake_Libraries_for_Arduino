#include "WeELF328P.h"

WeLEDPanelModuleMatrix7_21 ledPanel(PORT_C);

void setup()
{  
  ledPanel.setBrightness(7);     // Brightness:0-7
  ledPanel.clearScreen();
}
void loop() 
{
  ledPanel.turnOnDot(1,1);    //(x,y)
  ledPanel.turnOnDot(2,2);    //(x,y)
  ledPanel.turnOnDot(3,3);   //(x,y)

  delay(1000);
  ledPanel.turnOffDot(1,1);
  delay(1000);
  ledPanel.turnOffDot(2,2);
  delay(1000);
  ledPanel.turnOffDot(3,3);
  delay(1000);

}

