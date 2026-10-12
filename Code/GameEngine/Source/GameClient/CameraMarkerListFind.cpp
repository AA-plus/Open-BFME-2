// cl: /O1 /DNDEBUG /DWIN32 /MD
//
// BFME's ScriptActions::doMoveCameraTo calls this lookup when resolving its
// named camera marker.  The one caller supplies an AsciiString and the body
// walks the marker list at +0x80, comparing each node's name case-sensitively.
//
// CameraMarkerList and CameraMarker are descriptive, not recovered EA names --
// what is proven is the role.  The matched caller is
// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z at 0x002F24F0, and
// this is not the waypoint lookup it uses upstream: BFME still has
// ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z, matched at
// 0x001AA900, so the camera resolves its target through a second, separate
// named list that lives on the client side.

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

bool operator==(const AsciiString &left, const AsciiString &right);

struct CameraMarker
{
	~CameraMarker();
	CameraMarker &operator=(const CameraMarker &src);

	CameraMarker *m_next;
	AsciiString m_name;
};

// ??4CameraMarker@@QAEAAV0@ABV0@@Z, retail 0x0028876F, 29 bytes.
// CameraMarker copy assignment: copies the next link, then the name through
// the rowed AsciiString assignment at 0x366F0. Called pairwise by the
// CameraMarker range-copy loop at 0x48C897 and directly by the indexed
// copy-out at 0xB82EB. Layout is the donor struct above (8 bytes); the
// rowed 0x29D7C2 destructor plus the _Destroy stride prove the element.
CameraMarker &CameraMarker::operator=(const CameraMarker &src)
{
	m_next = src.m_next;
	m_name = src.m_name;
	return *this;
}

// ??1CameraMarker@@QAE@XZ, retail 0x0029D7C2; clear() is its only caller.
// Removing the definition also changes clear()'s inlining.
inline CameraMarker::~CameraMarker()
{
}

class CameraMarkerList
{
public:
	void clear();
	CameraMarker *find(const AsciiString &name) const;
	void remove(CameraMarker *marker);

private:
	char m_unknown[0x80];
	CameraMarker *m_markers;
};

void CameraMarkerList::clear()
{
	while (m_markers)
	{
		CameraMarker *marker = m_markers;
		m_markers = marker->m_next;
		delete marker;
	}
}

CameraMarker *CameraMarkerList::find(
	const AsciiString &name) const
{
	CameraMarker *marker = m_markers;
	while (marker)
	{
		if (marker->m_name.compare(name) == 0)
			return marker;
		marker = marker->m_next;
	}
	return 0;
}

// ?remove@CameraMarkerList@@QAEXPAUCameraMarker@@@Z present-unmatched
void CameraMarkerList::remove(CameraMarker *marker)
{
	CameraMarker **link = &m_markers;
	while (*link)
	{
		if ((*link)->m_name == marker->m_name)
		{
			CameraMarker *removed = *link;
			*link = removed->m_next;
			delete removed;
			return;
		}
		link = &(*link)->m_next;
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCameraMarkerInlineAnchor@@YAXPAVCameraMarker@@@Z absent-from-retail
void _bfmeCameraMarkerInlineAnchor(CameraMarker *p)
{
    p->CameraMarker::~CameraMarker();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva002DFC30@@QAE@XZ=??1CameraMarker@@QAE@XZ")
