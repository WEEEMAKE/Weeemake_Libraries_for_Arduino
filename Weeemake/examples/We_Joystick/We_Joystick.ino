#include "WeELF328P.h"

WeJoystick joystick(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  joystick.readData();
  Serial.print("X= ");
  Serial.println(joystick.showX());
  Serial.print("Y= ");
  Serial.println(joystick.showY());
  if(joystick.showKey()==1)
  Serial.println("KEY=1");
  delay(100);
}
