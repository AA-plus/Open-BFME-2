// Ported from BFME1; retain only after independent BFME2 placement.
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:?getCenterPosition@GeometryInfo@@QBEXABUCoord3D@@AAU2@@Z=?getCenterPosition@GeometryInfo@@ABEXABUCoord3D@@AAU2@@Z")

// Keep the MSVC float overloads local; their inlined operations stay retail-exact.
#define inline static inline
#include <math.h>
#undef inline

typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"

inline Real bfmeSqr(Real value)
{
	return value * value;
}

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition(void) const;
	Real getMaxHeightBelowPosition(void) const;
	void calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
		const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const;

private:
	void getCenterPosition(const Coord3D &position, Coord3D &center) const
	{
		center = m_centerOffset;
		center.x += position.x;
		center.y += position.y;
		center.z += position.z;
	}

	unsigned char m_unmodelled000[0x18];
	Coord3D m_centerOffset;
};

void GeometryInfo::calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
	const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const
{
	Coord3D thisCenter;
	getCenterPosition(thisPos, thisCenter);

	Real dxy = sqrt(bfmeSqr(thatPos.x - thisCenter.x) +
		bfmeSqr(thatPos.y - thisCenter.y));

	Real dz = (thatPos.z + that.getMaxHeightAbovePosition()) - thisCenter.z;
	maxPitch = atan2(dz, dxy);

	Real below = that.getMaxHeightBelowPosition();
	dz = (thatPos.z - below) - thisCenter.z;
	minPitch = atan2(dz, dxy);
}
