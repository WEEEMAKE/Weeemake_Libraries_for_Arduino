#include "WeLEDPanelModuleMatrix.h"

WeLEDPanelModuleMatrix7_21::WeLEDPanelModuleMatrix7_21(uint8_t port)
:WeLEDPanelModuleMatrix(port, 21, 7)
{}

WeLEDPanelModuleMatrix5_14::WeLEDPanelModuleMatrix5_14(uint8_t port)
:WeLEDPanelModuleMatrix(port, 14, 5)
{}

WeLEDPanelModuleMatrix::WeLEDPanelModuleMatrix(uint8_t port, uint8_t width, uint8_t height)
:panel_width(width)
,panel_height(height)
{
  _WeLEDPanel.reset(port);
}

void WeLEDPanelModuleMatrix::reset(uint8_t port)
{
  _WeLEDPanel.reset(port);
}

void WeLEDPanelModuleMatrix::setBrightness(uint8_t Bright)
{
    if((uint8_t)Bright>7)
    {
        Bright = 0x07;
    }

    if((uint8_t)Bright >=0)
    {
        Bright = 0x88 | (uint8_t)Bright; 
    }

    if(_WeLEDPanel.reset()!=0)
    return;
     _WeLEDPanel.write_byte(0x06); 
     _WeLEDPanel.reset();
     _WeLEDPanel.write_byte(Bright);
     delayMicroseconds(3000);
}

void WeLEDPanelModuleMatrix::clearScreen(void)
{
  uint8_t i;
  for (i=0;i<panel_width;i++)
  {
  	 Display_Buffer[i]=0;
  }
   if(_WeLEDPanel.reset()!=0)
   return;
  _WeLEDPanel.write_byte(0x05);
  delayMicroseconds(5000);
}
void WeLEDPanelModuleMatrix::writePanelData(void)
{
   if(_WeLEDPanel.reset()!=0)
   return;
  _WeLEDPanel.write_byte(0x02);
  if(_WeLEDPanel.reset()!=0)
  {
     delayMicroseconds(3000);
     return;
  }
  for (int i=0;i<panel_width;i++)
  {
    _WeLEDPanel.write_byte(Display_Buffer[i]);
  }
  delayMicroseconds(3000);
}
/*
void WeLEDPanelModuleMatrix7_21::showPanel(void)
{ 
  _WeLEDPanel.reset();
  _WeLEDPanel.write_byte(0x04);
  delayMicroseconds(3000);
}
*/
void WeLEDPanelModuleMatrix5_14::showBitmap2(int8_t x, int8_t y, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13)
{
  uint8_t data[14] = {v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13};
  showBitmap(x, y, data);
}

void WeLEDPanelModuleMatrix7_21::showBitmap2(int8_t x, int8_t y, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15, uint8_t v16, uint8_t v17, uint8_t v18, uint8_t v19, uint8_t v20)
{
  uint8_t data[21] = {v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20};
  showBitmap(x, y, data);
}


void WeLEDPanelModuleMatrix::showBitmap(int8_t x, int8_t y, uint8_t *data)
	{
	  const int w = panel_width;
	  const int h = panel_height;
	  if(x <= -w || x >= w || y <= -h || y >= h){
		clearScreen();
		return;
	  }
	  _WeLEDPanel.reset();
	  _WeLEDPanel.write_byte(0x02);
	  _WeLEDPanel.reset();
	  for(int i=-x; i<w-x; i++){
		uint8_t value = 0;
		if(0 <= i && i < w){
		  if(y >= 0){
			value = data[i] << y;
		  }else{
			value = data[i] >> -y;
		  }
		}
		_WeLEDPanel.write_byte(value);
	  }
	}

void WeLEDPanelModuleMatrix::showLine(uint8_t x,uint8_t buffer)
{
  if(x < 0 || x >= panel_width){
  	return;
  }
  if(_WeLEDPanel.reset()!=0)
   return;
  _WeLEDPanel.write_byte(0x03);
  if (_WeLEDPanel.reset()!=0)
   return;
  _WeLEDPanel.write_byte(x);
  _WeLEDPanel.write_byte(buffer);
 // Display_Buffer[x]=buffer;
//  delayMicroseconds(1000);
}
void WeLEDPanelModuleMatrix::setDot(uint8_t x,uint8_t y,bool isOn)
{
  if(isOn){
    turnOnDot(x, y);
  }else{
    turnOffDot(x, y);
  }
}
void WeLEDPanelModuleMatrix::turnOnDot(uint8_t x,uint8_t y)
{ 
   if(x>(panel_width-1)||y>(panel_height-1))
   	return;
   Display_Buffer[x]=Display_Buffer[x]|(0x01<<(y));   
   showLine(x,Display_Buffer[x]);

}

