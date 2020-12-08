#include "WeImageRecognition.h"

WeImageRecognition::WeImageRecognition(uint8_t port)
{
   reset(port);
}

void WeImageRecognition::reset(uint8_t port)
{
	_WeImageRecognition.reset(port);
}

bool WeImageRecognition::getLab(void)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return 0 ;
    _WeImageRecognition.write_byte(0x02);
	_WeImageRecognition.respond();
   	minL=_WeImageRecognition.read_byte();
	if(minL==-1)  return 0;
	maxL=_WeImageRecognition.read_byte();
	minA=_WeImageRecognition.read_byte();
	maxA=_WeImageRecognition.read_byte();
	minB=_WeImageRecognition.read_byte();
	maxB=_WeImageRecognition.read_byte();	
	return 1;
}

void WeImageRecognition::setAutoTrackingMode(void)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x03);
	delay(10);
}

bool WeImageRecognition::getAutoPosition(void)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return  0;
    _WeImageRecognition.write_byte(0x04);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<6;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
	pixels=(uartData[4]<<8)|uartData[5];
	if(centerX>320) return 0;
	if(centerY>240) return 0;
	//delay(10);
	return 1;
}

bool WeImageRecognition::getColorPosition(uint8_t num)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return  0;
    _WeImageRecognition.write_byte(0x05|num<<5);
 //   if(_WeImageRecognition.reset()!=0) 
//		return  0;
//	_WeImageRecognition.write_byte(num);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<6;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
	pixels=(uartData[4]<<8)|uartData[5];
	if(centerX>320) return 0;
	if(centerY>240) return 0;
	//delay(10);
	return 1;
}


void WeImageRecognition::setLabColor1(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x06);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(0x00);
	_WeImageRecognition.write_byte(minL);
	_WeImageRecognition.write_byte(maxL);
	_WeImageRecognition.write_byte(minA);
	_WeImageRecognition.write_byte(maxA);
	_WeImageRecognition.write_byte(minB);
	_WeImageRecognition.write_byte(maxB);	
	delay(10);
}
void WeImageRecognition::setLabColor2(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x06);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(0x01);
	_WeImageRecognition.write_byte(minL);
	_WeImageRecognition.write_byte(maxL);
	_WeImageRecognition.write_byte(minA);
	_WeImageRecognition.write_byte(maxA);
	_WeImageRecognition.write_byte(minB);
	_WeImageRecognition.write_byte(maxB);	
	delay(10);
}
void WeImageRecognition::setLabColor3(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x06);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(0x02);
	_WeImageRecognition.write_byte(minL);
	_WeImageRecognition.write_byte(maxL);
	_WeImageRecognition.write_byte(minA);
	_WeImageRecognition.write_byte(maxA);
	_WeImageRecognition.write_byte(minB);
	_WeImageRecognition.write_byte(maxB);	
	delay(10);
}
void WeImageRecognition::setLabColor4(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x06);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(0x03);
	_WeImageRecognition.write_byte(minL);
	_WeImageRecognition.write_byte(maxL);
	_WeImageRecognition.write_byte(minA);
	_WeImageRecognition.write_byte(maxA);
	_WeImageRecognition.write_byte(minB);
	_WeImageRecognition.write_byte(maxB);	
	delay(10);
}
void WeImageRecognition::setLabColor5(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x06);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(0x04);
	_WeImageRecognition.write_byte(minL);
	_WeImageRecognition.write_byte(maxL);
	_WeImageRecognition.write_byte(minA);
	_WeImageRecognition.write_byte(maxA);
	_WeImageRecognition.write_byte(minB);
	_WeImageRecognition.write_byte(maxB);	
	delay(10);
}

bool WeImageRecognition::getAppColorPosition(uint8_t num)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return  0;
	num=num-1;
    _WeImageRecognition.write_byte(0x07|num<<5);
