#include "We130DCMotor.h"

We130DCMotor::We130DCMotor(uint8_t port)
{
    reset(port);
	
}

void We130DCMotor::reset(uint8_t port)
{	
	_130DCMotor.reset(port);	
	last_speed=300;
}

void We130DCMotor::run(int16_t speed)
{
	speed = max(-255, min(255, speed));

	if(speed == last_speed){
		return;
	}

	last_speed = speed;
	uint8_t value;
	if(speed >= 0){
		value = (uint8_t)(speed/2.55);
	}else{
		value = (uint8_t)(100-speed/2.55);
	}

	_130DCMotor.reset();
	_130DCMotor.write_byte(0x02);
	_130DCMotor.reset();
	_130DCMotor.write_byte(value);
	delayMicroseconds(500);
}

void We130DCMotor::stop(void)
{
	run(0);
}

void We130DCMotor::runTo(int16_t speed)
{
	const int DELAY = 20;
	const int MAX_STEP = 10;

	int16_t now_speed = last_speed;

	if(now_speed > 255){
		now_speed = 1;
	}

	speed = max(-255, min(255, speed));

	if(speed == now_speed){
		return;
	}
	/*
	Serial.println("-----------------");
	Serial.print("speed: ");
	Serial.println(speed);

	Serial.print("now_speed: ");
	Serial.println(now_speed);
*/
	while(now_speed < speed){
		now_speed += min(MAX_STEP, speed - now_speed);
		//Serial.print("add to: ");
		//Serial.println(now_speed);
		run(now_speed);
		delay(DELAY);
	}

	while(now_speed > speed){
		now_speed -= min(MAX_STEP, now_speed - speed);
		//Serial.print("sub to: ");
		//Serial.println(now_speed);
		run(now_speed);
		delay(DELAY);	
	}
}





