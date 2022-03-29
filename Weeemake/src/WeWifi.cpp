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

/* Set Wifi Informatiom [SSID,PASSWORD] */
void WeWifi::setWIFIinfo(char *ssid, char *pwd)
{
  if(_WeWifi.reset()!=0)return ;
  _WeWifi.write_byte(0x03);
  if(_WeWifi.reset()!=0)return ;
  while(*ssid){
    _WeWifi.write_byte(*ssid);
    ++ssid;
  }
  _WeWifi.write_byte(0x00);
  delay(50);
  
  if(_WeWifi.reset()!=0)return ;
  _WeWifi.write_byte(0x04);
  if(_WeWifi.reset()!=0)return ;
  while(*pwd){
    _WeWifi.write_byte(*pwd);
    ++pwd;
  }
  _WeWifi.write_byte(0x00);
  delay(50);
}

void WeWifi::initAP(uint8_t chl)
{
  CWMode(2);
  CWSAP(chl,2);
  CIPMux(1);
  setPort(6602);
}

/* AP Mode Set Wifi Information, Communication channel, and Encryption */
/* chl:1~13; 0-OPEN，1-WEP，2-WPA_PSK，3-WPA2_PSK，4-WPA_WPA2_PSK */
bool WeWifi::CWSAP(uint8_t chl,uint8_t ecn)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x05);
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(chl);
  _WeWifi.write_byte(ecn);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1000)return 0;
  }
  return (_WeWifi.read_byte());
}

/* Set Up Multiple Connections */
/* mode: 0,1 */
bool WeWifi::CIPMux(bool mode)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x0e);
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(mode);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>200)return 0;
  }
  return (_WeWifi.read_byte());
}

void WeWifi::initSTA(void)
{
  CWMode(1);
  CWJAP();
  CIPMux(1);
  setPort(6602);
}

/* STA Mode Connect Wifi */
bool WeWifi::CWJAP(void)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x09);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>11000)return 0; 
  }
  return (_WeWifi.read_byte());
}

/* AP+STA Mode  Connect TCP Server*/
void WeWifi::initTCP(char *ip,uint16_t port,uint8_t linkID)
{
  CWMode(3);
  CWJAP();
  CIPMux(1);
  CIPStart(ip,port,linkID);
}

/* Multiple connections Connect TCP Server*/
bool WeWifi::CIPStart(char *ip,uint16_t port,uint8_t linkID)
{
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(0x0b);
  if(_WeWifi.reset()!=0)return 0;
  while(*ip){
    _WeWifi.write_byte(*ip);
    ++ip;
  }
  _WeWifi.write_byte(0x00);
  
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(0x0c);
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(port);
  _WeWifi.write_byte(port>>8);
  _WeWifi.write_byte(linkID);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1000)return 0;
  }
  return (_WeWifi.read_byte());
}

/* Single connections Connect TCP Server*/
bool WeWifi::CIPStart1(char *ip,uint16_t port)
{
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(0x0b);
  if(_WeWifi.reset()!=0)return 0;
  while(*ip){
    _WeWifi.write_byte(*ip);
    ++ip;
  }
  _WeWifi.write_byte(0x00);
  
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(0x13);
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(port);
  _WeWifi.write_byte(port>>8);
  
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1000)return 0;
  }
  return (_WeWifi.read_byte());
}

/* STA Mode  Connect TCP Server */
void WeWifi::initSlave(char *ip,uint16_t port) 
{
  CWMode(1);
  CWJAP();
  CIPMux(1);
  CIPStart(ip,port,0);
}

/* Set Wifi Working Mode, AP, STA or AP+STA */
/* mode: 1-STA, 2-AP, 3-AP+STA */
bool WeWifi::CWMode(uint8_t mode)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x02);
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(mode);

  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1000)return 0;
  }
  return (_WeWifi.read_byte());
}

/* AP Mode TCP Server */
bool WeWifi::setPort(uint16_t port)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x06);
  if(_WeWifi.reset()!=0)return 0;  
  _WeWifi.write_byte(port);
  _WeWifi.write_byte(port>>8);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>500)return 0;
  }
  return (_WeWifi.read_byte());
}

