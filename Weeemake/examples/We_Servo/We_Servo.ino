#include "WeELF328P.h"

Servo weservo;
void setup() 
{
    weservo.attach(PORT_1);
}
void loop()
{
  weservo.write(0);                  // sets the servo position according to the scaled value 0-180
  delay(2000);                           // waits for the servo to get there 
  weservo.write(180);
  delay(2000); 
}
