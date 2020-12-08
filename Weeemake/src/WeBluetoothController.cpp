#include "WeBluetoothController.h"

WeBluetoothController::WeBluetoothController()
{

}

uint8_t WeBluetoothController::readAnalog(uint8_t button)
{
	uint8_t result;
	if (!_isReady){
		return 0x80;
	}
	else{
		if(button == WeJOYSTICK_LY || button == WeJOYSTICK_LX || button == WeJOYSTICK_RY || button == WeJOYSTICK_RX){
	  	result = cmd_data_list[button];
	  	return result;
		}
		else{
		  return 0x80;
		}
	}
}

bool WeBluetoothController::buttonPressed(uint8_t button)
{
	if (!_isReady){
    return 0;
  }
  else{
    return  cmd_data_list[button];
  }
}

void WeBluetoothController::read_from_serial()
{
	_isAvailable = false;
  if(Serial.available() > 0){
    _isAvailable = true;
    _serialRead = Serial.read();
  }
}

void WeBluetoothController::write_data_to_buffer(uint8_t index, uint8_t data_byte)
{
	_index=index;
  buffer[_index]=data_byte;
}

bool WeBluetoothController::parse_data_packets()
{
	bool result = false;
  if(millis() - _lasttime > 200){
    _isReady = false;
    _isStart=false;
    _prevc = 0x00;
    buffer[2] = buffer[4] = buffer[6] =buffer[8] =0x80;
    buffer[1] = buffer[3] = buffer[5] =buffer[7] =0x00;
  }
  read_from_serial();
  while(_isAvailable){
    _lasttime = millis();
    unsigned char c = _serialRead & 0xff;
    if((c == 0xaa) && (_isStart == false)){
      if(_prevc == 0xff){
        _index=1;
        _isStart = true;
      }
    }
    else{
      _prevc = c;
      if(_isStart){
        write_data_to_buffer(_index,c);
      }
    }
    _index++;
    if((_isStart == false) && (_index > 10)){
      _index=0; 
      _isStart=false;
      buffer[2] = buffer[4] = buffer[6] =buffer[8] =0x80;
      buffer[1] = buffer[3] = buffer[5] =buffer[7] =0x00;
    }
    else if(_isStart && (_index > 9)){
      uint8_t checksum;
      checksum = buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7]+buffer[8];
      if(checksum == buffer[9]){
        _isReady = true;
       	_isStart = false;
       	_index = 0;
       	result = true;
      }
      else{
        _isStart = false;
        _index = 0;
        _prevc = 0x00;
        _isStart=false;
        result = false;
      }
    }
    read_from_serial();
   }
   return result;
}

void WeBluetoothController::loop()
{
	if(parse_data_packets()){
    cmd_data_list[WeJOYSTICK_LY] = buffer[2];
    cmd_data_list[WeJOYSTICK_LX] = buffer[4];
    cmd_data_list[WeJOYSTICK_RY] = buffer[6];
    cmd_data_list[WeJOYSTICK_RX] = buffer[8];
    cmd_data_list[WeBUTTON_ZR] = (buffer[3] & 0x01) == 0x01 ? true : false;
    cmd_data_list[WeBUTTON_R] = (buffer[3] & 0x02) == 0x02 ? true : false;
    cmd_data_list[WeBUTTON_ZL] = (buffer[3] & 0x04) == 0x04 ? true : false; 
    cmd_data_list[WeBUTTON_L] = (buffer[3] & 0x08) == 0x08 ? true : false;
    cmd_data_list[WeBUTTON_HOME] = (buffer[3] & 0x10) ==0x10 ? true : false;
    cmd_data_list[WeBUTTON_BL] = (buffer[3] & 0x20) == 0x20 ? true : false;
    cmd_data_list[WeBUTTON_Y] = (buffer[5] & 0x01) == 0x01 ? true : false;
    cmd_data_list[WeBUTTON_B] = (buffer[5] & 0x02) == 0x02 ? true : false;
    cmd_data_list[WeBUTTON_A] = (buffer[5] & 0x04) == 0x04 ? true : false;
    cmd_data_list[WeBUTTON_X] = (buffer[5] & 0x08) == 0x08 ? true : false;
    cmd_data_list[WeBUTTON_PLUS] = (buffer[5] & 0x10) == 0x10 ? true : false;
    cmd_data_list[WeBUTTON_MODE] = (buffer[5] & 0x20) == 0x20 ? true : false ;
    cmd_data_list[WeBUTTON_UP] = (buffer[7] & 0x01) == 0x01 ? true : false ;
    cmd_data_list[WeBUTTON_DOWN] = (buffer[7] & 0x02) == 0x02 ? true : false ;
    cmd_data_list[WeBUTTON_LEFT] = (buffer[7] & 0x04) == 0x04 ? true : false ;
    cmd_data_list[WeBUTTON_RIGHT] = (buffer[7] & 0x08) == 0x08 ? true : false ;
    cmd_data_list[WeBUTTON_MINUS] = (buffer[7] & 0x10) == 0x10 ? true : false ;
    cmd_data_list[WeBUTTON_BR] = (buffer[7] & 0x20) == 0x20 ? true : false ;
  }
}
