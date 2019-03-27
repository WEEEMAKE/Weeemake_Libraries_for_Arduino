
#ifndef WeUSBHost_H
#define WeUSBHost_H

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include "WeSerial.h"


#define USB2_0 1
#define USB1_0 0

#define	CH375_MAX_DATA_LEN	0x40			/* max package length */

#define	CMD_CHECK_EXIST		0x06			/* Chip check */
	/* Input: any (ep:0x12)*/
	/* Output: output inverse of input (ep:0x21) */

#define	CMD_SET_USB_MODE	0x15			/* Setup the module work mode, with enable or disable state */
	/* Input: mode */
	/*		 00H=Device mode disabled, 01H=Device mode enabled with external firmware, 02H=Device mode enabled with internal firmware, 03H=Device mode enabled with internal firmware and interrupt endpoint */
	/*		 04H=Host Mode disabled, 05H=Host Mode enabled, 06H=Host Mode enabled with SOF package, 07H=Host Mode enabled and reset USB bus */
	/* Output: status( CMD_RET_SUCCESS or CMD_RET_ABORT, otherswise unfinished ) */

#define	CMD_SET_ENDP6		0x1C			/* Device Mode: setup endpoint 2 receiver */
#define	CMD_SET_ENDP7		0x1D			/* Device Mode: setup endpoint 2 transmitter */
#define	CMD_GET_STATUS		0x22			/* Get interrupt state */

#define	CMD_RD_USB_DATA		0x28			/* block read from usb device, and release buffer */
#define	CMD_WR_USB_DATA7	0x2B			/* write to usb endpoint 2 */

#define	CMD_SET_RETRY		0x0B			/* Host Mode: setup usb token retry times */
	/* Input: 0x25, setup retry times */
	/*					  bit7=1 for infinite retry, bit3~0 retry times*/

#define	CMD_ISSUE_TOKEN		0x4F			/* Host Mode: issue the token */
	/* Input: token */
	/*			 bit3~0:token type, bit7~4:endpoint */
	/* Output interrupt state */

#define	CMD_CLR_STALL		0x41			/* Host Mode: clear the endpoint Error */
	/* Input: endpoint index */
	/* Output interrupt state */

#define	CMD_SET_ADDRESS		0x45			/* Host Mode: Control-setup usb address */
	/* Input: address */
	/* Output interrupt state */

#define	CMD_GET_DESCR		0x46			/* Host Mode: Control-get descriptor */
	/* Input: descriptor type 0:config 1:device */
	/* Output interrupt state */

#define	CMD_SET_CONFIG		0x49			/* Host Mode: Control-config and enable the device */
	/* Input: config */
	/* Output interrupt state */

#define	CMD_GET_IC_VER		0x01			/* get chip version */
#define	CMD_SET_USB_ADDR	0x13			/* Setup the usb address */
#define	USB_INT_SUCCESS		0x14			/* token successful sent */
#define	USB_INT_CONNECT		0x15			/* detect usb device plug in */
#define	USB_INT_DISCONNECT	0x16			/* detect usb device plug out */

#define	DEF_USB_PID_IN		0x09

#define WeJOYSTICK_START        1
#define WeJOYSTICK_SELECT       2
#define WeJOYSTICK_MODE         3
#define WeJOYSTICK_BUTTON_L     4
#define WeJOYSTICK_BUTTON_R     5
#define WeJOYSTICK_RIGHT_L      6
#define WeJOYSTICK_LEFT_L       7
#define WeJOYSTICK_UP_L         8
#define WeJOYSTICK_DOWN_L       9
#define WeJOYSTICK_UP_R         10
#define WeJOYSTICK_RIGHT_R      11
#define WeJOYSTICK_DOWN_R       12
#define WeJOYSTICK_LEFT_R      	13
#define WeJOYSTICK_L1           14
#define WeJOYSTICK_R1           15
#define WeJOYSTICK_L2           16
#define WeJOYSTICK_R2           17


//Define struct
/* ********************************************************************************************************************* */
typedef struct _USB_DEVICE_DEscriptOR {
    uint8_t bLength;
    uint8_t bDescriptorType;
    unsigned short bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    unsigned short idVendor;
    unsigned short idProduct;
    unsigned short bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;

typedef struct _USB_CONFIG_DEscriptOR {
    uint8_t bLength;
    uint8_t bDescriptorType;
    unsigned short wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationvalue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;

typedef struct _USB_INTERF_DEscriptOR {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;

typedef struct _USB_ENDPOINT_DEscriptOR {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    unsigned short wMaxPacketSize;
    uint8_t bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;

typedef struct _USB_CONFIG_DEscriptOR_LONG {
    USB_CFG_DESCR cfg_descr;
    USB_ITF_DESCR itf_descr;
    USB_ENDP_DESCR endp_descr[4];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;

/**
 * Class: WeUSBHost
 * \par Description
 * Declaration of Class WeUSBHost.
 */
class WeUSBHost
{
public:
  bool ch375_online;
  bool device_online;
  bool device_ready;
  uint8_t RECV_BUFFER[ CH375_MAX_DATA_LEN ];

  WeUSBHost(uint8_t receivePin, uint8_t transmitPin);
  void init(int8_t type);
  int16_t initHIDDevice();
  int16_t probeDevice();
  void resetBus();
  uint8_t host_recv();
  int16_t get_version();
  void loop();
  bool ButtonPressed(uint8_t button);
  uint8_t readAnalog(uint8_t button);
  void printValue(void);
  uint8_t joystickRx(void);
  uint8_t joystickRy(void);
  uint8_t joystickLx(void);
  uint8_t joystickLy(void);
  uint8_t joystick(uint8_t, uint8_t);
private:
  WeSerial *HSerial;
  int16_t stallCount;
  int8_t usbtype;
  uint8_t data_len;
  uint8_t js_buf[19];
  uint8_t ps2_data_list[26];
  uint8_t ps2_data_list_bak[26];
  bool _JSisReady;
  uint8_t CH375_RD();
  void CH375_WR(uint8_t c);
  int16_t set_usb_mode(int16_t mode);
  uint8_t getIrq();
  void toggle_send();
  void toggle_recv();
  uint8_t issue_token( uint8_t endp_and_pid );
  void wr_usb_data( uint8_t len, uint8_t *buf );
  uint8_t rd_usb_data( uint8_t *buf );
  
  void set_freq(void);
  uint8_t set_addr( uint8_t addr );
  uint8_t set_config(uint8_t cfg);
  uint8_t clr_stall6(void);
  uint8_t get_desr(uint8_t type);
  void parseJoystick(uint8_t *buf);
};
#endif

