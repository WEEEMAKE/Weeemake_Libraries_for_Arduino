#include "WeELF328P.h"

WePM25Sensor pm25Sensor(PORT_D);

void setup()
{  
  Serial.begin(115200);
  delay(2000);
  pm25Sensor.setFanLaser(1);
  delay(100);
}
void loop() 
{
  Serial.print("SensorData : ");
  // Serial.print(pm25Sensor.readPm1_0Concentration());
  Serial.print(pm25Sensor.readPm2_5Concentration());
  // Serial.print(pm25Sensor.readPm10Concentration());
  // Serial.print(pm25Sensor.read0_3NumIn100ml());
  // Serial.print(pm25Sensor.read0_5NumIn100ml());
  // Serial.print(pm25Sensor.read1_0NumIn100ml());
  // Serial.print(pm25Sensor.read2_5NumIn100ml());
  // Serial.print(pm25Sensor.read5_0NumIn100ml());
  // Serial.print(pm25Sensor.read10NumIn100ml());
  Serial.println(" ug/m^3");
  delay(200);
}
