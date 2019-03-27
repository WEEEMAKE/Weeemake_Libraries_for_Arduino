#include "WeELF328P.h"

WeRGBLED_RJ RGBLED(PORT_A);
float j, f, k;
void setup()
{  
}
void loop() 
{
  for(uint8_t t = 1; t < 6; t++)
  {
    uint8_t red  = 10 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 10 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 10 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    RGBLED.setColor(t, red, green, blue);    //(Red,Green,Blue)
  }
  RGBLED.RGBShow();
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
  delay(10);
}
