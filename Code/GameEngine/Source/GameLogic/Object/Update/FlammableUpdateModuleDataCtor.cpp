// cl: /O1 /arch:SSE /G7 /EHsc /DNDEBUG /MD /Ireference/shims/moduledata
// stlport
//
// ??0FlammableUpdateModuleData@@QAE@XZ, retail 0x0048D541..0x0048D60C (203
// bytes, EH): the FlammableUpdateModuleData constructor; the factory
// friend_newModuleData 0x0024D068 news 0x58 and calls it, and its destructor
// 0x0048D075 and field parse table 0x00C4C600 are rowed. Layout and member
// names follow FlammableUpdateModuleDataDtor.cpp. Defaults: the four delays
// zero, flame damage limit 20.0, expiration five seconds of logic frames
// (the frame-rate global at 0x00DBA4E4), damage type 6, burned status set,
// run-to-water depth 0.0 with search radius 200.0 and increment 60.0, custom
// animation -1. The CameraMarker vector is built empty (STLport vector base
// 0x00211E58) and cleared through the rowed CameraMarkerVec::erase; retail
// stores the +0x4C..+0x54 defaults on both sides of that call.
#include <vector>
#include "Common/Snapshot.h"

extern int BfmeLogicFramesPerSecond;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BurningSoundHolder
{
	BurningSoundHolder() : m_ptr(0) {}
	~BurningSoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

// 8-byte element with a destructor (StlportVectorDtorChains.cpp).
class CameraMarker { public: ~CameraMarker(); char m_pad[8]; };
struct CameraMarkerVec : public _STL::vector<CameraMarker>
{
	__forceinline CameraMarkerVec() {}
	~CameraMarkerVec();
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);
	void clear() { erase(begin(), end()); }
};

// The custom animation entry at +0x4C: an animation type (-1 for none) and
// two words.
struct CustomAnimAndDuration
{
	void reset()
	{
		m_animType = -1;
		m_frames = 0;
		m_extra = 0;
	}
	int m_animType;
	int m_frames;
	int m_extra;
};

class FlammableUpdateModuleData : public Snapshot
{
public:
	FlammableUpdateModuleData();
	virtual ~FlammableUpdateModuleData();

private:
	int m_unused04; // +0x04, retail never stores it
	int m_burnedDelay; // +0x08
	int m_aflameDuration; // +0x0C
	int m_aflameDamageDelay; // +0x10
	int m_aflameDamageAmount; // +0x14
	BurningSoundHolder m_burningSound; // +0x18
	float m_flameDamageLimit; // +0x1C
	int m_flameDamageExpiration; // +0x20
	int m_damageType; // +0x24
	CameraMarkerVec m_fireMarkers; // +0x28
	bool m_setBurnedStatus; // +0x34
	bool m_swapModelWhenAflame; // +0x35
	bool m_swapModelWhenQuenched; // +0x36
	bool m_swapTextureWhenAflame; // +0x37
	bool m_swapTextureWhenQuenched; // +0x38
	bool m_burnContained; // +0x39
	bool m_runToWater; // +0x3A
	float m_runToWaterDepth; // +0x3C
	float m_runToWaterSearchRadius; // +0x40
	float m_runToWaterSearchIncrement; // +0x44
	bool m_panicLocomotorWhileAflame; // +0x48
	CustomAnimAndDuration m_customAnimAndDuration; // +0x4C
};

FlammableUpdateModuleData::FlammableUpdateModuleData()
	: m_burnedDelay(0)
	, m_aflameDuration(0)
	, m_aflameDamageDelay(0)
	, m_aflameDamageAmount(0)
	, m_flameDamageLimit(20.0f)
	, m_flameDamageExpiration(BfmeLogicFramesPerSecond * 5)
	, m_damageType(6)
{
	m_runToWaterDepth = 0.0f;
	m_runToWaterSearchRadius = 200.0f;
	m_setBurnedStatus = true;
	m_swapModelWhenAflame = false;
	m_swapModelWhenQuenched = false;
	m_swapTextureWhenAflame = false;
	m_swapTextureWhenQuenched = false;
	m_burnContained = false;
	m_runToWater = false;
	m_runToWaterSearchIncrement = 60.0f;
	m_panicLocomotorWhileAflame = false;
	m_customAnimAndDuration.reset();
	m_fireMarkers.clear();
	m_customAnimAndDuration.reset();
}
