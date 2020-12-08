#include "WeWifi.h"
#include <avr/wdt.h>

WeWifi::WeWifi(uint8_t port)
{
   _WeWifi.reset(port);
}
void WeWifi::reset(uint8_t port)
{
   _WeWifi.reset(port);
}

void WeWifi::setWIFIinfo(char *ssid, char *pwd)  //wifi名称，密码(8-64个字节)
{
   if(_WeWifi.reset()!=0)
    	return ;
    _WeWifi.write_byte(0x03);
	if(_WeWifi.reset()!=0)
    	return ;
	while(*ssid)
    {
        _WeWifi.write_byte(*ssid);
		++ssid;
	}
	_WeWifi.write_byte(0x00);
	
	if(_WeWifi.reset()!=0)
    	return ;
	_WeWifi.write_byte(0x04);
	if(_WeWifi.reset()!=0)
    	return ;
	while(*pwd)
    {
        _WeWifi.write_byte(*pwd);
		++pwd;
	}
	_WeWifi.write_byte(0x00);
}

void WeWifi::initAP(uint8_t chl)
{
	CWMode(2);
	CWSAP(chl,2);
	CIPMux(1);
	setPort(6602);
}

void WeWifi::CWSAP(uint8_t chl,uint8_t ecn)   //通道号(1-13)，加密方式(0、2、3、4)
{
	if(_WeWifi.reset()!=0)
    	return ;
	_WeWifi.write_byte(0x05);
	if(_WeWifi.reset()!=0)
    	return ;
	_WeWifi.write_byte(chl);
	_WeWifi.write_byte(ecn);
	delay(1000);
}

void WeWifi::CIPMux(bool mode)  //0、 单连接 1、多连接
{
   if(_WeWifi.reset()!=0)
    	return ;
	_WeWifi.write_byte(0x0e);
	if(_WeWifi.reset()!=0)
    	return ;	
	_WeWifi.write_byte(mode);
	delay(100);
}

void WeWifi::initSTA(void)
{
	CWMode(1);
    CWJAP();
	CIPMux(1);
	setPort(6602);
}

bool WeWifi::CWJAP(void)
{
	unsigned long time;
	time = millis();

	if(_WeWifi.reset()!=0)
    	return 0;
	_WeWifi.write_byte(0x09);
	
     while(_WeWifi.respond()==1)
	{
		if((millis()-time)>10000)
		return 0;
	}
	return (_WeWifi.read_byte());
}

void WeWifi::initTCP(char *ip,uint16_t port,uint8_t linkID)
{
	CWMode(3);
    CWJAP();
	CIPMux(1);
	CIPStart(ip,port,linkID);
}

void WeWifi::CIPStart(char *ip,uint16_t port,uint8_t linkID)
{
	if(_WeWifi.reset()!=0)
		return ;	
	_WeWifi.write_byte(0x0b);
	if(_WeWifi.reset()!=0)
		return ;
	while(*ip)
    {
        _WeWifi.write_byte(*ip);
		++ip;
	}
	_WeWifi.write_byte(0x00);
	
	if(_WeWifi.reset()!=0)
		return ;	
	_WeWifi.write_byte(0x0c);
	if(_WeWifi.reset()!=0)
		return ;
	_WeWifi.write_byte(port);
	_WeWifi.write_byte(port>>8);
	_WeWifi.write_byte(linkID);
	delay(1000);
}

void WeWifi::initSlave(char *ip,uint16_t port)
{
	CWMode(1);
    CWJAP();
	CIPMux(1);
	CIPStart(ip,port,0);
}

void WeWifi::CWMode(uint8_t mode) //设置当前wifi模式: 1、STA。2、AP。3、AP+STA
{
	if(_WeWifi.reset()!=0)
    return ;
    _WeWifi.write_byte(0x02);
	if(_WeWifi.reset()!=0)
    return ;
    _WeWifi.write_byte(mode);
	delay(500);
}


void WeWifi::setPort(uint16_t port) //端口号
{
//	delay(100);
	if(_WeWifi.reset()!=0)
		return ;
	_WeWifi.write_byte(0x06);
	if(_WeWifi.reset()!=0)
		return ;	
	_WeWifi.write_byte(port);
	_WeWifi.write_byte(port>>8);
	delay(500);
}

bool WeWifi::write(String words,uint8_t linkID)  //linkID 0~4 
{
	return write(words.c_str(), linkID);
}
bool WeWifi::write(const char *words,uint8_t linkID)  //linkID 0~4 
{
	unsigned long time;
	time = millis();

	if(_WeWifi.reset()!=0)
		return 0;
	_WeWifi.write_byte(0x07);
	if(_WeWifi.reset()!=0)
		return 0;	
	_WeWifi.write_byte(linkID);
	while(*words)
    {
        _WeWifi.write_byte(*words);
		++words;
	}
	_WeWifi.write_byte(0x00);
	
	while(_WeWifi.respond()==1)
	{
		if((millis()-time)>6000)
		return 0;
	}
	return (_WeWifi.read_byte());
}


bool WeWifi::readString(void)
{
	delay(10);
    if(_WeWifi.reset()!=0)
		return 0;	
	_WeWifi.write_byte(0x08);
    _WeWifi.respond();
	link_IP=_WeWifi.read_byte();
	if(link_IP==0xff) return 0;
	for(uint8_t i=0;i<20;i++)
	{
		rx_buffer[i]=_WeWifi.read_byte();
		if(rx_buffer[i]==0) return 1;
	}
	return 0;
}

bool WeWifi::readIP(void)
{
	unsigned long time;
	time = millis();

    if(_WeWifi.reset()!=0)
		return 0;	
	_WeWifi.write_byte(0x0a);
	
    while(_WeWifi.respond()==1)
	{
		if((millis()-time)>6000)
		return 0;
	}
	for(uint8_t i=0;i<20;i++)
	{
		IP_addr[i]=_WeWifi.read_byte();
		if(IP_addr[i]==0)
		{
			delay(10);
			return 1;
		}
	}
	return 0;
}

void WeWifi::restore(void)  //恢复出厂设置
{
	if(_WeWifi.reset()!=0)
			return ;	
	_WeWifi.write_byte(0x0d);

}

/*
void WeWifi::CIPMode(bool mode)    //0、普通传输模式，2、透传模式
{
	if(_WeWifi.reset()!=0)
    return ;
    _WeWifi.write_byte(0x0f);
	if(_WeWifi.reset()!=0)
    return ;
    _WeWifi.write_byte(mode);
	delay(500);
}

void WeWifi::CIPSend(void)    //开启透彻模式下，发送数据
{
	if(_WeWifi.reset()!=0)
    return ;
    _WeWifi.write_byte(0x10);
	delay(100);
}

void WeWifi::write(char *words)  //透传模式下的写数据
{

   if(_WeWifi.reset()!=0)
		return ;
	_WeWifi.write_byte(0x11);
	if(_WeWifi.reset()!=0)
		return ;
	while(*words)
    {
        _WeWifi.write_byte(*words);
		++words;
	}
	_WeWifi.write_byte(0x00);
	
}

*/


