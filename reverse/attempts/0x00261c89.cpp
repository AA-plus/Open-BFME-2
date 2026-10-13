// ?rva00261C89@Rva00261C89@@QAEHXZ
// partial score=0.99 date=2026-10-13
// cl: /O1 /G7 /MD
// One-time init two global 7-word flags then KindOf gate: B8 set but not 9C set.
// Evidence: chain from 0x002618A2/0x002618FA landing; caller 0x003E603E this-plus-4 no pushes; rowed BitFlags test 0x002615C0; neighbours 0x002619A0/0x00262002.
template <int N>
class BitFlags
{
public:
	bool test(const void *other) const;
private:
	unsigned m_words[7];
};
class Rva002618A2
{
public:
	Rva002618A2 *rva002618A2(int unused, int b1, int b2, int b3);
	Rva002618A2 *rva002618FA(int unused, int b1, int b2, int b3, int b4, int b5);
private:
	unsigned m_words[7];
};
#define InitFlagsB (*(unsigned char *)0x00DFEAD4)
#define InitFlagsD (*(unsigned int *)0x00DFEAD4)
#define GlobalB8Init ((Rva002618A2 *)0x00DFEAB8)
#define Global9CInit ((Rva002618A2 *)0x00DFEA9C)
#define GlobalB8Test ((BitFlags<69> *)0x00DFEAB8)
#define Global9CTest ((BitFlags<69> *)0x00DFEA9C)
class Rva00261C89
{
public:
	int rva00261C89();
private:
	char m_pad[0x108];
	unsigned m_kind[7];
};
int Rva00261C89::rva00261C89()
{
	if ((InitFlagsB & 1) == 0) {
		InitFlagsD |= 1;
		GlobalB8Init->rva002618FA(0, 8, 9, 10, 11, 12);
	}
	if ((InitFlagsB & 2) == 0) {
		InitFlagsD |= 2;
		Global9CInit->rva002618A2(0, 0x6d, 7, 0x59);
	}
	void *kind = m_kind;
	if (GlobalB8Test->test(kind)) {
		if (!Global9CTest->test(kind))
			return 1;
	}
	return 0;
}

// Codegen: the result is an int (retail returns 1/0 with `xor eax,eax; inc eax` / `xor eax,eax`; a bool
// return gives inc al / xor al,al); the callers test AL only, as for any 0/1 result.
