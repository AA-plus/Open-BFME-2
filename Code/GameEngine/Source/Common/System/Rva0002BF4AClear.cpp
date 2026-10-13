// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?unPrepFile@INI@@IAEXXZ @0x0002BF4A 66B: thiscall clear with None plus empty.
// Evidence: ret no args; lea ecx [esi+0x838] to Rva00601BBCHelper::rva00601A8D pin; AsciiString+0x4 set None row; BfmeINICurrentFilename set TheEmptyString row; ints +0x8 +0xc +0x10 zeroed; byte +0x430 false; g_00DDF57C zeroed; callers are Catch funclets.
// Identity: the INI load variants 0x0002DA4B/0x0002DC75/0x0002DD38 call it on
// their normal and catch(...) exits after prepFile 0x0002D2C1, where BFME 1's
// ini.cpp calls unPrepFile; its stores (line list clear, filename "None",
// zeroed counters and end-of-file flag, null file-level global) follow that
// donor body. The member names stay offset-derived.
#include "ascii_string.h"
class Rva00601BBCHelper
{
public:
	void rva00601A8D();
};
extern AsciiString BfmeINICurrentFilename;
extern void *g_00DDF57C;
class INI
{
protected:
	void unPrepFile();
private:
	char m_pad00[4];
	AsciiString m_04;
	int m_08;
	int m_0c;
	int m_10;
	char m_pad14[0x430 - 0x14];
	bool m_430;
	char m_pad431[0x838 - 0x431];
	Rva00601BBCHelper m_838;
};

void INI::unPrepFile()
{
	m_838.rva00601A8D();
	((StringBase<char> *)&m_04)->set("None");
	((StringBase<char> *)&BfmeINICurrentFilename)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_430 = false;
	g_00DDF57C = 0;
}
