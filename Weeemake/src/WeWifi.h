
#ifndef WeWifi_H
#define WeWifi_H

#include "WePort.h"


class WeWifi
{
public:
  char rx_buffer[20]={0};
  char IP_addr[16]={0};
  uint8_t link_IP;
  WeWifi(uint8_t port=0);
  void reset(uint8_t port=0);

  void setWIFIinfo(char *ssid, char *pwd);
  void initAP(uint8_t chl=11);
  void CWSAP(uint8_t chl,uint8_t ecn);
  void CIPMux(bool mode);
  void initSTA(void);
  bool CWJAP(void);
  void initTCP(char *ip,uint16_t port,uint8_t linkID=0);
  void CIPStart(char *ip,uint16_t port,uint8_t linkID=0);
  void initSlave(char *ip,uint16_t port);
  void CWMode(uint8_t mode);
  void setPort(uint16_t port);
  bool write(const char *words,uint8_t linkID=0); 
  bool write(String words,uint8_t linkID=0); 
  bool readString(void);
  bool readIP(void);
  void restore(void);

  
private:
	WeOneWire _WeWifi;
	uint16_t last_time,eport;
};

#endif

