#ifndef _WeELF328P_H
#define _WeELF328P_H

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
#include "WeUSBHost.h"
#include "WeGestureSensor.h"
#include "WeImageRecognition.h"
#include "WeSpeechRecognition.h"
#include "WeVibrationMotor.h"
#include "WeBluetoothController.h"
#include "WeAdapter.h"
#include "WeWifi.h"
#include "WeServo360.h"
#include "WeSmartIRModule.h"
#include "We36EncoderMotor.h"

#define PORT_0  (13)
#define PORT_1  (A0)
#define PORT_2  (A1)
#define PORT_3  (A5)
#define PORT_4  (A4)
#define PORT_5  (A3)
#define PORT_6  (A2)
#define PORT_A  (9)
#define PORT_B  (10)
#define PORT_C  (12)
#define PORT_D  (4)

#define OnBoard_RGB           (3)
#define OnBoard_Button        (2)
#define OnBoard_Buzzer        (11)


#define M1      (0x01)
#define M2      (0x02)
#define M3      (0x03)
#define M4      (0x04)
#define M5      (0x05)
#define M6      (0x06)
#define M7      (0x07)
#define M8      (0x08)
#define M9      (0x09)
#define M10     (0x0A)


WePort_TwoSig WetwoPort[12] =
{
    { NC, NC }, { 6, 7 }, {  5,  8 }, { A5, 1 }, {  A5,  2 },
	{ A4, 1 }, { A4, 2 }, { A3, 1 }, { A3, 2 }, {  A2,  1 },
	{  A2,  2 }, { NC, NC },
};
void setfastPWM()
{
	
}


#endif 
