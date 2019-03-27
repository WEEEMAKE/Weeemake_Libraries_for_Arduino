#include <WeELF328P.h>

// WeLEDLineFollower ledLineFollower6_8K(PORT_A);
WeLEDLineFollower ledLineFollower10K(PORT_B);
// WeOneWire portDetect(PORT_A); 

WeOLED oled(PORT_D);

void setup()
{
	Serial.begin(115200);
	// portDetect.reset();
 //    portDetect.write_byte(0x01);
 //    portDetect.respond();
 //    uint8_t sensorType = portDetect.read_byte();
 //    Serial.println(sensorType);
	  //oled.setdigits(2); //   0.01
	   oled.setSize(16);  //    8or16
	   oled.clearScreen();
	ledLineFollower10K.openLED();
}

void loop()
{
	// ledLineFollower6_8K.openLED();
	// ledLineFollower10K.openLED();
// oled.clearScreen();
// delay(50);
// 	// oled.showString(0,0,"6.8K:");
// 	// oled.showNum(40,0,ledLineFollower6_8K.readSensor());

// 	oled.showString(0,3,"10K:");
// 	oled.showNum(40,3,ledLineFollower10K.readSensor());
    if (Serial.available() > 0) {

            // say what you got:
            Serial.print("I received: ");
            Serial.println((char)(Serial.read()));
            Serial.println(ledLineFollower10K.readSensor());
    }

	

	
	// Serial.println(ledLineFollower.readSensor());
	delay(100);
}