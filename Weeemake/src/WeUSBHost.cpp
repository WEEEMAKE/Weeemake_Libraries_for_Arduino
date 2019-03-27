
#include "WeUSBHost.h"

//#define CH375_DBG

#define p_dev_descr ((PUSB_DEV_DESCR)RECV_BUFFER)
#define p_cfg_descr ((PUSB_CFG_DESCR_LONG)RECV_BUFFER)

uint8_t endp_out_addr;
uint8_t endp_out_size;
uint8_t endp_in_addr;
uint8_t endp6_mode, endp7_mode;

uint8_t *cmd_buf;
uint8_t *ret_buf;
PUSB_ENDP_DESCR tmpEp;


WeUSBHost::WeUSBHost(uint8_t receivePin, uint8_t transmitPin)
{
  HSerial = new WeSerial(receivePin,transmitPin);
}

uint8_t WeUSBHost::CH375_RD()
{
  delay(2); // stupid delay, the chip don't got any buffer
  if(HSerial->available()){
	   uint8_t c = HSerial->read();
	   return c;
	  }
  return 0;
}

void WeUSBHost::CH375_WR(uint8_t c)
{
  HSerial->write(c);
  delay(2);
  
}

int16_t WeUSBHost::set_usb_mode(int16_t mode)
{
  CH375_WR(CMD_SET_USB_MODE);
  CH375_WR(mode);
  endp6_mode=endp7_mode=0x80;
  return CH375_RD();
}

uint8_t WeUSBHost::getIrq()
{
  CH375_WR(CMD_GET_STATUS);
  delay(20);
  return CH375_RD();
}

void WeUSBHost::toggle_send()
{
#ifdef CH375_DBG
  Serial.print("toggle send: 0x");
  Serial.print(endp7_mode,HEX);
  Serial.println();
#endif
  CH375_WR(CMD_SET_ENDP7);
  CH375_WR( endp7_mode );
  endp7_mode^=0x40;
}

void WeUSBHost::toggle_recv()
{
  CH375_WR( CMD_SET_ENDP6 );
  CH375_WR( endp6_mode );
#ifdef CH375_DBG
  Serial.print("toggle recv: 0x");
  Serial.print(endp6_mode,HEX);
  Serial.println();
#endif
  endp6_mode^=0x40;
}

uint8_t WeUSBHost::issue_token( uint8_t endp_and_pid )
{
  CH375_WR( CMD_ISSUE_TOKEN );
  CH375_WR( endp_and_pid );  /* Bit7~4 for EndPoint No, Bit3~0 for Token PID */
#ifdef CH375_DBG
  Serial.print("issue token: 0x");
  Serial.print(endp_and_pid,HEX);
  Serial.println();
#endif
  delay(2);
  return getIrq();
}

void WeUSBHost::wr_usb_data( uint8_t len, uint8_t *buf )
{
#ifdef CH375_DBG
  Serial.print("usb wr: ");
  Serial.print(len,DEC);
  Serial.println();
#endif
  CH375_WR( CMD_WR_USB_DATA7 );
  CH375_WR( len );
  while( len-- ){
    CH375_WR( *buf++ );
  }
}

uint8_t WeUSBHost::rd_usb_data( uint8_t *buf )
{
  uint8_t i, len;
  CH375_WR( CMD_RD_USB_DATA );
  len=CH375_RD();
#ifdef CH375_DBG
  Serial.print("usb rd: ");
  Serial.print(len,DEC);
  Serial.println();
#endif
  for ( i=0; i!=len; i++ ) 
  {
    *buf++=CH375_RD();
  }
  return( len );
}

int16_t WeUSBHost::get_version()
{
  CH375_WR(CMD_GET_IC_VER);
  return CH375_RD();
}

void WeUSBHost::set_freq(void)
{
  CH375_WR(0x0b);
  CH375_WR(0x17);
  CH375_WR(0xd8);
}

uint8_t WeUSBHost::set_addr( uint8_t addr )
{
  uint8_t irq;
  CH375_WR(CMD_SET_ADDRESS);
  CH375_WR(addr);
  irq = getIrq();
  if(irq==USB_INT_SUCCESS)
  {
    CH375_WR(CMD_SET_USB_ADDR);
    CH375_WR(addr);
  }
  return irq;
}

uint8_t WeUSBHost::set_config(uint8_t cfg)
{
  endp6_mode=endp7_mode=0x80; // reset the sync flags
  CH375_WR(CMD_SET_CONFIG);
  CH375_WR(cfg);
  return getIrq();
}

uint8_t WeUSBHost::clr_stall6(void)
{
  CH375_WR( CMD_CLR_STALL );
  CH375_WR( endp_out_addr | 0x80 );
  endp6_mode=0x80;
  return getIrq();
}

