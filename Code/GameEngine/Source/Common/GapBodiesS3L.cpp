// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// INI field-parse callbacks from .text gaps no ledger row covers (seat-3
// batch L; see GapBodiesS3A.cpp). Retail bytes establish every shape; the
// error text is retail's own literal.
#include "unicode_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);				// 0x0002DF97
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);				// 0x00148E1A
};

extern NameKeyGenerator *TheNameKeyGenerator;

class InGameUI
{
public:
	bool rva0029FCD9(const char *cursorName);				// 0x0029FCD9
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void __cdecl message(UnicodeString format, ...);
};

extern InGameUI *TheInGameUI;

// The release-build crash report stream (debug_purecall.cpp's view).
class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);					// 0x00038790
bool bfmeRva000387C0();										// 0x000387C0

// --- 0x0035AED4 (142B): parse a radius-cursor name into its name key; a name
// InGameUI does not know (rowed-by-pin 0x0029FCD9) raises the crash report
// and leaves the store untouched.
void rva0035AED4(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (TheInGameUI && !TheInGameUI->rva0029FCD9(token))
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Error, radius cursor \"" << token << "\" doesn't seem to exist in InGameUI.ini").CrashDone(2);
		}
		return;
	}
	*(NameKeyType *)store = TheNameKeyGenerator->nameToKey(token);
}

// --- 0x0041516C (55B): when own slot 2 allows it, announce the crowd-response
// reload on TheInGameUI (retail's literal) and latch +0x20; returns the latch.
class Rva0041516C
{
public:
	virtual void s0();
	virtual void s1();
	virtual bool s2();
	virtual bool rva0041516C(int unused);
private:
	char m_pad04[0x20 - 4];
	bool m_reloaded;										// +0x20
};

bool Rva0041516C::rva0041516C(int)
{
	if (s2())
	{
		TheInGameUI->message(UnicodeString((const unsigned short *)L"RIF: CrowdResponses reloaded"));
		m_reloaded = true;
	}
	return m_reloaded;
}

// --- 0x005114C6 (122B, EH): the Apt messenger factory: the online messenger
// (rowed AptMessengerOnline ctor 0x005AEF6B) when GameSpy is up, else the
// LAN messenger (rowed 0x005AE3A6) when TheLAN exists; 0x2A4 bytes each.
class GameSpyInfoInterface;
class LANAPI;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern LANAPI *TheLAN;

class Rva005114C6Messenger
{
public:
	virtual void m0();
};

class AptMessengerOnline : public Rva005114C6Messenger
{
public:
	AptMessengerOnline(void *owner);						// 0x005AEF6B
private:
	char m_pad[0x2A4 - 4];
};

class Rva005AE30A : public Rva005114C6Messenger
{
public:
	Rva005AE30A(void *owner);								// 0x005AE3A6
private:
	char m_pad[0x2A4 - 4];
};

class Rva005114C6
{
public:
	virtual Rva005114C6Messenger *rva005114C6(void *owner);
};

Rva005114C6Messenger *Rva005114C6::rva005114C6(void *owner)
{
	Rva005114C6Messenger *messenger = 0;
	if (TheGameSpyInfo)
		messenger = new AptMessengerOnline(owner);
	else if (TheLAN)
		messenger = new Rva005AE30A(owner);
	if (messenger)
		return messenger;
	return 0;
}
