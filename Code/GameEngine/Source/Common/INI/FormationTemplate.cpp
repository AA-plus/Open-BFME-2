// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Formation template object built by the "FormationTemplate" INI block parser
// (retail 0x00425842, banked in reverse/attempts/0x00425842.cpp). Original
// class and member names are unknown: LightPoint/LightSubPoint/CameraMarker
// are the ledger's existing spellings for this object and its row element.
// Target evidence: retail 0x004257AD builds a temporary at ebp-0x28 with
// 0x00424CB6, passes it to the rowed vector fill constructor 0x0042545A for
// the member at +0x00, destroys it with LightSubPoint's rowed destructor
// 0x004247E3 and stores its first argument at +0x0C; the destructor thunk
// 0x00425801 and scalar deleting destructor 0x00425826 tear the same object
// down. The STL view only declares the rowed callees, so this unit
// instantiates no container code.

class ModuleData;

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A = allocator<T> > class vector
{
public:
	vector(unsigned count, const T &value, const A &alloc = A());
	~vector();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

typedef _STL::vector<const ModuleData *> UnitList;
struct CameraMarker
{
	_STL::vector<UnitList> m_cells;
	UnitList m_units;
};
struct LightSubPoint : CameraMarker
{
	LightSubPoint(unsigned columns);
	~LightSubPoint();
};
class LightPoint
{
public:
	LightPoint(int key, unsigned rows, unsigned columns);
	_STL::vector<CameraMarker> m_points;
	int m_key;
};

LightPoint::LightPoint(int key, unsigned rows, unsigned columns) : m_points(rows, LightSubPoint(columns))
{
	m_key = key;
}
