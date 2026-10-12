// cl: /MD
//
// ?rva00362499@Rva00362499@@QAEEXZ retail 0x00362499 15 bytes. Dual null check
// returning 1 only if both +4 and +8 are non-zero. Evidence: two callers
// 0x003624C4 and 0x003627B8, no callees, 15B xor-first compare shape.

class Rva00362499
{
public:
	unsigned char __declspec(noinline) rva00362499();
    unsigned int rva003624A8();
    void rva003624FE();
private:
	char m_00[4];
	void *m_04;
	void *m_08;
	unsigned int m_0C;
	unsigned int m_10;
};

unsigned char Rva00362499::rva00362499()
{
	return m_08 != 0 && m_04 != 0;
}

// Clean BF1 f98983a7 Common/Rva00409570StateCheck.cpp under O2/SSE2/G6
// supplies the read-and-return control flow. Its state/owner names and
// volatile qualifier are not asserted here. Native3624A8..3624B4 is a
// complete twelve-byte leaf after the matched362499 RET and before the
// next argument setter. It reads receiver+4, then that child's DWORD+40,
// compares the value with1 and jumps to the immediately following RET.
// Both arms return the one loaded word. This existing receiver prefix is
// reused only for its proven +4 access; original concrete owners, full
// bounds, field purpose and original return type remain unknown.
struct Rva003624A8StatePrefix
{
    char unknown00[0x40];
    unsigned int word40;
};

unsigned int Rva00362499::rva003624A8()
{
    unsigned int value = static_cast<Rva003624A8StatePrefix *>(m_04)->word40;
    if (value == 1)
        return value;
    return value;
}

// ?rva003624FE@Rva00362499@@QAEXXZ @0x003624FE (26B)
void Rva00362499::rva003624FE()
{
    if (rva00362499())
    {
        Rva003624A8StatePrefix *s = static_cast<Rva003624A8StatePrefix *>(m_04);
        if (s)
        {
            unsigned int v = m_10;
            s->word40 = v;
            m_10 = v;
        }
    }
}
