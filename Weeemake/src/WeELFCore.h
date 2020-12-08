#ifndef _WeELFCORE_H
#define _WeELFCORE_H

// #include <Arduino.h>
// #include "WeConfig.h"
// #include "LinkedList.h"

// #include "WeDCMotor.h"

// #include "WeBuzzer.h"
// #include "WeLightSensor.h"
// #include "WeSoundSensor.h"
// #include "WeButton.h"
// #include "WeRGBLed.h"
// #include "WeInfraredReceiver.h"
// #include "WeInfraredSender.h"
// #include "WeTemperature.h"
// #include "WeGasSensor.h"
// #include "We7SegmentDisplay.h"
// #include "WeRGBLED_RJ.h"

#include <Arduino.h>
#include "WeConfig.h"
#include "LinkedList.h"

#include "WeDCMotor_S.h"

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
#include "WeInfraredSender.h"

#include "WeBluetoothController.h"
#include "WeAdapter.h"

#define PORT_A  (A1)
#define PORT_B  (A2)
#define PORT_C  (A3)
#define PORT_D  (A4)

#define OnBoard_RGB         (A0)
#define OnBoard_Light       (A7)
#define OnBoard_Button      (3)
#define OnBoard_Buzzer      (4)
#define OnBoard_IR          (2)
#define OnBoard_IR_T        (12)

#define M1      (0x01)
#define M2      (0x02)

WePort_TwoSig WetwoPort[12] =
{
    { NC, NC }, {  5, 8}, { 6, 7 }, { NC, NC }, {  NC,  NC },
	{ NC, NC }, { NC, NC }, { NC, NC }, { NC, NC }, {  NC,  NC },
	{  NC, NC }, { NC, NC },
};
void setfastPWM()
{
	
}


#endif 
