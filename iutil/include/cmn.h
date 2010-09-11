#ifndef  _CMN_H
#define	 _CMN_H

#include <libusb-1.0/libusb.h>
#include <readline/readline.h>
#include <pthread.h>
#include <usb.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

typedef unsigned short USHORT;

#define OPENIBOOTCMD_DUMPBUFFER 0
#define OPENIBOOTCMD_DUMPBUFFER_LEN 1
#define OPENIBOOTCMD_DUMPBUFFER_GOAHEAD 2
#define OPENIBOOTCMD_SENDCOMMAND 3
#define OPENIBOOTCMD_SENDCOMMAND_GOAHEAD 4
#define USB_BYTES_AT_A_TIME 512
#define USB_APPLE_ID		0x05AC
#define USB_RECOVERY		0x1281
#define USB_OLD_RECOVERY_MODE	0x1280
#define USB_DFU_MODE		0x1227

typedef struct OpenIBootCmd {
	uint32_t command;
	uint32_t dataLen;
}  __attribute__ ((__packed__)) OpenIBootCmd;

void PrintHeader( USHORT maj, USHORT min );

#endif
