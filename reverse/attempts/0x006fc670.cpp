// _BfmeAux006FC670
// partial score=0.91 date=2026-10-13
// cl: /O2 /G6 /arch:SSE /DNDEBUG /MD /EHs
// Target evidence: the 762-byte Ghidra body calls the matched AptValue
// predicates at 0x006DC170, 0x006DC210, 0x006DC0D0, 0x006DC010 and 0x006DBFA0;
// its string path constructs an EAStringC, calls the matched toString body at
// 0x006DD6C0, then uses the matched EAStringC accessors and the target imports
// strtol (0x00629ABA) and isdigit (0x00629982). Its caller at 0x006FF5D0 passes
// the top Apt stack value. The address-derived pin records that call path.
// Structural inference: the body is a numeric-string predicate; no named
// source identity is claimed. The grammar and exceptional type path below
// follow the retail branch structure, including its edge cases.

class EAStringC
{
    unsigned int m_data;

public:
    EAStringC();
    ~EAStringC();
    unsigned int rva006D3750() const;
    int GetAt(int index) const;
    const char *rva00620090() const;
};

class AptString;
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
    AptString *c_string() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isString() const;
    bool isUndefined() const;
    bool isNone() const;
    void toString(EAStringC &out) const;
protected:
    unsigned int m_valueFlags;
};

int Rva006CD220Get();
extern "C" long __cdecl strtol(const char *, char **, int);

// Retail calls the six-byte target import thunk at 0x00629982. Its existing
// ledger pin uses the generated no-argument wrapper name, so call that pinned
// symbol through the typed ABI the target call site establishes.
void ji_00629982();
typedef int (__cdecl *Rva00629982Digit)(int);
#define digitAt00629982(value) \
    (reinterpret_cast<Rva00629982Digit>(&ji_00629982)(value))

bool rva006fc370(AptValue *value)
{
    if (value->isInteger())
        return false;
    if (value->isFloat())
        return false;

    if (value->isString()) {
        EAStringC string;
        value->toString(string);

        if (string.rva006D3750() == 0)
            return true;

        if (string.GetAt(0) == '0' &&
            static_cast<int>(string.rva006D3750()) > 2 &&
            string.GetAt(1) == 'x') {
            char *end;
            strtol(string.rva00620090(), &end, 16);
            if (*end == '\0')
                return false;
        }

        bool decimalPointSeen = false;
        char last = static_cast<char>(
            string.GetAt(static_cast<int>(string.rva006D3750()) - 1));
        if (last != '-' && last != '+' && last != 'e' && last != '.' &&
            !digitAt00629982(last))
            return true;

        if (string.GetAt(0) != '.' && string.GetAt(0) != '-' &&
            string.GetAt(0) != '+' &&
            !digitAt00629982(string.GetAt(0)))
            return true;

        for (int index = 1;
             index < static_cast<int>(string.rva006D3750()); ++index) {
            if (string.GetAt(index) == '.') {
                if (!decimalPointSeen) {
                    decimalPointSeen = true;
                    continue;
                }
            }

            if (string.GetAt(index) == 'e' && index != 1) {
                if (index == 2) {
                    if (string.GetAt(0) == '+')
                        goto invalid_string;
                    if (string.GetAt(0) == '-')
                        goto invalid_string;
                }

                int next = index + 1;
                if (next < static_cast<int>(string.rva006D3750())) {
                    char exponent = static_cast<char>(string.GetAt(next));
                    if (exponent == '-' || exponent == '+') {
                        index = next;
                    } else {
                        if (!digitAt00629982(exponent))
                            goto invalid_string;
                        index = next;
                    }
                }
                continue;
            }

            if (!digitAt00629982(string.GetAt(index))) {
                goto invalid_string;
            }
        }

        return false;

    invalid_string:
        return true;
    } else if (value->isUndefined() || value->isNone()) {
        int version = Rva006CD220Get();
        if (version == 7)
            return true;
        return false;
    }

    return true;
}

// Native parser extent includes its jump table and byte-index table (2512B).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#define RUNTIME_ASSERT(e, line, text) \
	do { \
		if (!(e)) { \
			g_bfmeAptAssertAtE17734(text, "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", line); \
			if (g_bfmeAptBreakOnAssertAtDDC01C) \
				__debugbreak(); \
		} \
	} while (0)

