
#ifndef WeLEDPanelModuleMatrix_H
#define WeLEDPanelModuleMatrix_H

#include "WePort.h"

class WeLEDPanelModuleMatrix
{
public:
  void reset(uint8_t port);
  void setBrightness(uint8_t Bright);
  void clearScreen(void);
  void writePanelData(void);
  void showPanel(void);
  void showLine(uint8_t x,uint8_t buffer);
  void turnOnDot(uint8_t x,uint8_t y);
  void turnOffDot(uint8_t x,uint8_t y);
  void setDot(uint8_t x,uint8_t y,bool isOn);
  void showChar(int8_t X_position,int8_t Y_position,const char *str);
  void showChar(int8_t X_position,int8_t Y_position,String str);
  void showClock(uint8_t hour, uint8_t minute, bool point_flag);
  void showNum(float value);
  void writeChar(int8_t X_position,int8_t Y_position,uint8_t buffer);
  void showBitmap(int8_t x, int8_t y, uint8_t *data);
protected:
  WeLEDPanelModuleMatrix(uint8_t port, uint8_t width, uint8_t height);
private:
	WeOneWire _WeLEDPanel;
  volatile uint8_t Display_Buffer[21]={0};
	uint8_t panel_width;
	uint8_t panel_height;
};

class WeLEDPanelModuleMatrix7_21: public WeLEDPanelModuleMatrix
{
public:
  WeLEDPanelModuleMatrix7_21(uint8_t port=0);
  void showNum(float value);
  void showBitmap2(int8_t x, int8_t y, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15, uint8_t v16, uint8_t v17, uint8_t v18, uint8_t v19, uint8_t v20);
};

class WeLEDPanelModuleMatrix5_14: public WeLEDPanelModuleMatrix
{
public:
  WeLEDPanelModuleMatrix5_14(uint8_t port=0);
  void showNum(float value);
  void showBitmap2(int8_t x, int8_t y, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13);
};

#endif