//    if(_WeImageRecognition.reset()!=0) 
//		return  0;
//	_WeImageRecognition.write_byte(mun);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<6;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
	pixels=(uartData[4]<<8)|uartData[5];
	if(centerX>320) return 0;
	if(centerY>240) return 0;
	//delay(10);
	return 1;
}

void WeImageRecognition::setLineFollowerMode(void)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x08);
	delay(3000);
}
void WeImageRecognition::setLineFollowerThreshold(uint8_t min,uint8_t max)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x0e);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(min);
	_WeImageRecognition.write_byte(max);
	delay(10);
}

bool WeImageRecognition::getLineFollowerAngle(void)
{
	if(_WeImageRecognition.reset()!=0) 
			return	0;
	_WeImageRecognition.write_byte(0x0f);
	_WeImageRecognition.respond();
	angle=_WeImageRecognition.read_byte();
	if (angle==125) return 0;
	//delay(10);
	return 1;

}
bool WeImageRecognition::getLineFollowerAxis(void)
{
	if(_WeImageRecognition.reset()!=0) 
		return  0;
    _WeImageRecognition.write_byte(0x09);
	_WeImageRecognition.respond();
   	linex1=_WeImageRecognition.read_byte();
	if (linex1==0xff) return 0;
	linex2=_WeImageRecognition.read_byte();
	linex3=_WeImageRecognition.read_byte();
	linex4=_WeImageRecognition.read_byte();
	linex5=_WeImageRecognition.read_byte();	
	return 1;
}

void WeImageRecognition::setPixelsThreshold(uint8_t num)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x0a);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(num);
	delay(10);
}

bool WeImageRecognition::getColorAllPosition(uint8_t num)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return  0;
	num=num-1;
    _WeImageRecognition.write_byte(0x0b|num<<5);
 //  if(_WeImageRecognition.reset()!=0) 
//		return  0;
//	_WeImageRecognition.write_byte(mun);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<15;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
	pixels=(uartData[4]<<8)|uartData[5];
	frameX=(uartData[6]<<8)|uartData[7];
	frameY=(uartData[8]<<8)|uartData[9];
	width=(uartData[10]<<8)|uartData[11];
	high=(uartData[12]<<8)|uartData[13];
	rotation=uartData[14];
	density=(float)pixels/(float)(width*high);

	//delay(10);
	return 1;
}

bool WeImageRecognition::getAppColorAllPosition(uint8_t num)
{ 
	if(_WeImageRecognition.reset()!=0) 
		return  0;
	num=num-1;
    _WeImageRecognition.write_byte(0x0c|num<<5);
 //   if(_WeImageRecognition.reset()!=0) 
//		return  0;
//	_WeImageRecognition.write_byte(mun);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<15;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
	pixels=(uartData[4]<<8)|uartData[5];
	frameX=(uartData[6]<<8)|uartData[7];
	frameY=(uartData[8]<<8)|uartData[9];
	width=(uartData[10]<<8)|uartData[11];
	high=(uartData[12]<<8)|uartData[13];
	rotation=uartData[14];
	density=(float)pixels/(float)(width*high);
	//delay(10);
	return 1;
}

void WeImageRecognition::resetColorMode(uint8_t time)  //1-20
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x0d);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(time);
	delay(6000);
}
bool WeImageRecognition::getFacePositon(void)
{
	if(_WeImageRecognition.reset()!=0) 
		return  0;
    _WeImageRecognition.write_byte(0x10);
	_WeImageRecognition.respond();
   	uartData[0]=_WeImageRecognition.read_byte();
	if (uartData[0]==0xff) return 0;
	for(uint8_t i=1;i<4;i++)
	{
	   uartData[i]=_WeImageRecognition.read_byte();
	}
	centerX=(uartData[0]<<8)|uartData[1];
	centerY=(uartData[2]<<8)|uartData[3];
    if(centerX>320) return 0;
	if(centerY>240) return 0;
	return 1;
}
void WeImageRecognition::fastMode(bool mode)
{
	if(_WeImageRecognition.reset()!=0) 
		return  ;
    _WeImageRecognition.write_byte(0x11);
	if(_WeImageRecognition.reset()!=0) 
		return  ;
	_WeImageRecognition.write_byte(mode);
}

