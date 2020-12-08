#include "WeELF328P.h"
#include "SoftwareSerial.h"

WeUSBHost PS2(A3, A2);  //A3,A2 for 328P

void setup()
{
  Serial.begin(9600);
  PS2.init(USB2_0);  
  delay(10);
}

void loop()
{
  PS2.loop();
  //PS2.printValue();
  if (PS2.ButtonPressed(WeJOYSTICK_START))
  {
    Serial.println("START is pressed!");
  }
  if (PS2.ButtonPressed(WeJOYSTICK_SELECT))
  {
    Serial.println("SELECT is pressed!");
  }
  if (PS2.ButtonPressed(WeJOYSTICK_MODE))
  {
    Serial.println("MODE is pressed!");
  }
  if (PS2.ButtonPressed(WeJOYSTICK_BUTTON_L))
  {
    Serial.println("BUTTON_L is pressed!");
  }
  if (PS2.ButtonPressed(WeJOYSTICK_BUTTON_R))
  {
    Serial.println("BUTTON_R is pressed!");
  }
  
  if (PS2.ButtonPressed(WeJOYSTICK_UP_L))
  {
    Serial.print("L UP is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_UP_L));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_DOWN_L))
  {
    Serial.print("L DOWN is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_DOWN_L));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_LEFT_L))
  {
    Serial.print("L LEFT is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_LEFT_L));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_RIGHT_L))
  {
    Serial.print("L RIGHT is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_RIGHT_L));
  }
   if (PS2.ButtonPressed(WeJOYSTICK_L1))
  {
    Serial.print("L1 is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_L1));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_R1))
  {
    Serial.print("R1 is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_R1));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_L2))
  {
    Serial.print("L2 is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_L2));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_R2))
  {
    Serial.print("R2 is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_R2));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_UP_R))
  {
    Serial.print("R UP is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_UP_R));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_DOWN_R))
  {
    Serial.print("R DOWN is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_DOWN_R));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_LEFT_R))
  {
    Serial.print("R LEFT is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_LEFT_R));
  }
  if (PS2.ButtonPressed(WeJOYSTICK_RIGHT_R))
  {
    Serial.print("R RIGHT is ");
    Serial.println(PS2.readAnalog(WeJOYSTICK_RIGHT_R));
  }
  
  if(PS2.joystickRx()!=128)
  {
    Serial.print("PS2_RX value is: ");
    Serial.println(PS2.joystickRx());
  }
  if(PS2.joystickRy()!=127)
  {
    Serial.print("PS2_RY value is: ");
    Serial.println(PS2.joystickRy());
  }
  if(PS2.joystickLx()!=128)
  {
    Serial.print("PS2_LX value is: ");
    Serial.println(PS2.joystickLx());
  }
  if(PS2.joystickLy()!=127)
  {
    Serial.print("PS2_LY value is: ");
    Serial.println(PS2.joystickLy());
  }
}

