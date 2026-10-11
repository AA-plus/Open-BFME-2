// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva005A6E7A@NAT@@QAE?AVAsciiString@@H@Z, retail 0x005A6E7A (96 bytes,
// RET 8): the NAT negotiator's connection-state name for log output
// (BFME 2 addition; the strings are retail's): NOSTATE, WAITINGTOBEGIN,
// WAITINGFOR_MY_PORT_OR_TARGET_PORT, WAITINGFOR_TARGET_RECEIVED_MY_PROB,
// DONE and FAILED for states 0..5, "ERROR-unknown state" otherwise. The
// receiver is unused.
#include "ascii_string.h"

class NAT
{
public:
	AsciiString rva005A6E7A(int state);
};

AsciiString NAT::rva005A6E7A(int state)
{
	switch (state)
	{
	case 0:
		return AsciiString("NATCONNECTIONSTATE_NOSTATE");
	case 1:
		return AsciiString("NATCONNECTIONSTATE_WAITINGTOBEGIN");
	case 2:
		return AsciiString("NATCONNECTIONSTATE_WAITINGFOR_MY_PORT_OR_TARGET_PORT");
	case 3:
		return AsciiString("NATCONNECTIONSTATE_WAITINGFOR_TARGET_RECEIVED_MY_PROB");
	case 4:
		return AsciiString("NATCONNECTIONSTATE_DONE");
	case 5:
		return AsciiString("NATCONNECTIONSTATE_FAILED");
	}
	return AsciiString("ERROR-unknown state");
}
