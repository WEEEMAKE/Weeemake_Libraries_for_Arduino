#include "WeELF328P.h"
WeImageRecognition image(PORT_A);

void setup() 
{
   Serial.begin(9600);
   image.setLabColor1(66,90,-49,-20,-26,0); 
   image.setPixelsThreshold(10);
}
void loop()
{
  if(image.getAppColorPosition(1)==1)
  {
   Serial.print(image.centerX);
   Serial.print('-');
   Serial.print(image.centerY);
   Serial.print('-');
   Serial.println(image.pixels);
  }
  delay(20); 
}
