#include "WeELF328P.h"

WeLEDPanelModuleMatrix5_14 ledPanel(PORT_C);

void setup()
{  
  ledPanel.setBrightness(2);     // Brightness:0-7
  ledPanel.clearScreen();
  ledPanel.writeChar(0,0,3);
  ledPanel.writeChar(4,0,3);
  ledPanel.writeChar(9,0,15);
}
void loop() 
{
  // ledPanel.turnOnDot(1,1);    //(x,y)
  // ledPanel.turnOnDot(2,2);    //(x,y)
  // ledPanel.turnOnDot(3,3);   //(x,y)

  // delay(1000);
  // ledPanel.turnOffDot(1,1);
  // delay(1000);
  // ledPanel.turnOffDot(2,2);
  // delay(1000);
  // ledPanel.turnOffDot(3,3);
  // delay(1000);
      ledPanel.showNum(1.9);
      delay(1000);
      ledPanel.showNum(0);
      delay(1000);
      ledPanel.showNum(9.9);
      delay(1000);

}

