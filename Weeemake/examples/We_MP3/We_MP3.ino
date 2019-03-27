#include "WeELF328P.h"

WeMP3 mp3(PORT_A);

void setup()
{  
  mp3.appointVolume(20);  //Volume 0~22 
  mp3.appointDevice(4);   //2-TF; 4-FLASH
  mp3.appointMusic(1);   //0~3000
}
void loop() 
{
  if(mp3.isOver()==1)
  {
     mp3.nextMusic();
  }
}