void WeLEDPanelModuleMatrix::turnOffDot(uint8_t x,uint8_t y)
{ 
   if(x>(panel_width-1)||y>(panel_height-1))
   return;
   Display_Buffer[x]=Display_Buffer[x]&(~(0x01<<(y)));
   showLine(x,Display_Buffer[x]);
}

void WeLEDPanelModuleMatrix::showChar(int8_t X_position, int8_t Y_position, String str)
{
	showChar(X_position, Y_position, str.c_str());
}
void WeLEDPanelModuleMatrix::showChar(int8_t X_position, int8_t Y_position, const char *str)
{
	
	for(int i=0;; i++){
		int x = X_position + i * 6;
		if(x <= -6){
			continue;
		}
		if(x >= panel_width){
			break;
		}
		char v = str[i];
		if(v == 0){
			while(x < panel_width)
				showLine(x++, 0);
			break;
		}
		if(v <= 32 || v >= 127){
			writeChar(x, 0, 3);
			continue;
		}
		writeChar(x, Y_position, v-33);
	}
	while(X_position-- > 0){
		showLine(X_position, 0);
	}
}

void WeLEDPanelModuleMatrix::showClock(uint8_t hour, uint8_t minute, bool point_flag)
{
   writeChar(-1, 0, hour / 10 + 15);
   writeChar( 4, 0, hour % 10 + 15); 
   writeChar(11, 0, minute / 10 + 15);   
   writeChar(16, 0, minute % 10 + 15);
   showLine( 10, point_flag ? 0x14 : 0);
}

void WeLEDPanelModuleMatrix::writeChar(int8_t X_position,int8_t Y_position,uint8_t buffer)
{
    if(_WeLEDPanel.reset())return;
    _WeLEDPanel.write_byte(0x07);
    if(_WeLEDPanel.reset())return;
    _WeLEDPanel.write_byte(X_position);
    _WeLEDPanel.write_byte(Y_position);
	_WeLEDPanel.write_byte(buffer);
	delayMicroseconds(3000);
}
	

void WeLEDPanelModuleMatrix::showNum(float value)
{
  uint8_t tempBuf[10]={0};
  int buf[4]={0};
  uint8_t isNeg=0;
  uint8_t int_num = 0;
  uint8_t bit_num = 0;
  uint8_t temp_num = 0;
  uint8_t comma_flag=0;
  double number = value;
  if(number>=9999)
  {
     writeChar(-1,0,9+15);
	 writeChar(4,0,9+15);
	 writeChar(9,0,9+15);
	 writeChar(14,0,9+15);
	 showLine(20,0x00);
  }
  else if(number<= -999)
  {
    // showLine(-1,0x08);
	 
	 writeChar(4,0,9+15);
	 writeChar(10,0,9+15);
	 writeChar(15,0,9+15);
	 showLine(0,0x08);
	 showLine(1,0x08);
	 showLine(2,0x08);
	 showLine(3,0x08);
   }
  else if (number==0)
  {
     writeChar(0,0,3);
	 writeChar(5,0,3);
	 writeChar(10,0,3);
	 writeChar(15,0,15);
  }
   else
   {
     if (number<0)
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
     if(isNeg==1)         //
     {
       writeChar(-1,0,12);     //'-'
       writeChar(4,0,buf[0]+15);

	   for(int i=0;i<3;i++)
	   {
	     if(comma_flag-1<i)
	     {
	        writeChar(6+i*5,0,buf[i]+15);
	     }
		 else
		 {
		    writeChar(4+i*5,0,buf[i]+15);
		 }
	   }
	   showLine(5+5*comma_flag,0x40);
     }
	 else
	 {
	   writeChar(-1,0,buf[0]+15);
	   for(int i=0;i<4;i++)
	   {
	     if(comma_flag-1<i)
	     {
	        writeChar(1+i*5,0,buf[i]+15);
	     }
		 else
		 {
		    writeChar(-1+i*5,0,buf[i]+15);
		 }
	   }
       showLine(5*comma_flag,0x40); 
	 }

  }
     
} 
 

