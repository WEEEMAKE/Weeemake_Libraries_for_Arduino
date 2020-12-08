#include "WeRaspberryPi.h"

#include <SoftwareSerial.h>
SoftwareSerial serial_pi(7,8);

const uint8_t buffer_len = 70;
static uint8_t buffer[buffer_len];

WeRaspberryPi::WeRaspberryPi()
{

}

void WeRaspberryPi::init()
{
  uint8_t _case=0;
  uint8_t _result_len;
  serial_pi.begin(9600);
  long time = millis();
  while(serial_pi.available() <1){
    if (millis()-time>10000){
      break;
    }
  }
  _case=serial_pi.read();
  switch(_case){
    case 0x03:
      while(serial_pi.available()<4);
      serial_pi.readBytes(buffer, 4);
      _result_len = buffer[3];

      while(serial_pi.available()<_result_len);
      serial_pi.readBytes(buffer+4, result_len);
      break;

    case 0x04:
      while(serial_pi.available()<1);
      serial_pi.read();
      break;

    case 0x05:
      while(serial_pi.available()<1);
      serial_pi.read();
      break;

    case 0x06:
      while(serial_pi.available()<5);
      serial_pi.readBytes(buffer, 5);
      _result_len = buffer[4];

      while(serial_pi.available()<_result_len);
      serial_pi.readBytes(buffer+5, result_len);
      break;

    case 0x07:
      while(serial_pi.available()<5);
      serial_pi.readBytes(buffer, 5);
      _result_len = buffer[4];

      while(serial_pi.available()<_result_len);
      serial_pi.readBytes(buffer+5, result_len);
      break;

    case 0x08:
      while(serial_pi.available()<1);
      serial_pi.read();
      break;

    case 0x09:
      while(serial_pi.available()<1);
      serial_pi.read();
      break;
  }

  textToSpeech("\xca\xf7\xdd\xae\xc5\xc9\xb7\xfe\xce\xf1\xd2\xd1\xbe\xcd\xd0\xf7", 16);
}

