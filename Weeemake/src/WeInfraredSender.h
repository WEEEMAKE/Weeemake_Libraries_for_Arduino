#ifndef WeInfraredSender_H
#define WeInfraredSender_H

#include "WePort.h"

/* NEC Code table */
#define IR_CONTROLLER_A     (0x45)
#define IR_CONTROLLER_B     (0x46)
#define IR_CONTROLLER_C     (0x47)
#define IR_CONTROLLER_D     (0x44)
#define IR_CONTROLLER_UP    (0x40)
#define IR_CONTROLLER_E     (0x43)
#define IR_CONTROLLER_LEFT  (0x07)
#define IR_CONTROLLER_OK    (0x15)
#define IR_CONTROLLER_RIGHT (0x09)
#define IR_CONTROLLER_DOWN  (0x19)
#define IR_CONTROLLER_F     (0x0D)
#define IR_CONTROLLER_0     (0x16)
#define IR_CONTROLLER_1     (0x0C)
#define IR_CONTROLLER_2     (0x18)
#define IR_CONTROLLER_3     (0x5E)
#define IR_CONTROLLER_4     (0x08)
#define IR_CONTROLLER_5     (0x1C)
#define IR_CONTROLLER_6     (0x5A)
#define IR_CONTROLLER_7     (0x42)
#define IR_CONTROLLER_8     (0x52)
#define IR_CONTROLLER_9     (0x4A)
#define DEFAULT_USER_CODE   (0x00)

class WeInfraredSender
{
public:
	WeInfraredSender(uint8_t port=0);
	void reset(uint8_t port);

	void send_nec_message(uint8_t user_code, uint8_t data_code);

private:
	uint8_t _Sensorpin;
	void generate_38kHzPlus(uint16_t x,bool y);
	void send_code(uint8_t data_code);
	
};

#endif