bool WeWifi::CIPSend1(uint8_t linkID, uint16_t tx_len)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x07);
  if(_WeWifi.reset()!=0)return 0; 
  _WeWifi.write_byte(linkID);
  _WeWifi.write_byte(tx_len>>8);
  _WeWifi.write_byte(tx_len);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>500)return 0;
  }
  return (_WeWifi.read_byte());

}

bool WeWifi::write(String words,uint8_t linkID)  //linkID 0~4 
{
  return write(words.c_str(), linkID);
}

bool WeWifi::write(const char *words,uint8_t linkID)  //linkID 0~4 
{ 
  uint16_t tx_len = strlen(words);

  CIPSend1(linkID, tx_len);

  write_data(words, tx_len);
  
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1500)return 0;
  }
  return (_WeWifi.read_byte());
}

/* Get TCP Data */
bool WeWifi::readString(void)
{
  delay(10);
  if(_WeWifi.reset()!=0)return 0; 
  _WeWifi.write_byte(0x08);
  _WeWifi.respond();
  link_IP=_WeWifi.read_byte();
  if(link_IP==0xff) return 0;
  rx_len=((uint16_t)_WeWifi.read_byte()<<8)|((uint16_t)_WeWifi.read_byte()); 
  for(uint16_t i=0;i<rx_len;i++){
    rx_buffer[i]=_WeWifi.read_byte();
  }
  rx_buffer[rx_len]=0x00;
  return 1;
}

/* Get IP */
bool WeWifi::readIP(void)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x0a);
  
  unsigned long time;
  time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1000)return 0;
  }
  for(uint8_t i=0;i<16;i++){
    IP_addr[i]=_WeWifi.read_byte();
    if(IP_addr[i]==0){
      delay(10);
      return 1;
    }
  }
  return 0;
}

/* Restore */
void WeWifi::restore(void)
{
  if(_WeWifi.reset()!=0)return ;  
  _WeWifi.write_byte(0x0d);
}

/* Transparent transmission settings */
bool WeWifi::CIPMode(bool mode)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x0f);
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(mode);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>500)return 0;
  }
  return (_WeWifi.read_byte());
}

/* Transparent transmission Data Send CMD */
bool WeWifi::CIPSend2(void)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x10);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>100)return 0;
  }
  return (_WeWifi.read_byte());
}

void WeWifi::write_data(uint8_t words[], uint16_t tx_len)
{
  if(_WeWifi.reset()!=0)return ;
  _WeWifi.write_byte(0x11);
  if(_WeWifi.reset()!=0)return ;
  // _WeWifi.write_byte(tx_len>>8);
  // _WeWifi.write_byte(tx_len);
  for (int i = 0; i < tx_len;i++){
    _WeWifi.write_byte(words[i]);
  }
  _WeWifi.write_byte(0x00);
  delay(100);
}

void WeWifi::quit_transmission(void)  //退出透传模式
{
  if(_WeWifi.reset()!=0)return ;
  _WeWifi.write_byte(0x12);
  delay(100);
}

bool WeWifi::CIPClose(void)  //关闭连接
{
  if(_WeWifi.reset()!=0)
    return 0;
  _WeWifi.write_byte(0x14);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
  if((millis()-time)>100)
    return 0;
  }
  return (_WeWifi.read_byte());
}

void WeWifi::tinywebdb_link(void)
{
  CWMode(1);   //STA模式
  CWJAP();     //连接WIFI
  CIPMux(0);   //设置单连接模式
  CIPMode(1);  //设置为透传模式
  tinywebdb_CIPStart();  //连接TinyWebDB服务器
  CIPSend2();   //透传发送指令
}

bool WeWifi::tinywebdb_CIPStart(void)
{
  if(_WeWifi.reset()!=0)
  return 0; 
  _WeWifi.write_byte(0x15);
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>2000)
    return 0;
  }
  return (_WeWifi.read_byte());
}

