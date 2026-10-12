// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva0025DA8D@BfmeStrVM0@@UAE_NVAsciiString@@H@Z, retail 0x0025DA8D (160 bytes, EH, RET 8),
// display vtable slot 72 (W3DDisplay table 0x007C3C80). Refuses on Windows 9x
// (GetVersionExA platform 1); otherwise hands a copy of the movie name, the flags without
// bit 3 and two -1 limits to slot 66 (+0x108) and, when that starts, runs the rowed
// bfmeTickVM0 step and reports success. BfmeStrVM0 is this tree's address name for Display;
// the slot's own name is not recovered.
#include <windows.h>
#include <string.h>

#include "ascii_string.h"

class BfmeStrVM0
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043();
	virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051();
	virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055();
	virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063();
	virtual void s064(); virtual void s065();
	virtual bool playMovieFlags(AsciiString movieName, int flags, int first, int second);	// +0x108
	virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070();
	virtual void s071();
	virtual bool rva0025DA8D(AsciiString movieName, int flags);			// +0x120
	void bfmeTickVM0();
};

bool BfmeStrVM0::rva0025DA8D(AsciiString movieName, int flags)
{
	OSVERSIONINFOA info;
	memset(&info, 0, sizeof(info));
	info.dwOSVersionInfoSize = sizeof(info);
	GetVersionExA(&info);
	if (info.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS && playMovieFlags(movieName, flags & ~8, -1, -1)) {
		bfmeTickVM0();
		return true;
	}
	return false;
}
