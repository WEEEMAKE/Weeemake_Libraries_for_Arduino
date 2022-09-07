#include "WeRFIDModule.h"

WeRFIDModule::WeRFIDModule(uint8_t port)
{
  _WeRFIDModule.reset(port);
}
void WeRFIDModule::reset(uint8_t port)
{
  _WeRFIDModule.reset(port);
}

bool WeRFIDModule::read(void)
{
  rx_buffer[0] = 0x01;
  if (_WeRFIDModule.reset() != 0)
    return 0;
  _WeRFIDModule.write_byte(0x02);
  _WeRFIDModule.respond();
  rx_buffer[0] = _WeRFIDModule.read_byte();
  if (rx_buffer[0] == 0x02)
  {
    for (int i = 1; i < 13; ++i)
    {
      rx_buffer[i] = _WeRFIDModule.read_byte();
    }
    getID();
    return 1;
  }
  else {
    return 0;
  }
}

void WeRFIDModule::getID(void)
{
  String _id_hex;
  uint32_t pow_16[8]={268435456,16777216,1048576,65536,4096,256,16,1};
  ID_Number = 0;
  ID_String = "";
  // to hex
  for (int i = 3; i < 11; ++i)
  {
    _id_hex+=char(rx_buffer[i]);
  }
  
  // to dec
  for (int i = 0; i < _id_hex.length(); i++)
  {
    if (int(_id_hex.charAt(i))<0x41)
    {
      ID_Number+=(uint32_t)(int(_id_hex.charAt(i))-48)*pow_16[i];
    }
    else{
      ID_Number+=(uint32_t)(int(_id_hex.charAt(i))-55)*pow_16[i];
    } 
  }

  // to dec string
  ID_String = String(ID_Number);

  for(int i = 0; i< 10-ID_String.length(); i++)
  {
    ID_String = String("0")+ID_String;
  }
}
