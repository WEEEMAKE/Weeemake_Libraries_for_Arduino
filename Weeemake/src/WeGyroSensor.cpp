#include "WeGyroSensor.h"


WeGyroSensor::WeGyroSensor(uint8_t port)
{
  _WeGyroSensor.reset(port);
}
void WeGyroSensor::reset(uint8_t port)
{
  _WeGyroSensor.reset(port);
}
void WeGyroSensor::begin(void)
{
  long xSum = 0, ySum = 0, zSum = 0;
  int8_t return_value;
  uint16_t x = 0;
  uint16_t num = 50;
  for(x = 0; x < num; x++)
  {
    if(_WeGyroSensor.reset()!=0)
		return ;
    _WeGyroSensor.write_byte(0x03);
    _WeGyroSensor.respond();
    for(int i=0;i<6;i++)
    {
      i2cData[i]=_WeGyroSensor.read_byte();
    }
    xSum += ( (i2cData[0] << 8) | i2cData[1] );
    ySum += ( (i2cData[2] << 8) | i2cData[3] );
    zSum += ( (i2cData[4] << 8) | i2cData[5] );
  }
  gyrXoffs = xSum / num;
  gyrYoffs = ySum / num;
  gyrZoffs = zSum / num;
  
}

void WeGyroSensor::Calibration(void)
{
    if(_WeGyroSensor.reset()!=0)
    return ;
    _WeGyroSensor.write_byte(0x04);
    _WeGyroSensor.respond();
    for(int i=0;i<6;i++)
    {
      i2cData[i]=_WeGyroSensor.read_byte();
    }
    gyrXoffs = ( (i2cData[1] << 8) | i2cData[0] );
    gyrYoffs = ( (i2cData[3] << 8) | i2cData[2] );
    gyrZoffs = ( (i2cData[5] << 8) | i2cData[4] );
}

void  WeGyroSensor::update(void)
{
  static unsigned long	last_time = 0;
  int8_t return_value;
  double dt, filter_coefficient;

  dt = (double)(millis() - last_time) / 1000.0;
  last_time = millis();

  /* read imu data */
  if(_WeGyroSensor.reset()!=0)
		  return ;
	  _WeGyroSensor.write_byte(0x02);
	  _WeGyroSensor.respond();
	  for(int i=0;i<14;i++)
	  {
		i2cData[i]=_WeGyroSensor.read_byte();
	  }
  double ax, ay, az;
  /* assemble 16 bit sensor data */
  accX = ( (i2cData[0] << 8) | i2cData[1] );
  accY = ( (i2cData[2] << 8) | i2cData[3] );
  accZ = ( (i2cData[4] << 8) | i2cData[5] );  
  gyrX = ( ( (i2cData[8] << 8) | i2cData[9] ) - gyrXoffs) / gSensitivity;
  gyrY = ( ( (i2cData[10] << 8) | i2cData[11] ) - gyrYoffs) / gSensitivity;
  gyrZ = ( ( (i2cData[12] << 8) | i2cData[13] ) - gyrZoffs) / gSensitivity;  
  ax = atan2(accX, sqrt( pow(accY, 2) + pow(accZ, 2) ) ) * 180 / 3.1415926;
  ay = atan2(accY, sqrt( pow(accX, 2) + pow(accZ, 2) ) ) * 180 / 3.1415926;  

  if(accZ > 0)
  {
    gx = gx - gyrY * dt;
    gy = gy + gyrX * dt;
  }
  else
  {
    gx = gx + gyrY * dt;
    gy = gy - gyrX * dt;
  }
  gz += gyrZ * dt;
  
  gz = gz - 360 * floor(gz / 360);
  if(gz > 180)
  {
    gz = gz - 360;
  }

  gy = 0.98 * gy + 0.02 * ay;
  gx = 0.98 * gx + 0.02 * ax; 
}

double  WeGyroSensor::getAngleX(void)
{
  return gx;
}
double  WeGyroSensor::getAngleY(void)
{
  return gy;
}
double  WeGyroSensor::getAngleZ(void)
{
  return gz;
}
double  WeGyroSensor::getGyroX(void)
{
  return gyrX;
}
double  WeGyroSensor::getGyroY(void)
{
  return gyrY;
}

double WeGyroSensor::getGyroZ(void)
{
  return gyrZ;
}

double WeGyroSensor::readValue(uint8_t index)
{
  update();
  switch(index){
    case 0: return gx;
    case 1: return gy;
    case 2: return gz;
    case 3: return gyrX;
    case 4: return gyrY;
    case 5: return gyrZ;
  }
  return 0;
}

double WeGyroSensor::getGyration(uint8_t index)
{
  return readValue(index % 3);
}

double WeGyroSensor::getAcceleration(uint8_t index)
{
  return readValue(index % 3 + 3);
}

