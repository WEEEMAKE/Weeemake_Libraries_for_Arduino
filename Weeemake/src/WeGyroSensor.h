#ifndef _WeGyroSensor_H
#define _WeGyroSensor_H

#include "WePort.h"

class WeGyroSensor
{
public:

  WeGyroSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  void begin(void);
  void update(void);
  double getAngleX(void);
  double getAngleY(void);
  double getAngleZ(void);
  double getGyroX(void);
  double getGyroY(void);
  double getGyroZ(void);
  void Calibration(void);
  double readValue(uint8_t index);
  double getGyration(uint8_t index);
  double getAcceleration(uint8_t index);
 
  
private:
	WeOneWire _WeGyroSensor;
	double  gSensitivity = 65.5;; /* for 500 deg/s, check data sheet */
    double  gx=0, gy=0, gz=0;
    double  gyrX=0, gyrY=0, gyrZ=0;
    int16_t accX=0, accY=0, accZ=0;
    double  gyrXoffs=0, gyrYoffs=0, gyrZoffs=0;
    uint8_t i2cData[14];
};

#endif

