// ?rva006D9780@BfmeAptValue006DCD20@@QAE_NPAV1@PAVEAStringC@@0@Z
// cl: /O2 /MD
// Apt array set-by-key at 0x006D9780 (145B). The two-test condition
// (atoi(text) != 0 || *text == '0') had to be hoisted into a `bool ok` local:
// writing it directly in the `if` makes VC7.1 /O2 sink the `return false` block
// inline, while the local reproduces retail's body-fallthrough / fail-at-end
// layout byte-for-byte. isArray assert, both atoi calls, the double data() eval,
// value selection and checked store then follow exactly.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" int __cdecl atoi(const char *);

class EAStringC
{
public:
	const char *rva00620090() const;
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void slot1();

	int isArray() const;
	BfmeAptValue006DCD20 *rva006DCFA0();
	void rva006D9500(int nCapacity);
	void rva006D8AD0(int nIndex, BfmeAptValue006DCD20 *pNewValue);
	void rva006D95E0(int nIndex, BfmeAptValue006DCD20 *pValue);
	bool rva006D9780(BfmeAptValue006DCD20 *pContext, EAStringC *pKey, BfmeAptValue006DCD20 *pValue);

	unsigned int m_flags;
	char m_pad[0x18];
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};

class AptValue; extern AptValue *gpUndefinedValue;

bool BfmeAptValue006DCD20::rva006D9780(BfmeAptValue006DCD20 *pContext, EAStringC *pKey, BfmeAptValue006DCD20 *pValue)
{
	if (!static_cast<unsigned char>(pContext->isArray()))
	{
		g_bfmeAptAssertAtE17734("pContext->isArray()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x217);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	const char *text = pKey->rva00620090();
	bool ok = atoi(text) != 0 || *text == '0';
	if (ok)
	{
		int index = atoi(pKey->rva00620090());
		pContext->rva006DCFA0()->rva006D95E0(index, pValue ? pValue : (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue));
		return true;
	}
	return false;
}
