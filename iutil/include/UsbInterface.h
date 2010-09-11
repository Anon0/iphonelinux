#include <cmn.h>

class cUsbInterface{

public:
	cUsbInterface( USHORT devid );
	cUsbInterface(){ this->handle = NULL; }
	~cUsbInterface();

	int Open(); 			// Open a USB Handle
	int Close();			// Close USB Handle
	inline void SetDeviceID( USHORT devid ){ this->devid = devid; }
	int SendFile( string fname );		// Send a File
	int SendRawCommand( string cmd ); 	// Send A command to device
	void DetectAppleDevices();

private:
	struct libusb_device_handle *handle;
	USHORT devid;
};
