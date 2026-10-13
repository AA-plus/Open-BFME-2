// cl: /O1 /arch:SSE /G7 /Op /DNDEBUG /MD /ICode/Libraries/Include
// Native 0x0036CBF9, 129 bytes: WB names this AIGroup::rotateOffset (static;
// position, goal position, offset in/out; see reverse/symbols.csv). It is called
// from computeGoal (0x345E53) and the formation code (0x36D744, 0x3716C6,
// 0x3717B0, 0x3718AD). dir = goal - position with z forced to 0 and normalized
// (Coord3D::normalize, 0x35B6); the offset is rotated into that frame:
//   offset.x' = x * dir.x + y * (-dir.y)
//   offset.y' = y * dir.x + x * dir.y
// Codegen finding: retail loads dir.x into one xmm register and reuses it for
// both x*dir.x and dir.x*y. Plain C++ reads dir.x from memory twice (126 bytes,
// different allocation); one volatile read into a local reproduces the single
// load and the exact allocation under /Op.
#include "Lib/Coord2D.h"
#include "Lib/Coord3D.h"

class AIGroup
{
public:
	static void rotateOffset(const Coord3D *position, const Coord3D *goalPosition, Coord2D *offset);
};

void AIGroup::rotateOffset(const Coord3D *position, const Coord3D *goalPosition, Coord2D *offset)
{
	Coord3D dir;
	dir.x = goalPosition->x;
	dir.y = goalPosition->y;
	dir.x -= position->x;
	dir.y -= position->y;
	dir.z = 0.0f;
	dir.normalize();

	Coord2D perp;
	perp.x = -dir.y;
	float y = offset->y;
	float dx = *(volatile float *)&dir.x;
	float x = offset->x;
	float a = x * dx;
	float b = x * dir.y;
	float c = y * perp.x;
	float d = y * dx;
	offset->x = a + c;
	offset->y = d + b;
}
