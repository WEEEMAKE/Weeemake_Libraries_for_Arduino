#include "We7SegmentDisplay.h"


We7SegmentDisplay::We7SegmentDisplay(uint8_t port)
{
  reset(port);
}
void We7SegmentDisplay::reset(uint8_t port)
{
	_We7SegmentDisplay.reset(port);
	resetFlag = true;
	last_number = 10000;
}

void We7SegmentDisplay::sendNumber(void)
{
	if(_We7SegmentDisplay.reset()!=0)
       return ;
    _We7SegmentDisplay.write_byte(0x02);
    if(_We7SegmentDisplay.reset()!=0)
       return ;
	_We7SegmentDisplay.write_byte(_number1);
	_We7SegmentDisplay.write_byte(_number2);
	_We7SegmentDisplay.write_byte(_number3);
	_We7SegmentDisplay.write_byte(_number4);
}
void We7SegmentDisplay::showChar(uint8_t Addr, uint8_t Data)
{
     switch(Addr)
     {
        case 1: _number1=Data;break;
		case 2: _number2=Data;break;
		case 3: _number3=Data;break;
		case 4: _number4=Data;break;
     }
	 sendNumber();
}

void We7SegmentDisplay::showNumber(float value)
{    
	if(resetFlag){
		resetFlag = false;
	}else if(last_number == value){
		return;
	}
	 last_number = value;

     uint8_t tempBuf[10]={0};
     int buf[4]={0};
     uint8_t isNeg=0;
     uint8_t int_num = 0;
     uint8_t comma_flag=0;
     double number = value;
     if (number>=9999)
     {
        _number1=0x09;
		_number2=0x09;
		_number3=0x09;
		_number4=0x09;
     }
	 else if(number<=-999)
	 {
	    _number1=0x10;    //"-"
		_number2=0x09;
		_number3=0x09;
		_number4=0x09;
	 }
	 else if(number==0)
	 {
	    _number1=0x40;   //不显示
		_number2=0x40;
		_number3=0x40;
		_number4=0x00;
	 }
	 else
	 {
	    if(number<0)
	    {
	      number = -number;
          isNeg = 1;
	    }
		tempBuf[0]=number/1000;
	    tempBuf[1]=(int)number%1000/100;
	    tempBuf[2]=(int)number%100/10;
	    tempBuf[3]=(int)number%10;
	    tempBuf[4]=(int)(number*10)%10;
	    tempBuf[5]=(int)(number*100)%10;
	    tempBuf[6]=(int)(number*1000)%10;
	    while(tempBuf[int_num]==0)
	    {
	       int_num++;
	    }
		if(number>=1)
	    {	    
	 	   buf[0]=tempBuf[int_num];
		   buf[1]=tempBuf[int_num+1];
	   	   buf[2]=tempBuf[int_num+2];
		   buf[3]=tempBuf[int_num+3];
		   comma_flag=4-int_num;
	    }
        else
        {
           buf[0]=tempBuf[3];
		   buf[1]=tempBuf[4];
		   buf[2]=tempBuf[5];
		   buf[3]=tempBuf[6];
		   comma_flag=1;
        }
		if(isNeg==1)
		{
		   _number1=0x10;    //"-"
		   _number2=buf[0];
		   _number3=buf[1];
		   _number4=buf[2];
		   if (comma_flag==2)
		   _number3 =_number3|0x20; //"."
		   else if (comma_flag==1)
		   _number2 =_number2|0x20; //"."
		}
		else
		{
		   _number1=buf[0];    
		   _number2=buf[1];
		   _number3=buf[2];
		   _number4=buf[3];
		   if (comma_flag==3)
		      _number3=_number3|0x20; //"."
		   else if (comma_flag==2)
		      _number2=_number2|0x20; //"."
		   else if (comma_flag==1)
		      _number1=_number1|0x20; //"."
		}
		
	 }

	 
  if((_number1&0x20)==0x20)     //去除小数点后多余0位
  {
     if ((_number2==0)&&(_number3==0)&&(_number4==0))
     { 
        
        _number4=_number1&0x0f;
		_number1=0x40;
		_number2=0x40;
		_number3=0x40;
     }
	 else if((_number3==0)&&(_number4==0))
	 {
	    _number4=_number2;
		_number3=_number1;
		_number1=0x40;
		_number2=0x40;
	 //   _number3=_number3|0x20; //"."
	 }
	 else if (_number4==0)
	 {
	    _number4=_number3;
		_number3=_number2;
		_number2=_number1;
		_number1=0x40;
	//	_number2=_number2|0x20; //"."
	 }
  }
  else if((_number2&0x20)==0x20)
  {
     if ((_number3==0)&&(_number4==0))
     {
        _number4=_number2&0x0f;
		_number3=_number1;
		_number1=0x40;
		_number2=0x40;
     }
	 else if (_number4==0)
	 {
	    _number4=_number3;
		_number3=_number2;
		_number2=_number1;
		_number1=0x40;
	
	 }
  }
  else if((_number3&0x20)==0x20)
  {
     if (_number4==0)
     {
        _number4=_number3&0x0f;
		_number3=_number2;
		_number2=_number1;
		_number1=0x40;
     }
  }
  sendNumber();
}



