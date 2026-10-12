// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached forwarders from .text gaps no ledger row covers
// (seat-3 batch D; see GapBodiesS3A.cpp). Each body is reached only through a
// retail table in .rdata; retail bytes establish every shape. The unrowed
// callees are pinned under address-derived names with the argument counts
// their own `ret` immediates prove.

// --- 0x0035A97E (22B): both arguments and the +0x08 word to the +0x04
// object's 0x0035A8D7 (ret 0xC).
class Rva0035A8D7
{
public:
	void rva0035A8D7(void *a, void *b, void *c);			// 0x0035A8D7
};

class Rva0035A97E
{
public:
	virtual void rva0035A97E(void *a, void *b);
private:
	Rva0035A8D7 *m_target;									// +0x04
	void *m_08;												// +0x08
};

void Rva0035A97E::rva0035A97E(void *a, void *b)
{
	m_target->rva0035A8D7(a, b, m_08);
}

// --- 0x004E81DE (33B): when the flag is set, pass the +0x08 word, the first
// argument and the float to the +0x04 object's 0x004E7FCA (ret 0xC).
class Rva004E7FCA
{
public:
	void rva004E7FCA(void *owner, void *a, float value);	// 0x004E7FCA
};

class Rva004E81DE
{
public:
	virtual void rva004E81DE(void *a, float value, bool on);
private:
	Rva004E7FCA *m_target;									// +0x04
	void *m_08;												// +0x08
};

void Rva004E81DE::rva004E81DE(void *a, float value, bool on)
{
	if (on)
		m_target->rva004E7FCA(m_08, a, value);
}

// --- 0x005AF117 (24B): dispatch on the 0x00E046BC mode word: 0 runs the
// rowed AptMessenger 0x005AEBD3, 1 runs 0x005AED3C.
extern int g_Va00E046BC;

class AptMessenger
{
public:
	void rva005AEBD3();										// 0x005AEBD3
	void rva005AED3C();										// 0x005AED3C
	virtual void rva005AF117();
};

void AptMessenger::rva005AF117()
{
	switch (g_Va00E046BC)
	{
	case 0:
		rva005AEBD3();
		break;
	case 1:
		rva005AED3C();
		break;
	}
}
