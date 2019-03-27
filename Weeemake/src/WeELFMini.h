#ifndef _WeELFMini_H
#define _WeELFMini_H

#include <Arduino.h>
#include "WeConfig.h"
#include "LinkedList.h"

#include "WeDCMotor.h"

#include "WeLineFollower.h"
#include "WeUltrasonicSensor.h"
#include "WeLEDPanelModuleMatrix.h"
#include "WeBuzzer.h"
#include "WeLightSensor.h"
#include "WeSoundSensor.h"
#include "WeButton.h"
#include "WeRGBLed.h"
#include "WeInfraredReceiver.h"
#include "WeTemperature.h"
#include "WeSlidingPotentiometer.h"
#include "WePotentiometer.h"
#include "WeGasSensor.h"
#include "We4LEDButton.h"
#include "We7SegmentDisplay.h"
#include "WeHumiture.h"
#include "We130DCMotor.h"
#include "WeSingleLineFollower.h"
#include "WeIRAvoidSensor.h"
#include "WeRelay.h"
#include "WeTouchSensor.h"
#include "WeRGBLED_RJ.h"
#include "WeTiltSwitch.h"
#include "WePIRSensor.h"
#include "WeFlameSensor.h"
#include "WeJoystick.h"
#include "WeLimitSwitch.h"
#include "WeColorSensor.h"
#include "WeGyroSensor.h"
#include "WeCompassSensor.h"
#include "WeSingleLED.h"
#include "WeWaterAtomizer.h"
#include "WeMP3.h"
#include "WeOLED.h"
#include "WeEncoderMotor.h"
#include "WeLEDLineFollower.h"
#include "WeBarometerSensor.h"
#include "WePM25Sensor.h"
#include "WeFunnyTouchSensor.h"
#include "WeUVSensor.h"
#include "WeWaterSensor.h"
#include "WeServo.h"

#define PORT_A  (A5)
#define PORT_B  (A4)
#define PORT_C  (A2)
#define PORT_D  (A1)

#define OnBoard_Buzzer        (7)
#define OnBoard_IR            (2)
#define OnBoard_Light         (A7)
#define OnBoard_Sound         (A3)

#define MINI_LEFT_YELLOW   4
#define MINI_LEFT_RED      3
#define MINI_RIGHT_RED     A0
#define MINI_RIGHT_YELLOW  13

#define M1      (0x01)
#define M2      (0x02)


WePort_TwoSig WetwoPort[12] =
{
    { NC, NC }, {  10,  9}, { 5, 6 }, { NC, NC }, {  NC,  NC },
	{ NC, NC }, { NC, NC }, { NC, NC }, { NC, NC }, {  NC,  NC },
	{  NC, NC }, { NC, NC },
};

void setfastPWM()
{
	// TCCR1A = _BV(WGM10);
	// TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);
	
//	TCCR2A = _BV(WGM21) | _BV(WGM20);
//	TCCR2B = _BV(CS22);

}

void LED_LEFT_RED(bool sig)
{
  pinMode(MINI_LEFT_RED, OUTPUT);
  digitalWrite(MINI_LEFT_RED, sig);	
}
void LED_RIGHT_RED(bool sig)
{
  pinMode(MINI_RIGHT_RED, OUTPUT);
  digitalWrite(MINI_RIGHT_RED, sig);
}
void LED_LEFT_YELLOW(bool sig)
{
  pinMode(MINI_LEFT_YELLOW, OUTPUT);
  digitalWrite(MINI_LEFT_YELLOW, sig);
}
void LED_RIGHT_YELLOW(bool sig)
{
  pinMode(MINI_RIGHT_YELLOW, OUTPUT);
  digitalWrite(MINI_RIGHT_YELLOW, sig);
}

#endif 
