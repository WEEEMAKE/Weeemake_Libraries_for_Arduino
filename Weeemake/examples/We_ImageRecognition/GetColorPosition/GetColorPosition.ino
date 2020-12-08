#include "WeELF328P.h"
WeImageRecognition image(PORT_A);

void setup() 
{
    Serial.begin(9600);
    image.fastMode();
}
void loop()
{
  if(image.getColorPosition(1)==1)
  {
    Serial.print(image.centerX);
    Serial.print('-');
    Serial.print(image.centerY);
    Serial.print('-');
    Serial.println(image.pixels);
  }
}