class AptString;

class AptValueVector
{
public:
	void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;

class AptInteger { public: static AptValue *Create(int value); };
class AptBoolean { public: static AptValue *Create(bool value); };
AptValue *Rva008A4EA0MakeFloat(float value);
extern AptValue *gpUndefinedValue;

struct StringNode0070D9F0;
StringNode0070D9F0 *Rva0070DBB0Intern(const char *string);
void Rva0070DDC0Remove(StringNode0070D9F0 *node);

class Rva006DB160 { public: void *allocBlock(int blockSize); };
extern Rva006DB160 *g_pChainBlockAllocator;
void Rva006D8680Free(void *block, int blockSize);

// The two pooled 12-byte value types built from constant types 8 and 4.
class Rva006FB9C0 : public AptValue
{
public:
	Rva006FB9C0(int value);
	static void *operator new(unsigned int n) { return g_pChainBlockAllocator->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { Rva006D8680Free(p, n); }
private:
	int m_value;
};

class Rva006FB960 : public AptValue
{
public:
	Rva006FB960(int value);
	static void *operator new(unsigned int n) { return g_pChainBlockAllocator->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { Rva006D8680Free(p, n); }
private:
	int m_value;
};

struct AptConstantItem
{
	int type;
	union
	{
		const char *szString;
		int nValue;
		float fValue;
	};
};

struct AptConstantFile
{
	char m_pad00[0x1C];
	AptConstantItem *aConstants;		// +0x1C
};

extern "C" void BfmeAux006FC670(const unsigned char *aActionStream, int pBase, AptConstantFile *aConstantFile, int *pnCurrentConstantIndex);

class AptActionInterpreter
{
	friend void BfmeAux006FC670(const unsigned char *, int, AptConstantFile *, int *);
	struct FunctionTable
	{
		int mCheckAlignment;
		void *mFunctionPointer;
	};
	static FunctionTable sGlobalTable[];
};

struct ActionPushStringData { const char *szStringToBePushed; };
struct ActionItemsData { int nItems; void **apItems; };
struct ActionPushData { ActionItemsData items; };
struct ActionGetURLData { const char *szUrl; const char *szWin; };
struct ActionSetTargetData { const char *szTarget; };
struct ActionGotoLabelData { const char *szLabel; };
struct ActionDefineFunctionData
{
	const char *szName;
	int nParams;
	const char **aszParams;
	int nBodySize;
	int nMarker0;
	int nMarker1;
};
struct ActionParamInfo { int nRegister; const char *szParamName; };
struct ActionDefineFunction2Data
{
	const char *szName;
	int nParams;
	int nFlags;
	ActionParamInfo *aszParams;
	int nBodySize;
	int nMarker0;
	int nMarker1;
};
struct ActionTryData
{
	int nTrySize;
	int nCatchSize;
	int nFinallySize;
	unsigned char flags;
	const char *szCaughtVarName;
};
struct ActionWithData { int nOffset; };

#define ALIGN_STREAM(p) ((const unsigned char *)(((unsigned int)(p) + 3) & ~3))
#define RELOCATE(field) if (field) *(int *)&(field) += pBase
#define UNRELOCATE(field) if (field) *(int *)&(field) -= pBase

extern "C" void BfmeAux006FC670(const unsigned char *incomingActionStream, int pBase, AptConstantFile *aConstantFile, int *pnCurrentConstantIndex)
{
	int bUnrelocate = (aConstantFile == 0);
    const unsigned char *aActionStream=incomingActionStream;
	g_releaseVectorAtE17710->ReleaseValues();
	for (;;)
	{
		int eAction = *aActionStream++;
		RUNTIME_ASSERT(AptActionInterpreter::sGlobalTable[eAction].mCheckAlignment == eAction, 0x13E, "sGlobalTable[eAction].mCheckAlignment == eAction");
		if (eAction == 0)
			return;

		switch (eAction)
		{
		case 0xA2: case 0xAE: case 0xAF: case 0xB0: case 0xB1: case 0xB2: case 0xB3: case 0xB5:
			aActionStream += 1;
			break;

		case 0xA3: case 0xB6:
			aActionStream += 2;
			break;

		case 0xA1: case 0xA4: case 0xA5: case 0xA6: case 0xA7:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionPushStringData *pData = (ActionPushStringData *)aActionStream;
			aActionStream += sizeof(ActionPushStringData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szStringToBePushed);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szStringToBePushed < 0xfffff, 0x1AC, "(unsigned)pData->szStringToBePushed < 0xfffff");
				RELOCATE(pData->szStringToBePushed);
			}
			break;
		}