bool WeWifi::tinywebdb_update(const char *usr,const char *secret,const char *tag,const char *value)
{
  String postdata = String("user=")+String(usr)+
                    String("&secret=")+String(secret)+
                    String("&action=update&tag=")+String(tag)+
                    String("&value=")+String(value);
  postdata = String(postdata.length())+postdata;

  if(_WeWifi.reset()!=0)
    return 0; 
  _WeWifi.write_byte(0x16);
  if(_WeWifi.reset()!=0)
    return 0;

  for (int i = 0; i < postdata.length(); ++i){
    _WeWifi.write_byte(postdata[i]);
  }
  _WeWifi.write_byte(0x00);

  unsigned long time = millis();
  while(readString()!=1){
    delay(100);
    if((millis()-time)>5000)return 0;
  }
  return (strcmp(tinywebdb_data_process(), "success") == 0);
}

bool WeWifi::tinywebdb_delete(const char *usr,const char *secret,const char *tag)
{
  String postdata = String("user=")+String(usr)+
                    String("&secret=")+String(secret)+
                    String("&action=delete&tag=")+String(tag);
  postdata = String(postdata.length())+postdata;

  if(_WeWifi.reset()!=0)
    return 0; 
  _WeWifi.write_byte(0x16);
  if(_WeWifi.reset()!=0)
    return 0;

  for (int i = 0; i < postdata.length(); ++i){
    _WeWifi.write_byte(postdata[i]);
  }
  _WeWifi.write_byte(0x00);
  
  unsigned long time = millis();
  while(readString()!=1){
    delay(100);
    if((millis()-time)>5000)return 0;
  }
  
  return (strcmp(tinywebdb_data_process(), "success") == 0);
}

char *WeWifi::tinywebdb_get(const char *usr,const char *secret,const char *tag)
{
  String postdata = String("user=")+String(usr)+
                    String("&secret=")+String(secret)+
                    String("&action=get&tag=")+String(tag);
  postdata = String(postdata.length())+postdata;

  if(_WeWifi.reset()!=0)
    return NULL; 
  _WeWifi.write_byte(0x16);
  if(_WeWifi.reset()!=0)
    return NULL;

  for (int i = 0; i < postdata.length(); ++i){
    _WeWifi.write_byte(postdata[i]);
  }
  _WeWifi.write_byte(0x00);

  unsigned long time = millis();
  while(readString()!=1){
    delay(100);
    if((millis()-time)>5000)return NULL;
  }
  
  return tinywebdb_data_process();
}

char *WeWifi::tinywebdb_data_process()
{ 
  *strstr(rx_buffer, "\"}") = 0x00;
  return strstr(rx_buffer, ": \"")+3;
}

/**
* @brief  连接服务器的打包函数
* @param  MqttSendData[]  数据包存入
* @param  ClientID        客户端ID
* @param  Username        用户名
* @param  Password        密码
* @retval 返回数据包长度
* @example 
**/
int WeWifi::mqtt_connect_pkg(uint8_t MqttSendData[],const char *ClientID,const char *Username,char *Password)
{
  int ClientIDLen = strlen(ClientID);
  int UsernameLen    = strlen(Username);
  int PasswordLen = strlen(Password);
  int DataLen = 0;
  int Index = 2;
  int i = 0;

  DataLen = 12 + 2+2+ClientIDLen+UsernameLen+PasswordLen;
  MqttSendData[0] = 0x10;                //MQTT Message Type CONNECT
  MqttSendData[1] = DataLen;    //剩余长度(不包括固定头部)
  MqttSendData[Index++] = 0;        // Protocol Name Length MSB    
  MqttSendData[Index++] = 4;        // Protocol Name Length LSB    
  MqttSendData[Index++] = 'M';        // ASCII Code for M    
  MqttSendData[Index++] = 'Q';        // ASCII Code for Q    
  MqttSendData[Index++] = 'T';        // ASCII Code for T    
  MqttSendData[Index++] = 'T';        // ASCII Code for T    
  MqttSendData[Index++] = 4;        // MQTT Protocol version = 4    
  MqttSendData[Index++] = 0xc0;        // conn flags
  MqttSendData[Index++] = 0;        // Keep-alive Time Length MSB
  MqttSendData[Index++] = 78;        // Keep-alive Time Length LSB  120S心跳包

  MqttSendData[Index++] = (0xff00&ClientIDLen)>>8;// Client ID length MSB    
  MqttSendData[Index++] = 0xff&ClientIDLen;    // Client ID length LSB  
  for(i = 0; i < ClientIDLen; i++){
    MqttSendData[Index + i] = ClientID[i];          
  }
  Index = Index + ClientIDLen;
  
  if(UsernameLen > 0){   
    MqttSendData[Index++] = (0xff00&UsernameLen)>>8;//username length MSB    
    MqttSendData[Index++] = 0xff&UsernameLen;    //username length LSB    
    for(i = 0; i < UsernameLen ; i++){
      MqttSendData[Index + i] = Username[i];    
    }
    Index = Index + UsernameLen;
  }
  
  if(PasswordLen > 0){    
    MqttSendData[Index++] = (0xff00&PasswordLen)>>8;//password length MSB    
    MqttSendData[Index++] = 0xff&PasswordLen;    //password length LSB    
    for(i = 0; i < PasswordLen ; i++){
      MqttSendData[Index + i] = Password[i];    
    }
    Index = Index + PasswordLen; 
  }    
  return Index;
}

