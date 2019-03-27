#include"OLED.h"

void OLED::writeCommand(uint8_t cmdByte)
{
	iic_start();
	iic_write_byte(0x78);  //device addr 0x78
	iic_ack();
	iic_write_byte(0x00);
	iic_ack();
	iic_write_byte(cmdByte);
	iic_ack();
	iic_stop();
}

void OLED::writeData(uint8_t dataByte)
{
	iic_start();
	iic_write_byte(0x78);
	iic_ack();
	iic_write_byte(0x40);
	iic_ack();
	iic_write_byte(dataByte);
	iic_ack();
	iic_stop();
}

void OLED::init(void)
{
	writeCommand(0xAE);  //display off
	writeCommand(0x00);//---set low column address
	writeCommand(0x10);//---set high column address
	writeCommand(0x40);//--set start line address
	writeCommand(0xB0);//--set page address
	writeCommand(0x81); // contract control
	writeCommand(0xFF);//--128
	writeCommand(0xA1);//set segment remap
	writeCommand(0xA6);//--normal / reverse
	writeCommand(0xA8);//--set multiplex ratio(1 to 64)
	writeCommand(0x3F);//--1/32 duty
	writeCommand(0xC8);//Com scan direction
	writeCommand(0xD3);//-set display offset
	writeCommand(0x00);//

	writeCommand(0xD5);//set osc division
	writeCommand(0x80);//

	writeCommand(0xD8);//set area color mode off
	writeCommand(0x05);//

	writeCommand(0xD9);//Set Pre-Charge Period
	writeCommand(0xF1);//

	writeCommand(0xDA);//set com pin configuartion
	writeCommand(0x12);//

	writeCommand(0xDB);//set Vcomh
	writeCommand(0x30);//

	writeCommand(0x8D);//set charge pump enable
	writeCommand(0x14);//

	writeCommand(0xAF);//--turn on oled panel
}

void OLED::screenClear(void)
{
	uint8_t x_index,y_index;
	writeCommand(0x20);    //set memory addressing mode
	writeCommand(0x02);	   //page addressing mode
	for (x_index = 0; x_index < 8; ++x_index){
		writeCommand(0xB0+x_index);
		writeCommand(0x00);
		writeCommand(0x10);
		for (y_index = 0; y_index < 128; ++y_index){
			writeData(0x00);
		}
	}
}

void OLED::showString(uint8_t row, uint8_t col, uint8_t (*str)[16], uint8_t stringSize)
{
	uint8_t i,j;
	writeCommand(0xB0+(row*2-2));  //page 0
	writeCommand(col&0x0F);  //low
	writeCommand(0x10|(col>>4)); //high
	for ( j = 0; j < stringSize; ++j){
		for (i = 0; i < 8; ++i){
			writeData(str[j][i]);
		}
	}

	writeCommand(0xB1+(row*2-2));  //page 1
	writeCommand(col&0x0F);    //low
	writeCommand(0x10|(col>>4)); //high
	for (j = 0; j < stringSize; ++j){
		for (i = 0; i < 8; ++i){
			writeData(str[j][i]);
		}	
	}
}

void OLED::showCharacterOfChinese(uint8_t row,uint8_t col,uint8_t (*characterChinese)[32],uint8_t characterSize){
	uint8_t i,j;
	writeCommand(0xb0+(row*2-2)); //page 0
	writeCommand(col&0x0f); //low
	writeCommand(0x10|(col>>4)); //high
	for(j=0;j<characterSize;j++){
		for(i=0;i<16;i++){
			writeData(characterChinese[j][i]);//Ð´Êý¾ÝoledTable1
		}
	}

	writeCommand(0xb1+(row*2-2)); //page 1
	writeCommand(col&0x0f); //low
	writeCommand(0x10|(col>>4)); //high
	for(j=0;j<characterSize;j++){
		for(i=16;i<32;i++){
		  writeData(characterChinese[j][i]);//Ð´Êý¾ÝoledTable1
		}
	}
}

void OLED::showImage(uint8_t (*oledImageTable)[128]){
	uint8_t i,j;

	for(j=0;j<8;j++){
		writeCommand(0xb0+j); //page 0
		writeCommand(0x00); //low
		writeCommand(0x10); //high
		for(i=0;i<128;i++){
			writeData(pgm_read_byte_near((*(oledImageTable+j))+i));//Ð´Êý¾ÝoledImageTable
		}
	}
} 