uint8_t WeImageRecognition::getTrafficSigns(void)
{
	uint16_t frame_size,red_X,red_Y;
	float density;
	uint8_t Tnum=3;
	if(getAppColorAllPosition(4)==1)
	{
		frame_size=high*width;
		density=(float)pixels/frame_size;
		//Serial.println(pixels);
		
		if((density>0.23)&&(density<0.35)&&(pixels>2000))
		{
			//Serial.println(pixels);
			red_X=centerX;
			red_Y=centerY;
			while(Tnum)
			{
				Tnum--;
				//Serial.println(Tnum);
				if(getAppColorAllPosition(5)==1)
				{
					
					//Serial.println(pixels);
					//Serial.print(abs(centerX-red_X));
					//Serial.println('-');
					//Serial.print(abs(centerY-red_Y));
					if((abs(centerX-red_X)<30)&&(abs(centerY-red_Y)<30)&&(pixels>2000))
					{	
						//Serial.print(abs(centerY-red_Y));
						frame_size=high*width;
				        density=(float)pixels/frame_size;
						//Serial.print(rotation);
						//Serial.print('-');
						//Serial.println(density);
						if((density>0.57)&&(density<0.64)) return 1;
						if((density>0.51)&&(density<0.57)&&(rotation==0)) return 4;
						if((density>0.51)&&(density<0.57)&&(rotation==2)) return 3;
						if((density>0.46)&&(density<0.50)) return 5;
						if((density>0.40)&&(density<0.45)) return 2;						
								
						return 0;
					}
				}
			}
		}
		return 0;		
	}
	return 0;
}
void WeImageRecognition::setCardSignsMode(uint8_t num)  //num<=20
{
	resetColorMode(num);
	setLabColor4(10, 75, 25, 85, -20, 70);
	setLabColor5(20, 95, -20, 36, -60, -15);
	//setLabColor5(20, 50, -10, 36, -60, -20);
	setPixelsThreshold(100);
}
uint8_t WeImageRecognition::getCardSigns1(void)
{
	uint16_t frame_size,red_X,red_Y;
	float density;
	uint8_t Tnum=3;
	if(getAppColorAllPosition(4)==1)
	{
		frame_size=high*width;
		density=(float)pixels/frame_size;		
		if((density>0.20)&&(density<0.30)&&(pixels>3000))
		{

			red_X=centerX;
			red_Y=centerY;
			while(Tnum)
			{
				Tnum--;
				//Serial.println(Tnum);
				if(getAppColorAllPosition(5)==1)
				{

					if((abs(centerX-red_X)<30)&&(abs(centerY-red_Y)<30)&&(pixels>3000))
					{	

						frame_size=high*width;
				        density=(float)pixels/frame_size;
			
						if((density>0.45)&&(density<0.52)) return 1;   //Triangle
                        if((density>0.53)&&(density<0.61)) return 2;   //Cross
                        if((density>0.63)&&(density<0.7)) return 3;	   //Tick			
								
						return 0;
					}
				}
			}
		}
		return 0;		
	}
	return 0;
}






void WeImageRecognition::setMode(uint8_t mode)
{
	if(mode == 0){
		setAutoTrackingMode();
	}else{
		setLineFollowerMode();
	}
}

bool WeImageRecognition::updateMode(uint8_t mode)
{
	if(mode == 0){
		return getAutoPosition();
	}else{
		return getLineFollowerAngle();
	}
}

uint16_t WeImageRecognition::getValue(uint8_t type)
{
	if(type == 0){
		return centerX;
	}
	if(type == 1){
		return centerY;
	}
	if(type == 2){
		return pixels;
	}
	if(type == 3){
		return angle;
	}
	return 0;
}