bool WeRaspberryPi::setBlocklyServer(bool isOn)
{   
  
  uint8_t cmd=0;
  if (isOn){
    cmd=0xFF;
  }
  else{
    cmd=0xFE;
  }

  while(serial_pi.read() >= 0){}
  serial_pi.write(0xfd);

  serial_pi.write(cmd);   // Blockly Server

  while(serial_pi.available()<2);

  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

uint8_t WeRaspberryPi::setWifiInformation(String _ssid, String _password)
{
   uint32_t ssid_len = (uint32_t)_ssid.length();
   uint32_t password_len = (uint32_t)_password.length();
   const uint8_t buffer_len = 10;
   static uint8_t buffer[buffer_len];

   while(serial_pi.read() >= 0){}
  serial_pi.write(0xfd);

   serial_pi.write(0x01);   //Wifi

   serial_pi.write((ssid_len>>24) & 0xff);
   serial_pi.write((ssid_len>>16) & 0xff);
   serial_pi.write((ssid_len>>8) & 0xff);
   serial_pi.write(ssid_len & 0xff);

  for(uint8_t i=0;i<ssid_len;i++){
       serial_pi.write(_ssid[i]);
  }

  serial_pi.write((password_len>>24) & 0xff);
  serial_pi.write((password_len>>16) & 0xff);
  serial_pi.write((password_len>>8) & 0xff);
  serial_pi.write(password_len & 0xff);

  for(uint8_t i=0;i<password_len;i++){
     serial_pi.write(_password[i]);
  }

  while(serial_pi.available() < 2);

  serial_pi.readBytes(buffer,2);

  return buffer[1];
    
}

bool WeRaspberryPi::speechRecognition(void)
{
  const uint8_t buffer_len = 70;
  static uint8_t buffer[buffer_len];
  
  serial_pi.write(0xfd);

  serial_pi.write(0x03);   //ASR
  
  while(serial_pi.available()<1);
  if (serial_pi.read() != 0x03) return false;
  
  while(serial_pi.available()<4);
  serial_pi.readBytes(buffer, 4);

  uint8_t _result_len = buffer[3];
  result_len=_result_len;
  if (result_len > 0) {
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+4, result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[4+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::textToSpeech(const uint8_t gbk_code[], uint32_t len)
{
  uint32_t _data_len = len;
  
  serial_pi.write(0xfd);

  serial_pi.write(0x04);   //TTS

  serial_pi.write((_data_len>>24) & 0xff);
  serial_pi.write((_data_len>>16) & 0xff);
  serial_pi.write((_data_len>>8) & 0xff);
  serial_pi.write(_data_len & 0xff);

  for(uint8_t i=0;i<_data_len;i++){
    serial_pi.write(gbk_code[i]);
  }

  while(serial_pi.available()<1);
  if (serial_pi.read() != 0x04) return false;

  while(serial_pi.available()<1);

  bool result = (bool)serial_pi.read();

  return result;
}

bool WeRaspberryPi::freeDialogue(void)
{
  serial_pi.write(0xfd);
  serial_pi.write(0x05);   //Free Dialogue

  while(serial_pi.available()<2);

  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

bool WeRaspberryPi::setBaiduAccount(String _apikey, String _secretkey)
{
  uint32_t apikey_len = (uint32_t)_apikey.length();
  uint32_t secretkey_len = (uint32_t)_secretkey.length();
  
  serial_pi.write(0xfd);
  serial_pi.write(0x02);

  serial_pi.write((apikey_len>>24) & 0xff);
  serial_pi.write((apikey_len>>16) & 0xff);
  serial_pi.write((apikey_len>>8) & 0xff);
  serial_pi.write(apikey_len & 0xff);

  for(uint8_t i=0;i<apikey_len;i++){
       serial_pi.write(_apikey[i]);
  }

  serial_pi.write((secretkey_len>>24) & 0xff);
  serial_pi.write((secretkey_len>>16) & 0xff);
  serial_pi.write((secretkey_len>>8) & 0xff);
  serial_pi.write(secretkey_len & 0xff);

  for(uint8_t i=0;i<secretkey_len;i++){
    serial_pi.write(_secretkey[i]);
  }

  while(serial_pi.available()<2);

  serial_pi.readBytes(buffer,2);
  return buffer[1];
}


bool WeRaspberryPi::textRecognition()
{
  serial_pi.write(0xfd);
  serial_pi.write(0x06);

  while(serial_pi.available()<6);
  serial_pi.readBytes(buffer,6);
  uint8_t _result_len = buffer[5];
  result_len=_result_len;
  if (result_len>0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+6,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[6+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::animalRecognition()
{
  while(serial_pi.read() >= 0){return false;}
  
  serial_pi.write(0xfd);

  serial_pi.write(0x07);
  serial_pi.write(0x01);
 
  while(serial_pi.available()<1);
  if (serial_pi.read() != 0x06) return false;

  while(serial_pi.available()<5);
  serial_pi.readBytes(buffer,5);
  uint8_t _result_len = buffer[4];
  result_len=_result_len;

  if (result_len>0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+5,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[5+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::plantRecognition()
{
  uint8_t a=0;
  while(serial_pi.read() >= 0){return false;}

  serial_pi.write(0xfd);
  serial_pi.write(0x07);
  serial_pi.write(a);

  while(serial_pi.available()<6);
  serial_pi.readBytes(buffer,6);
  uint8_t _result_len = buffer[5];
  result_len=_result_len;

  if (result_len > 0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+6,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[6+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::objectRecognition()
{
  while(serial_pi.read() >= 0){return false;}
  serial_pi.write(0xfd);
  serial_pi.write(0x07);
  serial_pi.write(0x02);

  while(serial_pi.available()<6);
  serial_pi.readBytes(buffer,6);
  uint8_t _result_len = buffer[5];
  result_len=_result_len;

  if (result_len > 0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+6,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[6+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::faceTrain(uint8_t number)
{
  serial_pi.write(0xfd);
  serial_pi.write(0x08);
  serial_pi.write(number);

  while(serial_pi.available()<2);

  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

bool WeRaspberryPi::faceCompare(uint8_t number)
{
  serial_pi.write(0xfd);
  serial_pi.write(0x09);
  serial_pi.write(number);

  while(serial_pi.available()<2);

  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

bool WeRaspberryPi::contains(const uint8_t text_buffer[], uint8_t size)
{
  if(size > result_len)return false;
  for(int i=0, n=result_len-size; i<=n; ++i){
    bool flag = true;
    for(int j=0; j<size; ++j){
      if(result_buffer[i+j] != text_buffer[j]){
        flag = false;
        break;
      }
    }
    if(flag)return true;
  }
  return false;
}

bool WeRaspberryPi::tinywebdbUpdate(String _user, String _secret, String _tag, String _value)
{
   uint32_t user_len = (uint32_t)_user.length();
   uint32_t secret_len = (uint32_t)_secret.length();
   uint32_t tag_len = (uint32_t)_tag.length();
   uint32_t value_len = (uint32_t)_value.length();
 
   serial_pi.write(0xfd); 

   serial_pi.write(0x0b);   //tinywebdb update

   serial_pi.write((user_len>>24) & 0xff);
   serial_pi.write((user_len>>16) & 0xff);
   serial_pi.write((user_len>>8) & 0xff);
   serial_pi.write(user_len & 0xff);

  for(uint8_t i=0;i<user_len;i++){
       serial_pi.write(_user[i]);
  }

  serial_pi.write((secret_len>>24) & 0xff);
  serial_pi.write((secret_len>>16) & 0xff);
  serial_pi.write((secret_len>>8) & 0xff);
  serial_pi.write(secret_len & 0xff);

    for(uint8_t i=0;i<secret_len;i++){
       serial_pi.write(_secret[i]);
  }

  serial_pi.write((tag_len>>24) & 0xff);
  serial_pi.write((tag_len>>16) & 0xff);
  serial_pi.write((tag_len>>8) & 0xff);
  serial_pi.write(tag_len & 0xff);

  for(uint8_t i=0;i<tag_len;i++){
     serial_pi.write(_tag[i]);
  }

  serial_pi.write((value_len>>24) & 0xff);
  serial_pi.write((value_len>>16) & 0xff);
  serial_pi.write((value_len>>8) & 0xff);
  serial_pi.write(value_len & 0xff);

  for(uint8_t i=0;i<value_len;i++){
     serial_pi.write(_value[i]);
  }

  while(serial_pi.available()<2);
  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

bool WeRaspberryPi::tinywebdbGet(String _user, String _secret, String _tag)
{
   uint32_t user_len = (uint32_t)_user.length();
   uint32_t secret_len = (uint32_t)_secret.length();
   uint32_t tag_len = (uint32_t)_tag.length();
 
   serial_pi.write(0xfd); 

   serial_pi.write(0x0c);   //tinywebdb get

   serial_pi.write((user_len>>24) & 0xff);
   serial_pi.write((user_len>>16) & 0xff);
   serial_pi.write((user_len>>8) & 0xff);
   serial_pi.write(user_len & 0xff);

  for(uint8_t i=0;i<user_len;i++){
    serial_pi.write(_user[i]);
  }

  serial_pi.write((secret_len>>24) & 0xff);
  serial_pi.write((secret_len>>16) & 0xff);
  serial_pi.write((secret_len>>8) & 0xff);
  serial_pi.write(secret_len & 0xff);

  for(uint8_t i=0;i<secret_len;i++){
    serial_pi.write(_secret[i]);
  }

  serial_pi.write((tag_len>>24) & 0xff);
  serial_pi.write((tag_len>>16) & 0xff);
  serial_pi.write((tag_len>>8) & 0xff);
  serial_pi.write(tag_len & 0xff);

  for(uint8_t i=0;i<tag_len;i++){
    serial_pi.write(_tag[i]);
  }

  while(serial_pi.available()<1);
  if (serial_pi.read() != 0x0c) return false;

  while(serial_pi.available()<5);
  serial_pi.readBytes(buffer,5);
  uint8_t _result_len = buffer[4];
  result_len=_result_len;

  if (result_len > 0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+5,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[5+i];
    }
    return true;
  }
  else{
    return false;
  }
}

bool WeRaspberryPi::tinywebdbDelete(String _user, String _secret, String _tag)
{
   uint32_t user_len = (uint32_t)_user.length();
   uint32_t secret_len = (uint32_t)_secret.length();
   uint32_t tag_len = (uint32_t)_tag.length();
 
   serial_pi.write(0xfd); 

   serial_pi.write(0x0d);   //tinywebdb get

   serial_pi.write((user_len>>24) & 0xff);
   serial_pi.write((user_len>>16) & 0xff);
   serial_pi.write((user_len>>8) & 0xff);
   serial_pi.write(user_len & 0xff);

  for(uint8_t i=0;i<user_len;i++){
    serial_pi.write(_user[i]);
  }

  serial_pi.write((secret_len>>24) & 0xff);
  serial_pi.write((secret_len>>16) & 0xff);
  serial_pi.write((secret_len>>8) & 0xff);
  serial_pi.write(secret_len & 0xff);

  for(uint8_t i=0;i<secret_len;i++){
    serial_pi.write(_secret[i]);
  }

  serial_pi.write((tag_len>>24) & 0xff);
  serial_pi.write((tag_len>>16) & 0xff);
  serial_pi.write((tag_len>>8) & 0xff);
  serial_pi.write(tag_len & 0xff);

  for(uint8_t i=0;i<tag_len;i++){
    serial_pi.write(_tag[i]);
  }

  while(serial_pi.available()<2);
  serial_pi.readBytes(buffer,2);

  return buffer[1];
}

bool WeRaspberryPi::tinywebdbCount(String _user, String _secret)
{
   uint32_t user_len = (uint32_t)_user.length();
   uint32_t secret_len = (uint32_t)_secret.length();
 
   serial_pi.write(0xfd); 

   serial_pi.write(0x0e);   //tinywebdb get

   serial_pi.write((user_len>>24) & 0xff);
   serial_pi.write((user_len>>16) & 0xff);
   serial_pi.write((user_len>>8) & 0xff);
   serial_pi.write(user_len & 0xff);

  for(uint8_t i=0;i<user_len;i++){
    serial_pi.write(_user[i]);
  }

  serial_pi.write((secret_len>>24) & 0xff);
  serial_pi.write((secret_len>>16) & 0xff);
  serial_pi.write((secret_len>>8) & 0xff);
  serial_pi.write(secret_len & 0xff);

  for(uint8_t i=0;i<secret_len;i++){
    serial_pi.write(_secret[i]);
  }

  while(serial_pi.available()<1);
  if (serial_pi.read() != 0x0e) return false;

  while(serial_pi.available()<5);
  serial_pi.readBytes(buffer,5);
  uint8_t _result_len = buffer[4];
  result_len=_result_len;

  if (result_len > 0){
    while(serial_pi.available()<result_len);
    serial_pi.readBytes(buffer+5,result_len);
    for(uint8_t i=0; i<result_len; i++){
      result_buffer[i]=buffer[5+i];
    }
    return true;
  }
  else{
    return false;
  }
}

char* WeRaspberryPi::tinywebdbGetResult(String _user, String _secret, String _tag)
{
  if(tinywebdbGet(_user, _secret, _tag))
    return result_buffer;
  return 0;
}