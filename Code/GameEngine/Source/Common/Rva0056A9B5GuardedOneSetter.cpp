// cl: /MD
// RVA 0x0056A9B5 sets byte at +0x1E to 1 when bytes at +0x1C and +0x1D are both nonzero.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva0056A9A3LogicView
{
	char m_pad[0x100];
	unsigned int m_100;
};

class Rva0056A9B5
{
public:
	int rva0056A9A3();
	__declspec(noinline) void rva0056A9B5();
	void rva0056A9C6();
	char m_lead[0x14];
	unsigned int m_14;
	int m_18;
	unsigned char m_a;
	unsigned char m_b;
	unsigned char m_c;
};

// ?rva0056A9A3@Rva0056A9B5@@QAEHXZ @0x0056A9A3 (18B)
int Rva0056A9B5::rva0056A9A3()
{
	return ((Rva0056A9A3LogicView *)TheLivingWorldLogic)->m_100 >= m_14;
}

void Rva0056A9B5::rva0056A9B5()
{
	if (m_a == 0)
		return;
	if (m_b == 0)
		return;
	m_c = 1;
}

// RVA 0x0056A9C6 (9 bytes), right after it and reached only as slot 3 of
// 0x0086D2E8 (??_7Rva0056B0BF@@6BRva0056AC26@@@): set the +0x1C byte, then
// the same guarded set (a tail jump into the body above).
void Rva0056A9B5::rva0056A9C6()
{
	m_a = 1;
	rva0056A9B5();
}

class Rva0056A9DE
{
public:
	void rva0056A9DE(int unused);
private:
	char m_pad[9];
	unsigned char m_09;
};

// ?rva0056A9DE@Rva0056A9DE@@QAEXH@Z @0x0056A9DE (15B)
void Rva0056A9DE::rva0056A9DE(int)
{
	m_09 = 1;
	((Rva0056A9B5 *)((char *)this - 0x14))->rva0056A9B5();
}
