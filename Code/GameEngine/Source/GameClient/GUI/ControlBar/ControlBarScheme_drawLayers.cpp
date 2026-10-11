// cl: /O1 /DNDEBUG /MD /EHsc
// ControlBarSchemeManager::drawForeground @0x0031FA9A (43B) and
// ::drawBackground @0x0031FAC5 (43B): Zero Hour ControlBarScheme.cpp's
// bodies. Each hands the current scheme (+0x00) the manager's multiplier
// (+0x04, by value) and the caller's offset. drawBackground's identity is its
// caller W3DCommandBarBackgroundDraw 0x0009FA82 (ZH: man->drawBackground(
// offset)); drawForeground is its twin one body earlier, calling the twin of
// the scheme draw drawBackground calls. The scheme draws are rowed under
// address names (0x0031F89E and 0x0031F96F); their ZH names are pinned.
//
// class-gate: allow Coord2D retail copies the by-value multiplier into an esp temp and parks its address in the dead offset slot (mov [ebp+0xc],esp under an ebp frame) - the shape of an argument with a user copy ctor and dtor; the canonical plain Coord2D copies with two pushes
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &o) : x(o.x), y(o.y) {}
	~Coord2D() {}
	float x;
	float y;
};

typedef int Int;

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class ControlBarScheme
{
};

// LINK: the scheme draws are rowed as Rva0031F89E::rva0031F89E and Rva0031F96F::rva0031F96F(float, float, int, int) (the multiplier and offset
// are four stack words); the by-value Coord2D/ICoord2D call shape is kept through a member-pointer cast.
class Rva0031F89E
{
public:
	void rva0031F89E(float mx, float my, int ox, int oy);
};
class Rva0031F96F
{
public:
	void rva0031F96F(float mx, float my, int ox, int oy);
};
typedef void (Rva0031F89E::*SchemeForegroundShape)(Coord2D, ICoord2D);
typedef void (Rva0031F96F::*SchemeBackgroundShape)(Coord2D, ICoord2D);

class ControlBarSchemeManager
{
public:
	void drawForeground(ICoord2D offset);
	void drawBackground(ICoord2D offset);

private:
	ControlBarScheme *m_currentScheme;   // +0x00
	Coord2D m_multiplyer;                // +0x04
};

void ControlBarSchemeManager::drawForeground(ICoord2D offset)
{
	if (m_currentScheme)
		(((Rva0031F89E *)m_currentScheme)->*reinterpret_cast<SchemeForegroundShape>(&Rva0031F89E::rva0031F89E))(m_multiplyer, offset);
}

void ControlBarSchemeManager::drawBackground(ICoord2D offset)
{
	if (m_currentScheme)
		(((Rva0031F96F *)m_currentScheme)->*reinterpret_cast<SchemeBackgroundShape>(&Rva0031F96F::rva0031F96F))(m_multiplyer, offset);
}
