// Reverse engineering courtesty of c1de0x, et al. of the iPhone Dev Team

/*
Revisions:
	v0.0 - Original - loadibec.c of planetbeings iphonelinux repository
	v0.1 - C++ Port By Anon0 - 9/10/2010
*/

#include <cmn.h>
#include <UsbInterface.h>

static USHORT MAJ_VER = 0;
static USHORT MIN_VER = 1;

int main(int argc, char* argv[]) {

	PrintHeader( MAJ_VER, MIN_VER );
	cUsbInterface iPhoneDevice( USB_RECOVERY );

	// http://www.cplusplus.com/forum/unices/22584/
	if (getuid()) {
		cerr << "You must run this program as root." << endl;
		return -1;
	}

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <img3>" << endl;
		return -1;
	}
	
	
	if ( iPhoneDevice.Open() == -1 ) {
		cerr << "Your device must be in recovery mode." << endl;
		return -1;
	}
	
	// TODO: add interactive mode
	if(iPhoneDevice.SendFile( argv[1]) >= 0) {
	    iPhoneDevice.SendRawCommand( "go" );
	}

	iPhoneDevice.Close();

	return 0;
}

void PrintHeader( USHORT maj, USHORT min ){

	stringstream version;
	int verLen = 0;

	version << " Open iBoot Loader v" << MAJ_VER << "." << MIN_VER << " ";
	verLen = version.str().length()+2;

	for( int i = 0; i < verLen; i++ ) cout << "-";
	cout << endl << "-" << version.str().c_str() << "-" << endl;
	for( int i = 0; i < verLen; i++ ) cout << "-";
	cout << endl << endl;

}
