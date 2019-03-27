#include "WeELF328P.h"
WeRGBLed led(PORT_6);

int16_t bri = 0, st = 0;
void setup() 
{
}
void loop()
{
  color_loop();
}

void color_loop()   //White Breath Light
{
   if(bri >= 40)     //Brightness:0-255
  {
    st = 1;
  }
  if(bri <= 0)
  {
    st = 0;
  }
  if(st)
  {
    bri--;
  }
  else
  {
    bri++;
  }
  
   led.setColor(0, bri, bri, bri);  // led number, red, green, blue,
   led.show();
   delay(50);   
}
