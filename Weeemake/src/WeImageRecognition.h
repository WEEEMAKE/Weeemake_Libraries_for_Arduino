
#ifndef WeImageRecognition_H
#define WeImageRecognition_H

#include "WePort.h"

class WeImageRecognition
{
public:

   WeImageRecognition(uint8_t port);
   void reset(uint8_t port);
   bool getLab(void);
   void setAutoTrackingMode(void);
   bool getAutoPosition(void);
   bool getColorPosition(uint8_t num);
   void setLabColor1(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB);
   void setLabColor2(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB);
   void setLabColor3(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB);
   void setLabColor4(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB);
   void setLabColor5(int8_t minL,int8_t maxL,int8_t minA,int8_t maxA,int8_t minB,int8_t maxB);
   bool getAppColorPosition(uint8_t num);
   void setLineFollowerMode(void);
   void setLineFollowerThreshold(uint8_t min,uint8_t max);
   bool getLineFollowerAngle(void);
   bool getLineFollowerAxis(void);
   void setPixelsThreshold(uint8_t num);
   bool getColorAllPosition(uint8_t num);
   bool getAppColorAllPosition(uint8_t num);
   void resetColorMode(uint8_t time);
   bool getFacePositon(void);
   void fastMode(bool mode=1);
   uint8_t getTrafficSigns(void);
   void setCardSignsMode(uint8_t num=20);
   uint8_t getCardSigns1(void);

   void setMode(uint8_t);
   bool updateMode(uint8_t);
   uint16_t getValue(uint8_t);
   
   int8_t  minL, maxL, minA, maxA, minB, maxB,angle;
   uint16_t centerX,centerY,pixels,frameX,frameY,high,width,rotation;
   uint8_t linex1,linex2,linex3,linex4,linex5;
   float density;
 private:
	WeOneWire _WeImageRecognition;
	uint8_t uartData[15]={0};
};

#endif

