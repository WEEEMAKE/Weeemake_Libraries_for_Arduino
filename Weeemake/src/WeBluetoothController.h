#ifndef We_Bluetooth_Controller_H
#define We_Bluetooth_Controller_H

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#define WeJOYSTICK_LY     (1)
#define WeJOYSTICK_LX     (2)
#define WeJOYSTICK_RY     (3)
#define WeJOYSTICK_RX     (4)

#define WeBUTTON_ZR       (5)
#define WeBUTTON_R        (6)
#define WeBUTTON_ZL       (7)
#define WeBUTTON_L        (8)
#define WeBUTTON_HOME     (9)
#define WeBUTTON_BL       (10)
#define WeBUTTON_Y        (11)
#define WeBUTTON_B        (12)
#define WeBUTTON_A        (13)
#define WeBUTTON_X        (14)
#define WeBUTTON_PLUS     (15)   //+
#define WeBUTTON_MODE     (16)
#define WeBUTTON_UP       (17)
#define WeBUTTON_DOWN     (18)
#define WeBUTTON_LEFT     (19)
#define WeBUTTON_RIGHT    (20)
#define WeBUTTON_MINUS    (21)   //-
#define WeBUTTON_BR       (22)

class WeBluetoothController
{
public:
	WeBluetoothController();

	uint8_t readAnalog(uint8_t button);
	void loop();
  bool buttonPressed(uint8_t button);

private:
  bool _isStart;
  bool _isAvailable;
  bool _isReady;
  uint8_t _serialRead;
  uint8_t _index = 0;
  uint8_t _prevc = 0;
  long _lasttime;
  uint8_t buffer[16];
  uint8_t cmd_data_list[23];
  void read_from_serial(void);
  void write_data_to_buffer(uint8_t index, uint8_t data_byte);
  bool parse_data_packets(void);

};

#endif