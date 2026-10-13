// ?rva001EFD9C@Rva001EFD9C@@QAE_NVUnicodeString@@_NPBUSelPair@@@Z
// partial score=0.204 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG
// stlport
// Banked GameSpyInfo::sendChat reconstruction, retail 0x001EFD9C..0x001EFFC6.
// WB 0x00B01080 (Chat.cpp:166) and retail vtable VA0x00C19500 slot64 name
// the body. BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 donor
// game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoSendChat.cpp was
// compiled with BFME2 tools (zero placements). It supplies the chat flow;
// BFME2 replaces its listbox with begin/end profile-ID pointers.
// Retail and WB prove trim/empty return, request tags3/2, queue slot6,
// GameSpy slots12/22/23/29 and the format/concat loop. Returned player
// pointers are viewed only through their first AsciiString, not a full type.
// PeerRequest's owned constructor/destructor are 0x1EF661/0x1EF723.
// IMPORTANT corrections to the earlier bank: the vector<bool> ends at118;
// the action byte is the FIRST byte of the union there (not eight later).
// Reload message.str() AFTER PeerRequest construction: retail reloads the
// by-value argument and retains its null fallback. The old cached pointer
// incorrectly let the compiler eliminate that reload and fallback.
// Current body:563B vs554, allREL32 calls resolved; fixed-offset byte
// agreement only113/554 (0.204). No claim that the old0.65 score was exact
// byte agreement. Retail promotes the third argument to EDI and reuses its
// stack slot for string temporaries; this still spills it and reserves4
// extra frame bytes. Early-return variant576B, vector variant571B; sibling
// /G7 /arch:SSE flags do not help. Nothing integrated into Code/.
#include <string>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
template<typename T> inline bool StringBase<T>::isEmpty() const throw() { return !m_data || !m_data->length; }

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union
	{
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
		struct { bool action; } msgAction;
	};
};

struct PeerRequestQueue6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void addRequest(PeerRequest *rec);
};

class GameSpyPeerMessageQueueInterface;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
#define TheGameSpyPeerMessageQueue ((PeerRequestQueue6 *)TheGameSpyPeerMessageQueue)



// Begin/end int-pointer pair retail threads through the third slot.
// Strict pointee type unproven; elements are consumed as Int profileIDs.
struct SelPair
{
	int *begin;
	int *end;
};

struct PlayerInfo
{
	AsciiString m_name;
};

class Rva001EFD9C
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual int getCurrentGroupRoom();
	virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
	virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
	virtual void d21();
	virtual PlayerInfo *rva00382CCE(const char *name);
	virtual PlayerInfo *rva00382D0A(int profileID);
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28();
	virtual AsciiString getLocalName();
	bool rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels);
};

extern Rva001EFD9C *TheGameSpyInfo;

bool Rva001EFD9C::rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels)
{
	bool ok;
	getCurrentGroupRoom();
	message.trim();
	const void *bits = *reinterpret_cast<const void * const *>(&message);
	if (bits == 0
		|| *reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(bits) + 4) == 0)
		ok = false;
	else {
		PeerRequest rec;
		rec.unknown_10 = message.str();
		if (sels == 0
			|| (((reinterpret_cast<const char *>(sels->end) - reinterpret_cast<const char *>(sels->begin)) & ~3) == 0))
		{
			rec.msgAction.action = isAction;
			rec.unknown_00 = 3;
			TheGameSpyPeerMessageQueue->addRequest(&rec);
			ok = false;
		}
		else
		{
			AsciiString names;
			PlayerInfo *found = TheGameSpyInfo->rva00382CCE(TheGameSpyInfo->getLocalName().str());
			if (found)
				names.format("%s", found->m_name.str());
			else
				names.format("%s", TheGameSpyInfo->getLocalName().str());
			for (int *p = sels->begin; p != sels->end; ++p)
			{
				PlayerInfo *info = TheGameSpyInfo->rva00382D0A(*p);
				if (info)
				{
					AsciiString tmp;
					tmp.format(",%s", info->m_name.str());
					names.concat(tmp);
				}
			}
			if (!names.isEmpty())
			{
				rec.unknown_04 = names.str();
				rec.msgAction.action = isAction;
				rec.unknown_00 = 2;
			TheGameSpyPeerMessageQueue->addRequest(&rec);
			}
			ok = true;
		}
	}
	return ok;
}
