#include <WeELF328P.h>

WeBluetoothController ps2;
WeOLED oled_A(PORT_A);

void setup()
{
	Serial.begin(115200);
	oled_A.clearScreen();
}

void loop()
{
	ps2.loop();
    bool flag=(ps2.readAnalog(WeJOYSTICK_LX)!=128)||
              (ps2.readAnalog(WeJOYSTICK_LY)!=128)||
              (ps2.buttonPressed(WeBUTTON_BL))||
              (ps2.readAnalog(WeJOYSTICK_RX)!=128)||
              (ps2.readAnalog(WeJOYSTICK_RY)!=128)||
              (ps2.buttonPressed(WeBUTTON_BR))||
              (ps2.buttonPressed(WeBUTTON_L))||
              (ps2.buttonPressed(WeBUTTON_ZL))||
              (ps2.buttonPressed(WeBUTTON_R))||
              (ps2.buttonPressed(WeBUTTON_ZR))||
              (ps2.buttonPressed(WeBUTTON_UP))||
              (ps2.buttonPressed(WeBUTTON_DOWN))||
              (ps2.buttonPressed(WeBUTTON_LEFT))||
              (ps2.buttonPressed(WeBUTTON_RIGHT))||
              (ps2.buttonPressed(WeBUTTON_A))||
              (ps2.buttonPressed(WeBUTTON_B))||
              (ps2.buttonPressed(WeBUTTON_X))||
              (ps2.buttonPressed(WeBUTTON_Y))||
              (ps2.buttonPressed(WeBUTTON_MINUS))||
              (ps2.buttonPressed(WeBUTTON_PLUS))||
              (ps2.buttonPressed(WeBUTTON_MODE))||
              (ps2.buttonPressed(WeBUTTON_HOME));   
    if(flag){
        if(ps2.readAnalog(WeJOYSTICK_LX)!=128){
            oled_A.showString(0,0,"Lx:");
            oled_A.showString(25,0,"   ");
            oled_A.showNum(25,0,ps2.readAnalog(WeJOYSTICK_LX));
        }
        if(ps2.readAnalog(WeJOYSTICK_LY)!=128){
            oled_A.showString(0,1,"Ly:");
            oled_A.showString(25,1,"   ");
            oled_A.showNum(25,1,ps2.readAnalog(WeJOYSTICK_LY));
        }

        if(ps2.buttonPressed(WeBUTTON_BL)){
            oled_A.showString(0,3,"BL");
        }

        if(ps2.readAnalog(WeJOYSTICK_RX)!=128){
            oled_A.showString(60,0,"Rx:");
            oled_A.showString(85,0,"   ");
            oled_A.showNum(85,0,ps2.readAnalog(WeJOYSTICK_RX));
        }
        if(ps2.readAnalog(WeJOYSTICK_RY)!=128){
            oled_A.showString(60,1,"Ry:");
            oled_A.showString(85,1,"   ");
            oled_A.showNum(85,1,ps2.readAnalog(WeJOYSTICK_RY));
        }
        
        if(ps2.buttonPressed(WeBUTTON_BR)){
            oled_A.showString(60,3,"BR");
        }
        
        if(ps2.buttonPressed(WeBUTTON_L)){
            oled_A.showString(0,4," L");
        }

        if(ps2.buttonPressed(WeBUTTON_ZL)){
            oled_A.showString(0,5,"ZL");
        }

        if(ps2.buttonPressed(WeBUTTON_R)){
            oled_A.showString(0,6," R");
        }

        if(ps2.buttonPressed(WeBUTTON_ZR)){
            oled_A.showString(0,7,"ZR");
        }

        if(ps2.buttonPressed(WeBUTTON_UP)){
            oled_A.showString(30,4,"UP");
        }

        if(ps2.buttonPressed(WeBUTTON_DOWN)){
            oled_A.showString(30,5,"DOWN");
        }

        if(ps2.buttonPressed(WeBUTTON_LEFT)){
            oled_A.showString(30,6,"LEFT");
        }

        if(ps2.buttonPressed(WeBUTTON_RIGHT)){
            oled_A.showString(30,7,"RIGHT");
        }

        if(ps2.buttonPressed(WeBUTTON_A)){
            oled_A.showString(76,4,"A");
        }

        if(ps2.buttonPressed(WeBUTTON_B)){
            oled_A.showString(76,5,"B");
        }

        if(ps2.buttonPressed(WeBUTTON_X)){
            oled_A.showString(76,6,"X");
        }

        if(ps2.buttonPressed(WeBUTTON_Y)){
            oled_A.showString(76,7,"Y");
        }

        if(ps2.buttonPressed(WeBUTTON_MINUS)){
            oled_A.showString(95,4,"-");
        }

        if(ps2.buttonPressed(WeBUTTON_PLUS)){
            oled_A.showString(95,5,"+");
        }

        if(ps2.buttonPressed(WeBUTTON_MODE)){
            oled_A.showString(95,6,"MODE");
        }

        if(ps2.buttonPressed(WeBUTTON_HOME)){
            oled_A.showString(95,7,"HOME");
        }
    }else{
       oled_A.clearScreen(); 
    }

}
