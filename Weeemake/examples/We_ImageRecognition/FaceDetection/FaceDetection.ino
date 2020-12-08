#include "WeELF328P.h"
WeImageRecognition image(PORT_A);

void setup() 
{
    Serial.begin(9600); 
}
void loop()
{
  if(image.getFacePositon()==1)
  {
    Serial.print(image.centerX);
    Serial.print('-');
    Serial.println(image.centerY);
  }
  delay(20); 
}