void WeLEDPanelModuleMatrix7_21::showNum(float value)
{
  uint8_t tempBuf[10]={0};
  int buf[4]={0};
  uint8_t isNeg=0;
  uint8_t int_num = 0;
  uint8_t bit_num = 0;
  uint8_t temp_num = 0;
  uint8_t comma_flag=0;
  double number = value;
  if(number>=9999)
  {
     writeChar(-1,0,9+15);
   writeChar(4,0,9+15);
   writeChar(9,0,9+15);
   writeChar(14,0,9+15);
   showLine(20,0x00);
  }
  else if(number<= -999)
  {
   writeChar(4,0,9+15);
   writeChar(10,0,9+15);
   writeChar(15,0,9+15);
   showLine(0,0x08);
   showLine(1,0x08);
   showLine(2,0x08);
   showLine(3,0x08);
   }
  else if (number==0)
  {
     writeChar(0,0,3);
   writeChar(5,0,3);
   writeChar(10,0,3);
   writeChar(15,0,15);
  }
  else
  {
     if (number<0)
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

    if(isNeg==1)         //
    {
      if (number >= 100)
      {
        temp_num = 3;
        writeChar(-1,0,12);     //'-'
      }
      else if (number >= 10)
      {
        if (buf[2]!=0)
        {
          temp_num = 3;
          writeChar(-1,0,12);     //'-'
        }
        else
        {
          temp_num =2;
          writeChar(4,0,12);     //'-'
        }
      }
      else if (number >=1)
      {
        if (buf[2]!=0)
        {
          temp_num =3;
          writeChar(-1,0,12);     //'-'
        }
        else if (buf[2]==0&&buf[1]!=0)
        {
          temp_num = 2;
          writeChar(4,0,12);     //'-'
        }
        else
        {
          temp_num = 1;
          writeChar(9,0,12);     //'-'
        }
      }
      else
      {
        if (buf[2]!=0)
        {
          temp_num =3;
          writeChar(-1,0,12);     //'-'
        }
        else if (buf[2]==0&&buf[1]!=0)
        {
          temp_num = 2;
          writeChar(4,0,12);     //'-'
        }
        else
        {
          temp_num = 1;
          writeChar(9,0,12);     //'-'
        }
      }
       
      for(int i=0;i<temp_num;i++)
      {
        if (temp_num == 3)
        {
           if(comma_flag-1<i)
           {
              writeChar(6+i*5,0,buf[i]+15);
           }
           else
           {
              writeChar(4+i*5,0,buf[i]+15);
           }
           if (number>=100)
           {
             showLine(20,0x00);
           }
           else
           {
            showLine(5+5*comma_flag,0x40);
           }
        }
        else if (temp_num == 2)
        {
            if(comma_flag-1<i)
           {
              writeChar(6+i*5+5,0,buf[i]+15);
           }
           else
           {
              writeChar(4+i*5+5,0,buf[i]+15);
           }
           writeChar(-1,0,3);
           if (number>=10)
           {
             showLine(20,0x00);
           }
           else
           {
            showLine(5+5*comma_flag+5,0x40);
           }
        }
        else
        {
            if(comma_flag-1<i)
           {
              writeChar(6+i*5+10,0,buf[i]+15);
           }
           else
           {
              writeChar(4+i*5+10,0,buf[i]+15);
           }
           writeChar(4,0,3);
        } 
      }
  }   
  
   else
   {
     if (number>=1000)
     {
       temp_num = 4;
     }
     else if(number>=100)
     {
        if(buf[3]!=0)
        {
          temp_num = 4;
        }
        else
        {
          temp_num =3;
        }
     }
     else if(number>=10)
     {
         if(buf[3]!=0)
         {
           temp_num = 4;
         }
         else if(buf[3]==0 && buf[2]!=0)
         {
           temp_num = 3;
         }
         else
         {
           temp_num = 2;
         }
         
     }
     else if(number>=1)
     {
       if(buf[3]!=0)
       {
         temp_num = 4;
       }
       else if(buf[3]==0 && buf[2]!=0)
       {
         temp_num = 3;
       }
       else if(buf[3]==0 && buf[2]==0 && buf[1]!=0)
       {
         temp_num = 2;
       }
       else
       {
        temp_num = 1;
       }
     }
     else
     {
        if(buf[3]!=0)
       {
         temp_num = 4;
       }
       else if(buf[3]==0 && buf[2]!=0)
       {
         temp_num = 3;
       }
       else if(buf[3]==0 && buf[2]==0 && buf[1]!=0)
       {
         temp_num = 2;
       }
       else
       {
          temp_num = 1;
       }
     }
     
     for(int i=0;i<temp_num;i++)
     {
      if(temp_num == 4)
      {
        if(comma_flag-1<i)
         {
            writeChar(1+i*5,0,buf[i]+15);
         }
         else
         {
          writeChar(-1+i*5,0,buf[i]+15);
         }
         if(number>=1000)
         {
           showLine(20,0x00);
         }
         else
         {
            showLine(5*comma_flag,0x40);
         } 
      }
      else if(temp_num == 3)
      {
      	writeChar(-1,0,3);
          if(comma_flag-1<i)
         {
            writeChar(1+i*5+5,0,buf[i]+15);
         }
         else
         {
          writeChar(-1+i*5+5,0,buf[i]+15);
         }
         if (number>=100)
         {
           showLine(20,0x00);
         }
         else
         {
            showLine(5*comma_flag+5,0x40);
         }
      }
      else if(temp_num == 2)
      {
		writeChar(-1,0,3);
		writeChar(4,0,3);
		if(comma_flag-1<i)
		{
			writeChar(1+i*5+10,0,buf[i]+15);
		}
		else
		{
			writeChar(-1+i*5+10,0,buf[i]+15);
		}
		if (number>=10)
		{
			showLine(20,0x00);
		}
		else
		{
			showLine(5*comma_flag+10,0x40);
		}
	  }
	  else 
	  {
		writeChar(-1,0,3);
		writeChar(4,0,3);
		writeChar(9,0,3);
		if(comma_flag-1<i)
		{
			writeChar(1+i*5+15,0,buf[i]+15);
		}
		else
		{
			writeChar(-1+i*5+15,0,buf[i]+15);
		}
		if (number>=1)
		{
			showLine(20,0x00);
		}
       }   
   	}
	}
  } 
} 

