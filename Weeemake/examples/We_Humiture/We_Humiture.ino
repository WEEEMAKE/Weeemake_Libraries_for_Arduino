#include "WeELF328P.h"

WeHumiture humiture(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  humiture.startRead();
  Serial.print("Humidity (%) =");
  Serial.print( humiture.getHumidity() );
  Serial.print(", Temperature (oC) =");
  Serial.println( humiture.getTemperature() );
  delay(1200);
}
