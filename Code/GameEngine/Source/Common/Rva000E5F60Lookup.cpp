// cl: /MD /EHs /Ireference/shims/bfme2_ascii
//
// ?rva000E5F60@Rva000E5F60@@QAEPAVRva000E5EC1@@HVAsciiString@@@Z
// RVA 0x000E5F60, 86B. List-find by (id, name) over a sentinel-circular list
// at +0x18 (next at +0x00, item at +0x08); the matcher is
// Rva000E5EC1::rva000E5EC1 (id at +0x4C, name at +0x8C via a StringBase
// compare). Returns the item or 0.
//
// ?rva000E5FB6@Rva000E5F60@@QAEPAVRva000E5EC1@@HABVAsciiString@@@Z
// RVA 0x000E5FB6, 79B, RET8. Asks the game client (slot 0x40) for the id;
// when it answers and the name lookup byte +0x20 is set, finds the entry by
// id and name above and sets its byte +0x9D.
//
// The name travels as AsciiString. The caller copies it into the argument
// slot through AsciiString's inline copy constructor, which calls the rowed
// StringBase<char> copy constructor (0x000365F0); that inline step is what
// orders retail's saved-esp store before the ECX setup. The by-value
// parameter is torn down through the inline ~AsciiString (rowed releaseBuffer
// 0x00036410). The matcher keeps its StringBase<char> signature.

#include "ascii_string.h"

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const throw();
};

struct Rva000E5F60Node
{
	Rva000E5F60Node *m_next;
	Rva000E5F60Node *m_prev;
	Rva000E5EC1 *m_item;
};

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual Rva000E5EC1 *slot10(int id);
};

class GameClient;
extern GameClient *TheGameClient;

class Rva000E5F60
{
public:
	Rva000E5EC1 *rva000E5F60(int id, AsciiString name);
	Rva000E5EC1 *rva000E5FB6(int id, const AsciiString &name);

private:
	char m_pad[0x18];
	Rva000E5F60Node *m_head;
	char m_pad1C[4];
	unsigned char m_lookupByName;
};

Rva000E5EC1 *Rva000E5F60::rva000E5F60(int id, AsciiString name)
{
	Rva000E5F60Node *cur = m_head->m_next;
	while (cur != m_head)
	{
		if (cur->m_item->rva000E5EC1(id, *(const StringBase<char> *)&name))
			return cur->m_item;
		cur = cur->m_next;
	}
	return 0;
}

Rva000E5EC1 *Rva000E5F60::rva000E5FB6(int id, const AsciiString &name)
{
	Rva00DFE77CHolder *client = (Rva00DFE77CHolder *)TheGameClient;
	Rva000E5EC1 *result = client ? client->slot10(id) : 0;
	if (result && m_lookupByName)
	{
		result = rva000E5F60(id, name);
		if (result)
			*(reinterpret_cast<unsigned char *>(result) + 0x9D) = 1;
	}
	return result;
}