/**
* @brief  MQTT订阅/取消订阅数据打包函数
* @param  MqttSendData[]  数据包存入
* @param  topic           主题 
* @param  qos             消息等级 
* @param  whether         订阅/取消订阅请求包
* @retval 返回数据包长度
* @example 
**/
int WeWifi::mqtt_subscribe_pkg(uint8_t MqttSendData[],char *topic,uint8_t qos,uint8_t whether)
{
  int topiclen = strlen(topic);
  int i=0,index = 0;

  if(whether)
    MqttSendData[index++] = 0x82;                   //0x82 //消息类型和标志 SUBSCRIBE 订阅
  else
    MqttSendData[index++] = 0xA2;                   //0xA2 取消订阅
  MqttSendData[index++] = topiclen + 5;             //剩余长度(不包括固定头部)
  MqttSendData[index++] = 0;                        //消息标识符,高位
  MqttSendData[index++] = 0x01;                     //消息标识符,低位
  MqttSendData[index++] = (0xff00&topiclen)>>8;     //主题长度(高位在前,低位在后)
  MqttSendData[index++] = 0xff&topiclen;            //主题长度 
  
  for (i = 0;i < topiclen; i++){
    MqttSendData[index + i] = topic[i];
  }
  index = index + topiclen;
  
  if(whether){
    MqttSendData[index] = qos;//QoS级别
    index++;
  }
  return index;
}


/**
* @brief  MQTT发布数据打包函数
* @param  MqttSendData 打包数据存入该数组
* @param  message mqtt_message 
* @param  topic       主题 
* @param  qos         消息等级 
* @retval 返回数据包长度
* @example 
**/
int WeWifi::mqtt_publish_pkg(uint8_t MqttSendData[],char * topic, char * message, uint8_t qos)
{
  int topic_length = strlen(topic);    
  int message_length = strlen(message);  
  int i,index=0;    
  static uint16_t id=0;
  
  MqttSendData[index++] = 0x30;    // MQTT Message Type PUBLISH  

  if(qos)
    MqttSendData[index++] = 2 + topic_length + 2 + message_length;  //数据长度
  else
    MqttSendData[index++] = 2 + topic_length + message_length;      // Remaining length  

  MqttSendData[index++] = (0xff00&topic_length)>>8;                //主题长度
  MqttSendData[index++] = 0xff&topic_length;
       
  for(i = 0; i < topic_length; i++){
    MqttSendData[index + i] = topic[i];                //拷贝主题
  }
  index += topic_length;
      
  if(qos){
    MqttSendData[index++] = (0xff00&id)>>8;
    MqttSendData[index++] = 0xff&id;
    id++;
  }

  for(i = 0; i < message_length; i++){
    MqttSendData[index + i] = message[i];  //拷贝数据
  }
  index += message_length;
      
  return index;
}

bool WeWifi::mqtt_write(uint8_t send_data[],uint8_t send_len,uint8_t linkID=0)
{
  if(_WeWifi.reset()!=0)return 0;
  _WeWifi.write_byte(0x17);
  if(_WeWifi.reset()!=0)return 0; 
  _WeWifi.write_byte(linkID);
  _WeWifi.write_byte(send_len);
  for (int i = 0; i < send_len; ++i){
    _WeWifi.write_byte(send_data[i]);
  }
  unsigned long time = millis();
  while(_WeWifi.respond()==1){
    if((millis()-time)>1500)return 0;
  }
  return (_WeWifi.read_byte());
}