		case 0x88: case 0x96:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionPushData *pData = (ActionPushData *)aActionStream;
			aActionStream += sizeof(ActionPushData);
			if (!bUnrelocate)
			{
				RUNTIME_ASSERT((unsigned)pData->items.apItems < 0xfffff, 0x1B7, "(unsigned)pData->items.apItems < 0xfffff");
				RELOCATE(pData->items.apItems);
				for (int i = 0; i < pData->items.nItems; i++)
				{
					int nConstTableIndex = (int)pData->items.apItems[i];
					RUNTIME_ASSERT(nConstTableIndex == *pnCurrentConstantIndex, 0x1D7, "nConstTableIndex == *pnCurrentConstantIndex");
					int nextIndex=*pnCurrentConstantIndex+1;
                    *pnCurrentConstantIndex=nextIndex;
                    int constantType=aConstantFile->aConstants[nConstTableIndex].type;
					AptValue *pAtom = 0;
					if (constantType == 1)
					{
                        AptConstantFile *constantBase=aConstantFile;
						RUNTIME_ASSERT((unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff, 0x1E5, "(unsigned)aConstantFile->aConstants[nConstTableIndex].szString < 0xfffff");
						if (aConstantFile->aConstants[nConstTableIndex].szString)
							*(int *)&aConstantFile->aConstants[nConstTableIndex].szString += (int)constantBase;
						pAtom = (AptValue *)Rva0070DBB0Intern(aConstantFile->aConstants[nConstTableIndex].szString);
						if (aConstantFile->aConstants[nConstTableIndex].szString)
							*(int *)&aConstantFile->aConstants[nConstTableIndex].szString -= (int)constantBase;
					}
					else if (constantType == 6)
						pAtom = Rva008A4EA0MakeFloat(aConstantFile->aConstants[nConstTableIndex].fValue);
					else if (constantType == 7)
						pAtom = AptInteger::Create(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 8)
						pAtom = new Rva006FB9C0(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 5)
						pAtom = AptBoolean::Create(aConstantFile->aConstants[nConstTableIndex].nValue != 0);
					else if (constantType == 4)
						pAtom = new Rva006FB960(aConstantFile->aConstants[nConstTableIndex].nValue);
					else if (constantType == 3)
						pAtom = gpUndefinedValue;
					RUNTIME_ASSERT(pAtom, 0x20B, "pAtom");
					pData->items.apItems[i] = pAtom;
					if (!pAtom->isString())
						pAtom->AddRef();
					if ((i % 16) == 0)
						g_releaseVectorAtE17710->ReleaseValues();
				}
			}
			else
			{
				for (int i = 0; i < pData->items.nItems; i++)
				{
					AptValue *pAtom = (AptValue *)pData->items.apItems[i];
					if (pAtom->isString())
						Rva0070DDC0Remove((StringNode0070D9F0 *)pAtom->c_string());
					else
						pAtom->Release();
					pData->items.apItems[i] = (void *)*pnCurrentConstantIndex;
					(*pnCurrentConstantIndex)++;
					if ((i % 16) == 0)
						g_releaseVectorAtE17710->ReleaseValues();
				}
				UNRELOCATE(pData->items.apItems);
			}
			break;
		}

