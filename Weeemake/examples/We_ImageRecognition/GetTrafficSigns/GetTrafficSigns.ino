#include "WeELF328P.h"
WeImageRecognition image(PORT_A);

void setup() 
{
    Serial.begin(9600);
    image.setTrafficSignsMode();
}
uint8_t num=0;
void loop()
{ 
  num=image.getTrafficSigns();
  switch(num)
  {
      case 1:  Serial.println("Forward");break;
      case 2:  Serial.println("Turn back");break;
      case 3:  Serial.println("Left");break;
      case 4:  Serial.println("Right");break;
      case 5:  Serial.println("Park");break;
   }
}
