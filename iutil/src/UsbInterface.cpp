// Basic USB Interface - Original File -> loadibec.c
// Help from: http://www.cplusplus.com/reference/iostream/istream/read/

#include <UsbInterface.h>

volatile size_t readIntoOutput = 0;
volatile int InterestWrite = 0;

cUsbInterface::cUsbInterface( USHORT devid ){
	this->handle = NULL;
	this->devid = devid;
}

cUsbInterface::~cUsbInterface(){
	if (this->handle != NULL) {
		this->Close();
	}
}

int cUsbInterface::Open(){

	int configuration = 0;
	if (this->handle != NULL) {
		if( this->Close() == -1 ) return -1;
	}

	libusb_init(NULL);
	handle = libusb_open_device_with_vid_pid(NULL, USB_APPLE_ID, devid);
	if (this->handle == NULL) {
		cerr << "Open Interface: Usb Unable to connect to device." << endl;
		return -1;
	}

	libusb_get_configuration(this->handle, &configuration);
	if(configuration != 1) {
		if (libusb_set_configuration(this->handle, 1) < 0) {
			cerr << "Open Usb Interface: Error setting configuration." << endl;
			return -1;
		}
	}
	if (libusb_claim_interface(this->handle, 0) < 0) {
		cerr << "Open Usb Interface: Error claiming interface." << endl;
		return -1;
	}

	return 0;
}

int cUsbInterface::Close(){

	if (this->handle == NULL) {
		cerr << "Close Usb Interface: That device handle has not been initialized yet." << endl;
		return -1;
	}

	libusb_release_interface(this->handle, 0);
	libusb_release_interface(this->handle, 1);
	libusb_close(this->handle);
	libusb_exit(NULL);
	this->handle = NULL;

	return 0;

}

int cUsbInterface::SendFile( string fname ){

	ifstream data;
	int length = 0;
	char * buffer;

	if(this->handle == NULL) {
		cerr << "Send File: Device has not been initialized yet." << endl;
		return -1;
	}

	data.open( fname.c_str(), ifstream::binary );

	if( !data.is_open() ) {
		cerr << "Send File: unable to find file." << endl;
		return -1;
	}

	data.seekg (0, ios::end);
  	length = data.tellg();
  	data.seekg (0, ios::beg);

	// allocate memory:
  	buffer = new char [length];

	if (buffer == NULL) {
		cerr << "Send File: error allocating memory.\n" << endl;
		data.close();
		return -1;
	}

	// read data as a block:
  	data.read(buffer,length);
  	data.close();

	int packets = length / 0x800;
	if(length % 0x800) {
		packets++;
	}

	int last = length % 0x800;
	if(!last) {
		last = 0x800;
	}

	int i = 0;
	char response[6];
	for(i = 0; i < packets; i++) {
		int size = i + 1 < packets ? 0x800 : last;

		// Needed a typecast
		if(!libusb_control_transfer(handle, 0x21, 1, i, 0, (unsigned char*)&buffer[i * 0x800], size, 1000)) {
			printf("send_file: error sending packet.\n");
			return -1;
		}

		// Needed a typecast
		if(libusb_control_transfer(handle, 0xA1, 3, 0, 0, (unsigned char*)response, 6, 1000) != 6) {
			printf("send_file: error receiving status.\n");
			return -1;

		} else {
			if(response[4] != 5) {
				printf("send_file: invalid status.\n");
				return -1;
			}
		}

	}

	// Needed a typecast
	libusb_control_transfer(handle, 0x21, 1, i, 0, (unsigned char*)buffer, 0, 1000);
	for(i = 6; i <= 8; i++) {
		// Needed a typecast
		if(libusb_control_transfer(handle, 0xA1, 3, 0, 0, (unsigned char*)response, 6, 1000) != 6) {
			printf("send_file: error receiving status.\n");
			return -1;

		} else {
			if(response[4] != i) {
				printf("send_file: invalid status.\n");
				return -1;
			}
		}
	}

	delete[] buffer;
	return 0;
}

int cUsbInterface::SendRawCommand( string cmd ){
	size_t length = cmd.length();
	if (length >= 0x200) {
		cerr << "Send Command: Command is too long." << endl;
		return -1;
	}

	// Needed a typecast
	if (!libusb_control_transfer(handle, 0x40, 0, 0, 0, (unsigned char*)cmd.c_str(), length + 1, 1000)) {
		cerr << "Send Command: Unable to send command." << endl;
		return -1;
	}
 
	return 0;
}

void cUsbInterface::DetectAppleDevices(){
/*
	usb_init();
	usb_find_busses();
	usb_find_devices();

	struct usb_bus *busses;
	struct usb_bus *bus;
	struct usb_device *dev;

	busses = usb_get_busses();

	int found = 0;
	int c, i, a;
	for(bus = busses; bus; bus = bus->next) {
    		for (dev = bus->devices; dev; dev = dev->next) {
    			if (dev->descriptor.idVendor != 0x0525 || dev->descriptor.idProduct != 0x1280) {
    				continue;
    			}
    
			// Loop through all of the interfaces
			for (i = 0; i < dev->config[0].bNumInterfaces; i++) {
				for (a = 0; a < dev->config[0].interface[i].num_altsetting; a++) {
					// Check For Apple Device Device Code
    				}
    			}
    		}
	}
*/
}