		case 0x83:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionGetURLData *pData = (ActionGetURLData *)aActionStream;
			aActionStream += sizeof(ActionGetURLData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szUrl);
				UNRELOCATE(pData->szWin);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szUrl < 0xfffff, 0x238, "(unsigned)pData->szUrl < 0xfffff");
				RELOCATE(pData->szUrl);
				RUNTIME_ASSERT((unsigned)pData->szWin < 0xfffff, 0x239, "(unsigned)pData->szWin < 0xfffff");
				RELOCATE(pData->szWin);
			}
			break;
		}

		case 0x8B:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionSetTargetData *pData = (ActionSetTargetData *)aActionStream;
			aActionStream += sizeof(ActionSetTargetData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szTarget);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szTarget < 0xfffff, 0x24E, "(unsigned)pData->szTarget < 0xfffff");
				RELOCATE(pData->szTarget);
			}
			break;
		}

		case 0x8C:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionGotoLabelData *pData = (ActionGotoLabelData *)aActionStream;
			aActionStream += sizeof(ActionGotoLabelData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szLabel);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szLabel < 0xfffff, 0x257, "(unsigned)pData->szLabel < 0xfffff");
				RELOCATE(pData->szLabel);
			}
			break;
		}

		case 0x9B:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionDefineFunctionData *pData = (ActionDefineFunctionData *)aActionStream;
			aActionStream += sizeof(ActionDefineFunctionData);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szName < 0xfffff, 0x261, "(unsigned)pData->szName < 0xfffff");
				RELOCATE(pData->szName);
				RUNTIME_ASSERT((unsigned)pData->aszParams < 0xfffff, 0x262, "(unsigned)pData->aszParams < 0xfffff");
				RELOCATE(pData->aszParams);
			}
			for (int i = 0; i < pData->nParams; i++)
			{
				if (bUnrelocate)
				{
					UNRELOCATE(pData->aszParams[i]);
				}
				else
				{
					RUNTIME_ASSERT((unsigned)pData->aszParams[i] < 0xfffff, 0x265, "(unsigned)pData->aszParams[i] < 0xfffff");
					RELOCATE(pData->aszParams[i]);
				}
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->aszParams);
				pData->nMarker0 = 0x98765432;
				pData->nMarker1 = 0x12345678;
			}
			break;
		}

		case 0x81: case 0x87: case 0x99: case 0x9D: case 0x9F: case 0xB8:
			aActionStream = ALIGN_STREAM(aActionStream);
			aActionStream += 4;
			break;

		case 0xB4: case 0xB7:
			aActionStream += 4;
			break;

		case 0x94:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionWithData *pData = (ActionWithData *)aActionStream;
			aActionStream += sizeof(ActionWithData);
			if (bUnrelocate)
				pData->nOffset -= (int)aActionStream;
			else
				pData->nOffset += (int)aActionStream;
			break;
		}

		case 0x8E:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionDefineFunction2Data *pData = (ActionDefineFunction2Data *)aActionStream;
			aActionStream += sizeof(ActionDefineFunction2Data);
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szName < 0xfffff, 0x297, "(unsigned)pData->szName < 0xfffff");
				RELOCATE(pData->szName);
				RUNTIME_ASSERT((unsigned)pData->aszParams < 0xfffff, 0x29A, "(unsigned)pData->aszParams < 0xfffff");
				RELOCATE(pData->aszParams);
			}
			for (int i = 0; i < pData->nParams; i++)
			{
				if (bUnrelocate)
				{
					UNRELOCATE(pData->aszParams[i].szParamName);
				}
				else
				{
					RUNTIME_ASSERT((unsigned)pData->aszParams[i].szParamName < 0xfffff, 0x29E, "(unsigned)pData->aszParams[i].szParamName < 0xfffff");
					RELOCATE(pData->aszParams[i].szParamName);
				}
			}
			if (bUnrelocate)
			{
				UNRELOCATE(pData->aszParams);
				pData->nMarker0 = 0x98765432;
				pData->nMarker1 = 0x12345678;
			}
			break;
		}

		case 0x8F:
		{
			aActionStream = ALIGN_STREAM(aActionStream);
			ActionTryData *pData = (ActionTryData *)aActionStream;
			aActionStream += sizeof(ActionTryData);
			if (pData->flags & 4)
				break;
			if (bUnrelocate)
			{
				UNRELOCATE(pData->szCaughtVarName);
			}
			else
			{
				RUNTIME_ASSERT((unsigned)pData->szCaughtVarName < 0xfffff, 0x2B7, "(unsigned)pData->szCaughtVarName < 0xfffff");
				RELOCATE(pData->szCaughtVarName);
			}
			break;
		}
		}

		g_releaseVectorAtE17710->ReleaseValues();
	}
}
