#include "WeOLED.h"


WeOLED::WeOLED(uint8_t port)
{
  _WeOLED.reset(port);

}

void WeOLED::reset(uint8_t port)
{
  _WeOLED.reset(port);
}

void WeOLED::setSize(uint8_t size)
{
   charSize=size;
}
void WeOLED::setdigits(uint8_t mun)
{
   digits_num=mun;
}

void WeOLED::clearScreen(void)
{
  uint8_t i;
  if(_WeOLED.reset()!=0)
   return;
  _WeOLED.write_byte(0x04);
  delayMicroseconds(3000);
}

void WeOLED::fullScreen(void)
{
	if(_WeOLED.reset()!=0)
   return;
  _WeOLED.write_byte(0x06);
  delayMicroseconds(3000);
}

void WeOLED::showString(uint8_t X_position,uint8_t Y_position,char *str)
{
	uint8_t number_of_Str;
	if(_WeOLED.reset()!=0)
    return;
	_WeOLED.write_byte(0x02);
    if(_WeOLED.reset()!=0)
	 return;
	_WeOLED.write_byte(charSize);
	_WeOLED.write_byte(X_position);
	_WeOLED.write_byte(Y_position);
	for(number_of_Str=0;str[number_of_Str] != '\0';number_of_Str++)
	{
	  _WeOLED.write_byte((int8_t)(str[number_of_Str]));
	}
	_WeOLED.write_byte(0);
	delayMicroseconds(3000);
}

void WeOLED::show8dot(uint8_t X_position,uint8_t Y_position,uint8_t buffer)
{
     if(_WeOLED.reset()!=0)
     return;
    _WeOLED.write_byte(0x03);
     if(_WeOLED.reset()!=0)
     return;
    _WeOLED.write_byte(X_position);
    _WeOLED.write_byte(Y_position);
	_WeOLED.write_byte(buffer);
	delayMicroseconds(3000);
}
void WeOLED::sendNum(uint8_t X_position,uint8_t Y_position,uint8_t Num)
{
   
if(_WeOLED.reset()!=0)
     return;
	_WeOLED.write_byte(0x05);
    if(_WeOLED.reset()!=0)
	 return;
	_WeOLED.write_byte(charSize);
	_WeOLED.write_byte(X_position);
	_WeOLED.write_byte(Y_position);
	_WeOLED.write_byte(Num);
	delayMicroseconds(3000);
}

void WeOLED::showNum(uint8_t X_position,uint8_t Y_position,double Num)
{
	double num_decimal=0;
	long num_integer=0;
	long num_data=1000000000;
	uint8_t digits_count;
	if(Num==0)
	{
	  sendNum(X_position,Y_position,0);
	}
	else
	{
	if(Num<0)
	{
	   sendNum(X_position,Y_position,-3);
	   X_position=X_position+8;
	   Num=-Num;
	}
	num_integer=(long)Num;
    num_decimal=Num-num_integer;	
	
	if(num_integer>=1)
	{
	   while((num_integer/num_data)==0) num_data=num_data/10;
	   while(num_data>1)
	   {
	     sendNum(X_position,Y_position,num_integer/num_data);
		 num_integer=num_integer%num_data;
		 num_data=num_data/10;
		 X_position=X_position+8;
	   }
	   sendNum(X_position,Y_position,num_integer/1);
	   X_position=X_position+8;
	   if (num_decimal>0)
	   {
	      digits_count=0;
	      if(digits_count>=digits_num) return;
	      sendNum(X_position,Y_position,-2);
		  X_position=X_position+8;
          while(num_decimal>0)
          {      
            if(digits_count>=digits_num) return;
		    sendNum(X_position,Y_position,num_decimal*10/1);
			num_decimal=num_decimal*10-(uint8_t)(num_decimal*10);
			X_position=X_position+8;
			digits_count++;
          }
	   }
	}
	else
	{
	  digits_count=0;
	  if(digits_count>=digits_num) return;
	  sendNum(X_position,Y_position,0); 
	  X_position=X_position+8;
	  sendNum(X_position,Y_position,-2);
	  X_position=X_position+8;
	  digits_num=0;
	  while(num_decimal>0)
      {
         if(digits_count>=digits_num) return;
	     sendNum(X_position,Y_position,num_decimal*10/1);
		 num_decimal=num_decimal*10-(uint8_t)(num_decimal*10);
		 X_position=X_position+8;
		 digits_count++;		 		 
      }	  
	}
		}
}

void WeOLED::showChineseCharacters(uint8_t X_position,uint8_t Y_position,uint8_t (*zh_str)[16], uint8_t no)
{
	for (uint8_t i = 0; i < 16; ++i)
	{
		show8dot(X_position+i,Y_position,zh_str[2*no][i]);
		show8dot(X_position+i,Y_position+1,zh_str[2*no+1][i]);
	}
}

void WeOLED::showBMP(uint8_t X_position,uint8_t Y_position,uint8_t p[])
{	
	 
}