#include "WeELF328P.h"
WeOneWire portDetect;

void module_test();
void print_module(uint8_t port);
uint8_t flag_A,flag_B,flag_C,flag_D;

void setup()
{
   pinMode(9, INPUT);
   pinMode(10, INPUT);
   pinMode(12, INPUT);
   pinMode(4, INPUT);
   Serial.begin(9600);
}

void loop() 
{
     module_test();    
}

void module_test()
{
   
    if((digitalRead(9)==1)&&(flag_A==0))
    {
        flag_A=1;
        Serial.print("PORT_A Insert:");
        print_module(9);
     }
     else if((digitalRead(9)==0)&&(flag_A==1))
     {
         flag_A=0;
         Serial.println("PORT_A Module Pull Out!");
     }
    
     if((digitalRead(10)==1)&&(flag_B==0))
    {
        flag_B=1;
        Serial.print("PORT_B Insert:");
        print_module(10);
     }
     else if((digitalRead(10)==0)&&(flag_B==1))
    {
        flag_B=0;
        Serial.println("PORT_B Module Pull Out!");
     }
     
     if((digitalRead(12)==1)&&(flag_C==0))
    {
        flag_C=1;
        Serial.print("PORT_C Insert:");
        print_module(12);
     }
      else if((digitalRead(12)==0)&&(flag_C==1))
    {
        flag_C=0;
        Serial.println("PORT_C Module Pull Out!");
     }
     
     if((digitalRead(4)==1)&&(flag_D==0))
    {
        flag_D=1;
        Serial.print("PORT_D Insert:");
        print_module(4);
     }
     else if((digitalRead(4)==0)&&(flag_D==1))
    {
        flag_D=0;
        Serial.println("PORT_D Module Pull Out!");
     }
}
void print_module(uint8_t port)
{
  delay(500);
  uint8_t module_code;
   portDetect.reset(port);
   portDetect.reset();
   portDetect.write_byte(0x01);
   portDetect.respond();
   module_code=portDetect.read_byte(); 
   switch(module_code)
   {
      case 1: Serial.println("UltrasonicSensor");break;
      case 2: Serial.println("LineFollower");break;
      case 3: Serial.println("LEDPanelModuleMatrix7_21");break;      
      default:Serial.println(module_code);break;
   }
}