uint8_t WeUSBHost::get_desr(uint8_t type)
{
  CH375_WR( CMD_GET_DESCR );
  CH375_WR( type );   /* description type, only 1(device) or 2(config) */
  return getIrq();
}

uint8_t WeUSBHost::host_recv()
{
  uint8_t irq;
  toggle_recv();
  irq = issue_token( ( endp_in_addr << 4 ) | DEF_USB_PID_IN );
  if(irq==USB_INT_SUCCESS)
  {
    int16_t len = rd_usb_data(RECV_BUFFER);
#ifdef CH375_DBG
    for(int16_t i=0;i<len;i++)
    {
      // point hid device
      Serial.print(" 0x");
      Serial.print((int16_t)RECV_BUFFER[i],HEX);
    }
    Serial.println();
#endif
    stallCount = 0;
    return len;
  }
  else if(irq==USB_INT_DISCONNECT)
  {
    device_online = false;
    device_ready = false;
#ifdef CH375_DBG
    Serial.println("##### disconn #####");
#endif
    return 0;
  }
  else
  {
    clr_stall6();
#ifdef CH375_DBG
    Serial.println("##### stall #####");
#endif
    delay(10);
    /*
    stallCount++;
    if(stallCount>10){
      device_online = false;
      device_ready = false;
      resetBus();
    }
    */
    return 0;
  }
}

void WeUSBHost::resetBus()
{
  int16_t c;
  c = set_usb_mode(7);
#ifdef CH375_DBG
  Serial.print("set mode 7: 0x");
  Serial.print(c,HEX);
  Serial.println();
#endif
  delay(10);
  c = set_usb_mode(6);
#ifdef CH375_DBG
  Serial.print("set mode 6: 0x");
  Serial.print(c,HEX);
  Serial.println();
#endif
  delay(10);
}

void WeUSBHost::init(int8_t type)
{
  ch375_online = false;
  device_online = false;
  device_ready = false;
  _JSisReady = false;
  usbtype = type; 
  HSerial->begin(9600); 
}


int16_t WeUSBHost::initHIDDevice()
{
  int16_t irq, len, address;
  if(usbtype==USB1_0) set_freq(); //work on a lower freq, necessary for ch375
  irq = get_desr(1);
#ifdef CH375_DBG
  Serial.print("get des irq: 0x");
  Serial.print(irq,HEX);
  Serial.println();
#endif
  if(irq==USB_INT_SUCCESS)
  {
      len = rd_usb_data( RECV_BUFFER );
#ifdef CH375_DBG
      Serial.print("descr1 len: ");
      Serial.print(len,DEC);
      Serial.print(" type: 0x");
      Serial.print(p_dev_descr->bDescriptorType,HEX);
      Serial.println();
#endif
      irq = set_addr(2);
      if(irq==USB_INT_SUCCESS)
      {
        irq = get_desr(2); // max buf 64byte, todo:config descr overflow
        if(irq==USB_INT_SUCCESS)
        {
          len = rd_usb_data( RECV_BUFFER );
#ifdef CH375_DBG
          Serial.print("descr1 len: ");
          Serial.print(len,DEC);
          Serial.print(" class: 0x");
          Serial.print(p_cfg_descr->itf_descr.bInterfaceClass,HEX);
          Serial.print(" subclass: 0x");
          Serial.print(p_cfg_descr->itf_descr.bInterfaceSubClass,HEX);
          Serial.println();

          Serial.print("num of ep: ");
          Serial.print(p_cfg_descr->itf_descr.bNumEndpoints,DEC);
          Serial.println();

          Serial.print("ep0: 0x");
          Serial.print(p_cfg_descr->endp_descr[0].bLength,HEX);
          Serial.print(" 0x");
          Serial.print(p_cfg_descr->endp_descr[0].bDescriptorType,HEX);
          Serial.println();
#endif
          if(p_cfg_descr->endp_descr[0].bDescriptorType==0x21)
          { // skip hid des
            tmpEp = (PUSB_ENDP_DESCR)((int8_t*)(&(p_cfg_descr->endp_descr[0]))+p_cfg_descr->endp_descr[0].bLength); // get the real ep position
          }
#ifdef CH375_DBG
          Serial.print("endpoint: 0x");
          Serial.print(tmpEp->bEndpointAddress,HEX);
          Serial.print(" 0x");
          Serial.print(tmpEp->bDescriptorType,HEX);
          Serial.println();
#endif
          endp_out_addr=endp_in_addr=0;
          address =tmpEp->bEndpointAddress;  /* Address of First EndPoint */
          // actually we only care about the input end points
          if( address&0x80 )
          {
            endp_in_addr = address&0x0f;  /* Address of IN EndPoint */
          }
          else
          {  /* OUT EndPoint */
            endp_out_addr = address&0x0f;
            endp_out_size = p_cfg_descr->endp_descr[0].wMaxPacketSize;
			/* Length of Package for Received Data EndPoint */
            if( endp_out_size == 0 || endp_out_size > 64 )
              endp_out_size = 64;
          }
          // todo: some joystick with more than 2 node
          // just assume every thing is fine, bring the device up
          irq = set_config(p_cfg_descr->cfg_descr.bConfigurationvalue);
          if(irq==USB_INT_SUCCESS)
          {
            CH375_WR( CMD_SET_RETRY );  // set the retry times
            CH375_WR( 0x25 );
            CH375_WR( 0x85 );
            device_ready = true;
            return 1;
          }
        }
      }
  }
  return 0;
}

