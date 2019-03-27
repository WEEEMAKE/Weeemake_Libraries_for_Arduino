#include "WeELF328P.h"

WeInfraredReceiver ir(PORT_2);

void setup()
{  
  ir.begin(); 
  Serial.begin(9600);
}
void get_ir_command()
{
  if (ir.decode())
  {
    uint32_t value = ir.value;
    switch (value >> 16 & 0xff)
    {
      case IR_CONTROLLER_A:    Serial.println("A");break;
      case IR_CONTROLLER_B:    Serial.println("B");break;
      case IR_CONTROLLER_C:    Serial.println("C");break;
      case IR_CONTROLLER_D:    Serial.println("D");break;
      case IR_CONTROLLER_E:    Serial.println("E");break;
      case IR_CONTROLLER_F:    Serial.println("F");break;
      case IR_CONTROLLER_UP:   Serial.println("UP");break;
      case IR_CONTROLLER_LEFT: Serial.println("LEFT");break;
      case IR_CONTROLLER_RIGHT:Serial.println("RIGHT");break;
      case IR_CONTROLLER_DOWN: Serial.println("DOWN");break;
      case IR_CONTROLLER_OK:   Serial.println("OK");break;
      case IR_CONTROLLER_0:    Serial.println("0");break;
      case IR_CONTROLLER_1:    Serial.println("1");break;
      case IR_CONTROLLER_2:    Serial.println("2");break;
      case IR_CONTROLLER_3:    Serial.println("3");break;
      case IR_CONTROLLER_4:    Serial.println("4");break;
      case IR_CONTROLLER_5:    Serial.println("5");break;
      case IR_CONTROLLER_6:    Serial.println("6");break;
      case IR_CONTROLLER_7:    Serial.println("7");break;
      case IR_CONTROLLER_8:    Serial.println("8");break;
      case IR_CONTROLLER_9:    Serial.println("9");break;
    }
  }
}

void loop() 
{
    get_ir_command();
}
