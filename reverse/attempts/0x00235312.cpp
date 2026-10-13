// ?rva00235312@GlobalData@@QAE_NW4TimeOfDay@@0M@Z
// partial score=0.8 date=2026-10-13
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// GlobalData::setTimeOfDay, retail 0x002352BC (86 bytes). Zero Hour's
// GlobalData.cpp body: select one of the five lit times of day and copy its
// three terrain lights into the current ambient/diffuse/position arrays.
// The GlobalData layout below carries only the members this body reaches,
// at the offsets the retail body addresses: m_timeOfDay +0x134, the
// [TIME_OF_DAY_COUNT][MAX_GLOBAL_LIGHTS] TerrainLighting table +0x140
// (0x6C per time of day), and the current arrays +0x8D8/+0x8FC/+0x920.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum TimeOfDay
{
	TIME_OF_DAY_INVALID = 0,
	TIME_OF_DAY_FIRST = 1,
	TIME_OF_DAY_INTERPOLATE = 5,
	TIME_OF_DAY_COUNT = 6
};

enum { MAX_GLOBAL_LIGHTS = 3 };

#include "Code/Libraries/Include/Lib/RGBColor.h"

#include "Code/Libraries/Include/Lib/Coord3D.h"

struct TerrainLighting
{
	RGBColor ambient;
	RGBColor diffuse;
	Coord3D lightPos;
};

class GlobalData
{
public:
	Bool setTimeOfDay( TimeOfDay tod );
    Bool rva00235312(TimeOfDay from,TimeOfDay to,Real t);

private:
	unsigned char m_unreconstructed_000[ 0x134 ];
	TimeOfDay m_timeOfDay;
	unsigned char m_unreconstructed_138[ 0x8 ];
	TerrainLighting m_terrainLighting[ TIME_OF_DAY_COUNT ][ MAX_GLOBAL_LIGHTS ];
	TerrainLighting m_lighting3C8[TIME_OF_DAY_COUNT][MAX_GLOBAL_LIGHTS];
    TerrainLighting m_lighting650[TIME_OF_DAY_COUNT][MAX_GLOBAL_LIGHTS];
	RGBColor m_terrainAmbient[ MAX_GLOBAL_LIGHTS ];
	RGBColor m_terrainDiffuse[ MAX_GLOBAL_LIGHTS ];
	Coord3D m_terrainLightPos[ MAX_GLOBAL_LIGHTS ];
};

// ?setTimeOfDay@GlobalData@@QAE_NW4TimeOfDay@@@Z @0x2352BC
Bool GlobalData::setTimeOfDay( TimeOfDay tod )
{
	if( tod >= TIME_OF_DAY_COUNT || tod < TIME_OF_DAY_FIRST )
	{
		return false;
	}

	m_timeOfDay = tod;
	for (Int i=0; i<MAX_GLOBAL_LIGHTS; i++)
	{	m_terrainAmbient[i] = m_terrainLighting[ tod ][i].ambient;
		m_terrainDiffuse[i] = m_terrainLighting[ tod ][i].diffuse;
		m_terrainLightPos[i] = m_terrainLighting[ tod ][i].lightPos;
	}

	return true;
}

// Target1060 blend uses native erroneous red/blue stores; the setTimeOfDay
// donor supplies the table/copy guide only. Original method name is unknown.
Bool GlobalData::rva00235312(TimeOfDay from, TimeOfDay to, Real t)
{
	if (from >= TIME_OF_DAY_COUNT || from < TIME_OF_DAY_FIRST)
		return false;
	if (to >= TIME_OF_DAY_COUNT || to < TIME_OF_DAY_FIRST)
		return false;

	Real inv = 1.0 - t;
	Int i;
	for (i = 0; i < MAX_GLOBAL_LIGHTS; i++)
	{
		TerrainLighting &d = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i];
		const TerrainLighting &a = m_terrainLighting[from][i];
		const TerrainLighting &b = m_terrainLighting[to][i];
		d.ambient.red = a.ambient.red * inv + b.ambient.red * t;
		d.ambient.green = a.ambient.green * inv + b.ambient.green * t;
		d.ambient.red = a.ambient.blue * inv + b.ambient.blue * t;
		d.diffuse.red = a.diffuse.red * inv + b.diffuse.red * t;
		d.diffuse.green = a.diffuse.green * inv + b.diffuse.green * t;
		d.diffuse.red = a.diffuse.blue * inv + b.diffuse.blue * t;
		d.lightPos.x = a.lightPos.x * inv + b.lightPos.x * t;
		d.lightPos.y = a.lightPos.y * inv + b.lightPos.y * t;
		d.lightPos.z = a.lightPos.z * inv + b.lightPos.z * t;

		TerrainLighting &od = m_lighting3C8[TIME_OF_DAY_INTERPOLATE][i];
		const TerrainLighting &oa = m_lighting3C8[from][i];
		const TerrainLighting &ob = m_lighting3C8[to][i];
		od.diffuse.red = inv * oa.diffuse.red + t * ob.diffuse.red;
		od.diffuse.green = inv * oa.diffuse.green + t * ob.diffuse.green;
		od.diffuse.red = inv * oa.diffuse.blue + t * ob.diffuse.blue;
		od.diffuse.red = inv * oa.diffuse.red + t * ob.diffuse.red;
		od.diffuse.green = inv * oa.diffuse.green + t * ob.diffuse.green;
		od.diffuse.red = inv * oa.diffuse.blue + t * ob.diffuse.blue;
		od.lightPos.x = oa.lightPos.x * inv + ob.lightPos.x * t;
		od.lightPos.y = oa.lightPos.y * inv + ob.lightPos.y * t;
		od.lightPos.z = oa.lightPos.z * inv + ob.lightPos.z * t;

		TerrainLighting &ud = m_lighting650[TIME_OF_DAY_INTERPOLATE][i];
		const TerrainLighting &ua = m_lighting650[from][i];
		const TerrainLighting &ub = m_lighting650[to][i];
		ud.ambient.red = ua.ambient.red * inv + ub.ambient.red * t;
		ud.ambient.green = ua.ambient.green * inv + ub.ambient.green * t;
		ud.ambient.red = ua.ambient.blue * inv + ub.ambient.blue * t;
		ud.diffuse.red = ua.diffuse.red * inv + ub.diffuse.red * t;
		ud.diffuse.green = ua.diffuse.green * inv + ub.diffuse.green * t;
		ud.diffuse.red = ua.diffuse.blue * inv + ub.diffuse.blue * t;
		ud.lightPos.x = ua.lightPos.x * inv + ub.lightPos.x * t;
		ud.lightPos.y = ua.lightPos.y * inv + ub.lightPos.y * t;
		ud.lightPos.z = ua.lightPos.z * inv + ub.lightPos.z * t;
	}

	m_timeOfDay = TIME_OF_DAY_INTERPOLATE;
	for (i = 0; i < MAX_GLOBAL_LIGHTS; i++)
	{
		m_terrainAmbient[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].ambient;
		m_terrainDiffuse[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].diffuse;
		m_terrainLightPos[i] = m_terrainLighting[TIME_OF_DAY_INTERPOLATE][i].lightPos;
	}
	return true;
}
