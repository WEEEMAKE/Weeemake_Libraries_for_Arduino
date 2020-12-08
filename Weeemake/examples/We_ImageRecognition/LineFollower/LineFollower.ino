#include "WeELF328P.h"
WeImageRecognition image(PORT_A);

void setup() 
{
    Serial.begin(9600);
    image.setLineFollowerMode(); 
}
void loop()
{
  if(image.getLineFollowerAngle()==1)
  {
      Serial.println(image.angle);      
  }
  delay(50); 
}