int16_t WeUSBHost::probeDevice()
{
  int16_t c;
  if(!ch375_online)
  {
    CH375_WR( CMD_CHECK_EXIST);
    CH375_WR( 0x5A);
    c = CH375_RD(); // should return 0xA5
    if(c!=0xA5) return 0;
    
    resetBus();
    ch375_online = false;
  }

  c = getIrq();
  if(c!=USB_INT_CONNECT) return 0;
  resetBus(); // reset bus and wait the device online again
  c=0;
  while(c!=USB_INT_CONNECT)
  {
    delay(500); // some device may need long time to get ready
    c = getIrq();
#ifdef CH375_DBG
    Serial.print("waiting:");
    Serial.println(c,HEX);
#endif
  }
  if( initHIDDevice()==1)
    device_online=true;
    
}

bool WeUSBHost::ButtonPressed(uint8_t button)
{
    return  ps2_data_list[button];
}


void WeUSBHost::printValue(void)
{
	int i = 0;
	for(i=0;i<18;i++)
	{
	  Serial.print(js_buf[i]);	   
	  Serial.print('-');
	} 
	Serial.print(js_buf[18]);	
	Serial.println(' ');
}
uint8_t WeUSBHost::readAnalog(uint8_t button)
{
    return  js_buf[button+1];
}
uint8_t WeUSBHost::joystickRx(void)
{
	return (js_buf[5]);
}
uint8_t WeUSBHost::joystickRy(void)
{
   return (js_buf[6]);
}
uint8_t WeUSBHost::joystickLx(void)
{
	return (js_buf[3]);
}
uint8_t WeUSBHost::joystickLy(void)
{
	return (js_buf[4]);
}

uint8_t WeUSBHost::joystick(uint8_t dir, uint8_t axis)
{
  uint8_t index = (dir ? 5 : 3) + (axis ? 1 : 0);
  return js_buf[index];
}

void WeUSBHost::parseJoystick(uint8_t *buf)
{
  int i = 0;
  for(i = 0; i < 19; i++)
  {
    js_buf[i] = buf[i];
  }

    ps2_data_list[WeJOYSTICK_UP_L] = js_buf[9] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_DOWN_L] = js_buf[10] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_LEFT_L] = js_buf[8] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_RIGHT_L] = js_buf[7] > 0 ? true : false;
	
    ps2_data_list[WeJOYSTICK_START] = (js_buf[1] & 0x02) == 0x02 ? true : false;
    ps2_data_list[WeJOYSTICK_SELECT] = (js_buf[1] & 0x01) == 0x01 ? true : false;
	ps2_data_list[WeJOYSTICK_MODE] = (js_buf[1] & 0x10) == 0x10 ? true : false;
	
    ps2_data_list[WeJOYSTICK_BUTTON_L] = (js_buf[1] & 0x04) == 0x04 ? true : false; 
    ps2_data_list[WeJOYSTICK_BUTTON_R] = (js_buf[1] & 0x08) == 0x08 ? true : false;
	
    ps2_data_list[WeJOYSTICK_L1] = js_buf[15] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_R1] = js_buf[16] > 0 ? true : false;
	ps2_data_list[WeJOYSTICK_L2] = js_buf[17] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_R2] = js_buf[18] > 0 ? true : false;
	
    ps2_data_list[WeJOYSTICK_UP_R] = js_buf[11] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_DOWN_R] = js_buf[13] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_LEFT_R] = js_buf[14] > 0 ? true : false;
    ps2_data_list[WeJOYSTICK_RIGHT_R] = js_buf[12] > 0 ? true : false;
  
  delay(2);
}

void WeUSBHost::loop(void)
{
  if(!device_online)
  {
    probeDevice();
    Serial.println("try again ...");
    delay(1000);
  }
  else
  {
    int len = host_recv();
    parseJoystick(RECV_BUFFER);
    delay(2);
  }
}