bool WeWifi::onenet_mqtt_connect(const char *ProductID,const char *DeviceID,char *Authorization)
{ 
  uint8_t _send_len=0;
  _send_len = mqtt_connect_pkg(rx_buffer,DeviceID,ProductID,Authorization);
  mqtt_write(rx_buffer,_send_len,0);

  unsigned long time = millis();
  while(readString()!=1){
    if((millis()-time)>200)return 0;
  }

  if (rx_len==4&&rx_buffer[0]==0x20&&rx_buffer[1]==0x02&&rx_buffer[3]==0x00){
    return 1;
  }
  else{
    return 0;
  }
}

bool WeWifi::mqtt_subscribe(const char *topic,uint8_t qos,uint8_t whether)
{
  uint8_t _send_len=0;
  _send_len=mqtt_subscribe_pkg(rx_buffer,topic,qos,whether);
  mqtt_write(rx_buffer,_send_len,0);

  unsigned long time = millis();
  while(readString()!=1){
    if((millis()-time)>200)return 0;
  }

  if (rx_len==5&&rx_buffer[0]==0x90&&rx_buffer[1]==0x03&&rx_buffer[4]==qos){
    return 1;
  }
  else{
    return 0;
  }
}

void WeWifi::mqtt_publish(const char * topic, const char * message, uint8_t qos)
{
  int _send_len=0;
  _send_len=mqtt_publish_pkg(rx_buffer,topic, message, qos);
  mqtt_write(rx_buffer,_send_len,0);
  delay(150);
}

void WeWifi::mqtt_ping(void)
{
  uint8_t _send_buffer[2]={0xC0, 0x00};
  mqtt_write(_send_buffer,2,0);
}

void WeWifi::mqtt_disconnect(void)
{
  uint8_t _send_buffer[2]={0xE0, 0x00};
  mqtt_write(_send_buffer,2,0);
}

// void WeWifi::onenet_mqtt_publish(String  topic, String  message)
// {
//   onenet_mqtt_publish(topic.c_str(), message.c_str());
// }

bool WeWifi::onenet_mqtt_publish(/*const char * topic,*/ const char * data_name, const char * value)
{
  uint8_t topic_length = 3/*strlen(topic)*/;    
  uint8_t data_name_length = strlen(data_name);
  uint8_t value_length = strlen(value);
  uint8_t message_length = 2+data_name_length+3+value_length+2;
  int i,index=0;    
  static uint16_t id=0;
  
  rx_buffer[index++] = 0x30;    // MQTT Message Type PUBLISH  
  rx_buffer[index++] = 2 + topic_length + 3 + message_length;  //数据长度

  rx_buffer[index++] = (0xff00&topic_length)>>8;                //主题长度
  rx_buffer[index++] = 0xff&topic_length;
  
    
  // for(i = 0; i < topic_length; i++){
  //   rx_buffer[index + i] = topic[i];                //拷贝主题
  // }
  // index += topic_length;
  

  rx_buffer[index + 0]='$';
  rx_buffer[index + 1]='d';
  rx_buffer[index + 2]='p';
  index += topic_length;

  rx_buffer[index++] = 0x03;       // Onenet 数据类型3:Json数据2
  

  rx_buffer[index++] = (0xff00&message_length)>>8;                //信息长度
  rx_buffer[index++] = 0xff&message_length;

  rx_buffer[index++] = 0x7B;  //{
  rx_buffer[index++] = 0x22;  //"

  for(i = 0; i < data_name_length; i++){
    rx_buffer[index + i] = data_name[i];  //拷贝数据
  }
  index += data_name_length;

  rx_buffer[index++] = 0x22;  //"
  rx_buffer[index++] = 0x3A;  //:
  rx_buffer[index++] = 0x22;  //"

  for(i = 0; i < value_length; i++){
    rx_buffer[index + i] = value[i];  //拷贝数据
  }
  index += value_length;

  rx_buffer[index++] = 0x22;  //"
  rx_buffer[index++] = 0x7D;  //}

  mqtt_write(rx_buffer,index,0);
}

char *WeWifi::onenet_data_process()
{
  return rx_buffer+rx_buffer[3]+4;
}