// ?rva003FAC83@Rva003FAC83@@QAEXXZ
// partial score=0.82 date=2026-10-13
// ?rva003FAC83@Rva003FAC83@@QAEXXZ
// partial score=0.82 date=2026-10-12
// cl: /DNDEBUG /MD
// Closest family attempt: xor-al ||/goto skeleton reproduces branches but cl
// folds ((m_state>>N)&1) into test-imm everywhere (83: 40/49, B4: 36/48 with
// bit0/bit2 merged to test al,5, E9: 52/66, 4A: 62/80). E9 retail
// mov-eax/mov-ecx/shr-ecx shift-copy source unknown. Cross-TU jmp tails to
// rowed 3FAB93/3FAC3F and Region2D predicate decl resolve fine in-TU.
#include "../../../Libraries/Include/Lib/Coord2D.h"
struct Region2D
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
	bool isInside(const Coord2D &point) const;
};
class Rva003FAB93
{
public:
	void rva003FAB93();
};
class Rva003FAC3F
{
public:
	void rva003FAC3F();
};
class Rva003FAC83
{
public:
	void rva003FAC83();
	void rva003FACB4();
	void rva003FACE9(void *arg);
	void rva003FAD4A(void *arg);
private:
	char m_pad00[0x18];
	unsigned int m_state;
	Region2D m_region;
	char m_pad2C[4];
	bool m_30;
	bool m_31;
	bool m_32;
};
void Rva003FAC83::rva003FAC83()
{
	if (m_31 == 0 || m_32 == 0)
		goto checkBit5;
	if ((((m_state >> 4) & 1) != 0) && m_30 != 0)
		return;
	((Rva003FAB93 *)this)->rva003FAB93();
	return;
checkBit5:
	if ((((m_state >> 5) & 1) != 0))
		return;
	((Rva003FAC3F *)this)->rva003FAC3F();
}
void Rva003FAC83::rva003FACB4()
{
	m_30 = false;
	if ((m_state & 1) != 0)
		goto clear;
	if (((m_state >> 2) & 1) != 0)
		goto clear;
	m_31 = true;
	goto tail;
clear:
	m_31 = false;
tail:
	m_32 = !((m_state >> 3) & 1);
	rva003FAC83();
}
void Rva003FAC83::rva003FACE9(void *arg)
{
	if ((((m_state >> 1) & 1) != 0))
		m_31 = false;
	else if (((m_state & 1) != 0) || (((m_state >> 2) & 1) != 0))
		m_31 = m_region.isInside(*(const Coord2D *)arg);
	else
		m_31 = true;
	rva003FAC83();
}
void Rva003FAC83::rva003FAD4A(void *arg)
{
	if ((((m_state >> 1) & 1) != 0))
		m_31 = false;
	else if (((m_state & 1) != 0) || (((m_state >> 2) & 1) != 0)) {
		m_31 = m_region.isInside(*(const Coord2D *)arg);
		if (m_31 && ((((m_state >> 2) & 1) != 0)))
			return;
	} else
		m_31 = true;
	rva003FAC83();
}