void WeLEDPanelModuleMatrix5_14::showNum(float value)
{
  uint8_t tempBuf[10]={0};
  int buf[4]={0};
  uint8_t isNeg=0;
  uint8_t int_num = 0;
  double number = value;
  if(number>=999)
  {
      writeChar(-1,0,9+15);
	    writeChar(4,0,9+15);
	    writeChar(9,0,9+15);
	    //writeChar(14,0,9+15);
	    //showLine(20,0x00);
  }
  else if(number<= -99)
  {
	 writeChar(0,0,12);
	 writeChar(4,0,9+15);
	 writeChar(9,0,9+15);
  }
  else if (number==0) 
  {
    writeChar(0,0,3);
    writeChar(4,0,3);
    writeChar(9,0,15);
  }
   else
   {
     if (number<0)
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
    buf[4]=tempBuf[int_num+3];
	 }
     else
     {
           buf[0]=tempBuf[3];
		buf[1]=tempBuf[4];
		buf[2]=tempBuf[5];
    buf[3]=tempBuf[6];
     }
     if(isNeg==1)         //
     {
        //writeChar(-1,0,12);     //'-'
        if (number >= 10)
        {
          writeChar(-1,0,12);     //'-'
          writeChar(4,0,buf[0]+15);
          if (buf[0] ==1)
          {
             writeChar(8,0,buf[1]+15);
          }
          else
          {
            writeChar(9,0,buf[1]+15);
          }  
        }
        else if (number >= 1)
        {
            if (buf[1] == 0 && buf[2] == 0 )
            {
            	writeChar(0,0,3);
              if (buf[0]==3 || buf[0] == 7 )
              {
                writeChar(8,0,buf[0]+15);
                showLine(6,0x04);
                showLine(7,0x04);
                showLine(8,0x04);
              }
              else if (buf[0] == 4)
              {
                writeChar(8,0,buf[0]+15);
                showLine(5,0x04);
                showLine(6,0x04);
                showLine(7,0x04);
              }
              else
              {
                 writeChar(0,0,3);     
                 writeChar(5,0,12);     //'-'
                writeChar(9,0,buf[0]+15);
              }

            }
            else if (buf[0] == 1)
            { 
                if (buf[1] == 1 || buf[1] == 2)
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  writeChar(9,0,buf[1]+15);
                  showLine(8,0x10);
                }
                else if (buf[1] == 3)
                {
                  writeChar(0,0,12);     //'-'
                  writeChar(4,0,buf[0]+15);
                  writeChar(9,0,buf[1]+15);
                  showLine(9,0x10);
                }
                else if (buf[1] == 4)
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  writeChar(8,0,buf[1]+15);
                  showLine(8,0x10);
                }
                else if (buf[1] == 7)
                {
                  writeChar(0,0,12);     //'-'
                  writeChar(4,0,buf[0]+15);
                  writeChar(9,0,buf[1]+15);
                  showLine(9,0x10);
                }
                else
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  writeChar(9,0,buf[1]+15);
                  showLine(8,0x10);
                }
            }
            else if (buf[0] == 2)
            {
                if (buf[1] == 2 || buf[1] == 4 || buf[1] == 5)
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  if (buf[1] == 2 || buf[1] == 5)
                  {
                    writeChar(9,0,buf[1]+15);
                  }
                  else
                  {
                    writeChar(8,0,buf[1]+15);
                  }
                  showLine(7,0x02);
                  showLine(8,0x10);
                }
                else if (buf[1] == 1)
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  writeChar(10,0,buf[1]+15);
                  showLine(9,0x10);
                }
                else 
                {
                  writeChar(-1,0,12);     //'-'
                  writeChar(3,0,buf[0]+15);
                  writeChar(9,0,buf[1]+15);
                  showLine(9,0x10);
                }
            }
            else if (buf[0] == 3)
            {
            	if (buf[1] == 3 || buf[1] == 4 || buf[1] == 7)
            	{
            		writeChar(2,0,buf[0]+15);
              		writeChar(8,0,buf[1]+15);
              		showLine(0,0x04);
              		showLine(1,0x04);
              		showLine(2,0x04);
              		showLine(8,0x10);
            	}
            	else //if (/* condition */)
            	{
            		writeChar(2,0,buf[0]+15);
              		writeChar(9,0,buf[1]+15);
              		showLine(0,0x04);
              		showLine(1,0x04);
              		showLine(2,0x04);  
              		showLine(8,0x10);
            	}
          	}
          	else
          	{
            	if (buf[1] ==0 )
            	{
              		writeChar(9,0,buf[0]+15);
            	}
            	else
            	{
              		writeChar(-1,0,12);     //'-'
              		writeChar(3,0,buf[0]+15);
              	if(buf[1] == 1 || buf[1] == 3)
              	{
                 	writeChar(10,0,buf[1]+15);
                 	showLine(9,0x10);
              	}
              	else
              	{
                	writeChar(9,0,buf[1]+15);
                	showLine(9,0x10);
              	}

              	if (buf[1] == 2 || buf[1] == 5)
              	{
                	writeChar(9,0,buf[1]+15);
                	showLine(8,0x10);
              	}
              	else
              	{
                	writeChar(9,0,buf[1]+15);
                	showLine(9,0x10);
              	}
            }
        }
    }
     }
	 else
	 {
          if (number >=100)
          {
            if (buf[0] == 1)
            {
              writeChar(0,0,buf[0]+15);
            }
            else
            {
              writeChar(-1,0,buf[0]+15);
            }
            
            writeChar(4,0,buf[1]+15);
            writeChar(9,0,buf[2]+15);
          }
          else if (number >= 10)
          {
            writeChar(-1,0,buf[0]+15);
            if (buf[0] == 1)
            {
              writeChar(3 ,0,buf[1]+15);
            }
            else
            {
              writeChar(4 ,0,buf[1]+15);
            }
            
            if (buf[2] == 1)
            {
              writeChar(10,0,buf[2]+15);
              showLine(9,0x10);
            }
            else
            {
              writeChar(9,0,buf[2]+15);
              showLine(9,0x10);
            }
            
          }
          else if (number >= 1)
          {
            writeChar(-1,0,buf[0]+15);
            if (buf[1] == 1)
            {
              writeChar(5,0,buf[1]+15);
            }
            else
            {
               writeChar(4,0,buf[1]+15);
            }
           
            if (buf[2] == 1)
            {
              writeChar(10,0,buf[2]+15);
            }
            else
            {
             writeChar(9,0,buf[2]+15);
             
            }
            showLine(4,0x10);
          }
          else
          {
            writeChar(-1,0,buf[0]+15);
            if (buf[1] == 1)
            {
              writeChar(5,0,buf[1]+15);
            }
            else
            {
               writeChar(4,0,buf[1]+15);
            }
           
            if (buf[2] == 1)
            {
              writeChar(10,0,buf[2]+15);
              //showLine(5,0x10);
            }
            else
            {
             writeChar(9,0,buf[2]+15);
             
            }
            showLine(4,0x10);
          }
	 }
  }    
} 



