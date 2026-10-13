// cl: /MD
// ?rva0057A382@Rva0057A382@@QAEXXZ @0x0057A382 39B
// Evidence: caller 0x0057A748 sets +0x58=0 +0x5C=1; callee row ?rva005D3F6D@Rva005D3F6D@@QAEXH@Z; neighbours share /O1 /MD
int g_00E06374;	// retail RVA 0x00A06374 (.data, 4 bytes), defined here: nothing else owns it
int g_00E06378;	// retail RVA 0x00A06378 (.data, 4 bytes), defined here: nothing else owns it
int g_00E0637C;	// retail RVA 0x00A0637C (.data, 8 bytes), defined here: nothing else owns it

class Rva005D3F6DInner;
class Rva005D3F6D
{
public:
	void rva005D3F6D(int v);
private:
	char m_pad[0x24];
	Rva005D3F6DInner *m_ptr24;
	int m_pad28;
	int m_cached2C;
};

class Rva005D3FBD
{
public:
	void rva005D3FBD(bool v);
};

class Rva0057A4A3Target
{
public:
	char m_pad00[0x38];
	bool m_38;
};

class Rva0057A382
{
public:
	__declspec(noinline) void rva0057A382();
	void rva0057A471(int val);
	void rva0057A4A3();
private:
	char m_pad00[8];
	Rva005D3F6D m_08;
	char m_pad38[0x10];
	Rva0057A4A3Target *m_48;
	char m_pad4C[0xC];
	int m_58;
	bool m_5C;
};

void Rva0057A382::rva0057A382()
{
	int v = g_00E06374;
	if (m_58 == 1)
		v = g_00E06378;
	else if (m_5C != 0)
		v = g_00E0637C;
	m_08.rva005D3F6D(v);
}

// ?rva0057A471@Rva0057A382@@QAEXH@Z @0x0057A471 (50B)
void Rva0057A382::rva0057A471(int val)
{
	if (val != m_58) {
		((Rva005D3FBD *)&m_08)->rva005D3FBD(val == 1);
		Rva0057A4A3Target *target = m_48;
		m_58 = val;
		target->m_38 = true;
		rva0057A382();
	}
}

// ?rva0057A4A3@Rva0057A382@@QAEXXZ
void Rva0057A382::rva0057A4A3()
{
	if (m_5C) {
		m_5C = false;
		m_48->m_38 = true;
		rva0057A382();
	}
}
