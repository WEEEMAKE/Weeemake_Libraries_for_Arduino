#ifndef _WEELFPI_H
#define _WEELFPI_H

#include <Arduino.h>
#include "WeConfig.h"
#include "LinkedList.h"

#include "WeDCMotor.h"

#include "WeLineFollower.h"
#include "WeUltrasonicSensor.h"
#include "WeLEDPanelModuleMatrix.h"
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
#include "WeStepperMotor.h"
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
#include "WeGestureSensor.h"
#include "WeVibrationMotor.h"
#include "WeAdapter.h"
#include "WeServo360.h"
#include "WeSmartIRModule.h"
#include "We36EncoderMotor.h"

#define PORT_1  (14)
#define PORT_2  (15)
#define PORT_3  (2)
#define PORT_4  (3)

#define PORT_A  (4)
#define PORT_B  (5)
#define PORT_C  (6)
#define PORT_D  (9)

#define OnBoard_Button        (21)

#define M3      (0x03)
#define M4      (0x04)
#define M5      (0x05)
#define M6      (0x06)
#define M7      (0x07)
#define M8      (0x08)
#define M9      (0x09)
#define M10      (0x10)


WePort_TwoSig WetwoPort[12] =
{
    { NC, NC },{ NC, NC },{ NC, NC }, {PORT_1,1}, {PORT_1,2 },
	{ PORT_2,1 }, {PORT_2, 2 }, { PORT_3, 1 }, { PORT_3, 2 }, { PORT_4,1}, 
	{ PORT_4,2}, {  NC,  NC }
};
void setfastPWM()
{
	
}


#endif 
