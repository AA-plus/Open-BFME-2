// ??0MainMenuMediumScaleUpTransition@@QAE@XZ
// cl: /MD
//
// ??0MainMenuMediumScaleUpTransition@@QAE@XZ @0x0035DE55 80B: derived ctor calling base
// ??0Rva001DBAA4 at 0x001DBAA4, the shorter sibling of the rowed
// Rva0035E00F ctor 0x0035E206 (Rva0035E00FFinish.cpp, same three levers):
// window +0x10..+0x44 with +0x14 = 3 and +0x28 = -1, vtable 0x00C16574
// (the rowed destructor 0x0035DCF9 and vslots 0x0035DD08/0x0035DD9C share
// it), then the base +4 takes +0x14, +0xC clears and +9 is set.
extern "C" const void *const vtbl_00C16574[];  // ??_7MainMenuMediumScaleUpTransition@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C16574=??_7MainMenuMediumScaleUpTransition@@6B@")

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};
class __declspec(novtable) MainMenuMediumScaleUpTransition : public Rva001DBAA4
{
public:
	virtual ~MainMenuMediumScaleUpTransition();
	MainMenuMediumScaleUpTransition();
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
};
MainMenuMediumScaleUpTransition::MainMenuMediumScaleUpTransition()
{
	int *p28 = &m_28;
	int *p14 = &m_14;
	m_10 = 0;
	m_14 = 3;
	*(unsigned int *)this = ((unsigned int)vtbl_00C16574);
	int *p18 = &m_18;
	*p18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	*p28 = -1;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_4 = *p14;
	m_44 = 0;
	m_C = 0;
	m_9 = true;
}
