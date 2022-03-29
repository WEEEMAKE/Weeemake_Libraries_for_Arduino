
#ifndef WeWifi_H
#define WeWifi_H

#include "WePort.h"


class WeWifi
{
public:
  uint8_t rx_buffer[300]={0};
  uint16_t rx_len;
  char IP_addr[16]={0};
  uint8_t link_IP;
  WeWifi(uint8_t port=0);
  void reset(uint8_t port=0);

  void setWIFIinfo(char *ssid, char *pwd);
  void initAP(uint8_t chl=11);
  bool CWSAP(uint8_t chl,uint8_t ecn);
  bool CIPMux(bool mode);
  void initSTA(void);
  bool CWJAP(void);
  void initTCP(char *ip,uint16_t port,uint8_t linkID=0);
  bool CIPStart(char *ip,uint16_t port,uint8_t linkID=0);
  bool CIPStart1(char *ip,uint16_t port);
  void initSlave(char *ip,uint16_t port);
  bool CWMode(uint8_t mode);
  bool setPort(uint16_t port);
  bool write(const char *words,uint8_t linkID=0); 
  bool write(String words,uint8_t linkID=0);
  void write_data(uint8_t words[], uint16_t tx_len);
  bool readString(void);
  bool readIP(void);
  void restore(void);
  bool CIPMode(bool mode);
  bool CIPSend1(uint8_t linkID, uint16_t tx_len);
  bool CIPSend2(void);
  void quit_transmission(void);
  bool CIPClose(void);
  
  void tinywebdb_link(void);
  bool tinywebdb_CIPStart(void);
  bool tinywebdb_update(const char *usr,const char *secret,const char *tag,const char *value);
  bool tinywebdb_delete(const char *usr,const char *secret,const char *tag);
  char *tinywebdb_get(const char *usr,const char *secret,const char *tag);
  char *tinywebdb_data_process();

  int mqtt_connect_pkg(uint8_t MqttSendData[],const char *ClientID,const char *Username,char *Password);
  int mqtt_subscribe_pkg(uint8_t MqttSendData[],char *topic,uint8_t qos,uint8_t whether);
  int mqtt_publish_pkg(uint8_t MqttSendData[],char * topic, char * message, uint8_t qos);

  bool mqtt_subscribe(const char *topic,uint8_t qos,uint8_t whether);
  void mqtt_publish(const char * topic, const char * message, uint8_t qos);
  void mqtt_ping(void);
  void mqtt_disconnect(void);
  bool onenet_mqtt_connect(const char *ProductID,const char *DeviceID,char *Authorization);
  bool onenet_mqtt_publish(/*const char * topic,*/ const char * data_name, const char * value);

  char *onenet_data_process();

private:
	WeOneWire _WeWifi;
  
  bool mqtt_write(uint8_t send_data[],uint8_t send_len,uint8_t linkID=0); 
	uint16_t last_time,eport;
};

#endif

