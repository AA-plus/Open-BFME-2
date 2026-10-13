// ?rva000C6E1A@Rva000C6E1A@@QAEXXZ
// partial score=0.95 date=2026-10-13
// ?rva000C6E1A@Rva000C6E1A@@QAEXXZ
// partial score=0.97 date=2026-10-13
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?rva000C6E1A@Rva000C6E1A@@QAEXXZ  retail 0x000C6E1A..0x000C7699 (2175B)
// WorldBuilder twin 0x0092DD90 (4394B, unnamed).
//
// Client particle systems attached to the bones of a W3DModelDraw-like draw
// module. Once the dirty byte (+0x48) is set it concatenates the particle-bone
// records of the current condition state (+0x18, list at +0x74) and of the
// module data (+0x14, list at +0xB4) into a local list and walks it: records
// with a persist id that is already tracked in the list at +0x64 are skipped
// (or the tracked system is destroyed, kind 1 also erases the entry, kind 2
// marks it), the rest create a system, place it (client bone matrices, bone
// translation or bone-less origin), apply the only-on-water / only-on-land
// terrain query, attach it to the drawable and track it. When the dirty byte
// is clear the secondary interface at +0xC takes slot 0x6C(1) and the bone
// attachment update 0xC65CB runs instead.
//
// Layout facts are target reads (retail accesses); the record fields come from
// the scripted-model INI reader (W3DScriptedModelDrawParticleSysBone.cpp) and
// the copy at 0xB75AE: text +0 / trigger +4 / persist id +8 / persist kind +0xC /
// callback arg +0x10 / callback +0x14 / template +0x18 / follow-bone +0x1C /
// house colour +0x1D / only-on-land +0x1E / only-on-water +0x1F. Donor: ZH
// W3DModelDraw::recalcBonesForClientParticleSystems supplies the bone placement
// shape; the owning class name is not established.
#define _STLP_NO_EXCEPTIONS 1
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <list>
#include "ascii_string.h"
#include "Coord3D.h"
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }

// Opaque 4B list proxy: clear() and the base dtor are the pins of
// StlportPod248ElementDtor.cpp (0x239D49 / 0x2FECBC; payload 32B per 0xB92D2). Retail
// tears a local Pod32 list down as an explicit clear, the unwind-state reset, then the
// out-of-line base dtor; the two specializations spell that without a second name for 0x2FECBC.
struct Rva000C6D44ListProxy74
{
	void *m_header;
	void clear();
	~Rva000C6D44ListProxy74();
};
namespace _STL {
template <> __forceinline _List_base<BfmePod32, allocator<BfmePod32> >::~_List_base()
{
	reinterpret_cast<Rva000C6D44ListProxy74 *>(this)->~Rva000C6D44ListProxy74();
}
}

// Copy at retail 0xB75AE (row ??0BfmeStringRecord000B75AE@@QAE@ABU0@@Z).
struct BfmeStringRecord000B75AE {
	AsciiString text;
	unsigned int trigger, persistId, persistKind, callbackArg;
	void (*callback)(unsigned int, unsigned int);
	unsigned int sysTemplate;
	unsigned char followBone, houseColor, onlyOnLand, onlyOnWater;
	BfmeStringRecord000B75AE(const BfmeStringRecord000B75AE &o);
};

// Tracker record, copy at retail 0xB757D.
struct BfmeStringRecord000B757D {
	unsigned int word0, word1; AsciiString text; unsigned int word2; unsigned char tail;
	BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o);
	BfmeStringRecord000B757D() {}
};
inline bool operator==(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 == y.word0; }
inline bool operator<(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 < y.word0; }

struct Vector3
{
	__forceinline Vector3() {}
	__forceinline Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	float X, Y, Z;
};

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(const Vector4 &v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) {}
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Matrix3D(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }
	__forceinline Matrix3D(bool)
	{
		Row[0].X = 1.0f; Row[0].Y = 0.0f; Row[0].Z = 0.0f; Row[0].W = 0.0f;
		Row[1].X = 0.0f; Row[1].Y = 1.0f; Row[1].Z = 0.0f; Row[1].W = 0.0f;
		Row[2].X = 0.0f; Row[2].Y = 0.0f; Row[2].Z = 1.0f; Row[2].W = 0.0f;
	}
	__forceinline void Scale(float scale)
	{
		Row[0][0] *= scale; Row[1][0] *= scale; Row[2][0] *= scale;
		Row[0][1] *= scale; Row[1][1] *= scale; Row[2][1] *= scale;
		Row[0][2] *= scale; Row[1][2] *= scale; Row[2][2] *= scale;
	}
	__forceinline Vector3 Get_Translation() const { Vector3 v; v.X = Row[0][3]; v.Y = Row[1][3]; v.Z = Row[2][3]; return v; }
	float Get_Z_Rotation(void) const;
	Vector4 Row[3];
};

struct Rva001F3899Arg { float x, y, z; };
struct Rva001F38C1Arg { float v[12]; };
class Rva0055A88BDwordField;

class Rva001F3C20Slot { public: void set(const Rva0055A88BDwordField *) throw(); };
class Rva001F3899Slot : public Rva001F3C20Slot { public: void set(const Rva001F3899Arg &) throw(); };
class Rva001F38C1Slot : public Rva001F3899Slot { public: void set(const Rva001F38C1Arg &) throw(); };
class Rva001F3852ByteOneSetter { public: void enable() throw(); };

class ParticleSystemColorSink { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void setColor(int color); };

class ParticleSystem : public Rva001F38C1Slot
{
public:
	void destroy() throw();
	void rva001F45F4(Bool enabled) throw();
	void rotateLocalTransformZ(float rotation) throw();
	char m_pad[0x1A7];
};
ParticleSystem *Make001FCBD7(void);

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	__forceinline ~BfmeParticleSystemHandle() throw() { if (m_system) rva0004CBC0(); }
	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}
};

class ParticleSystemTemplate;
class Rva000C6E1A;
class ParticleSystemManager
{
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
	friend class Rva000C6E1A;
public:
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};
extern ParticleSystemManager *TheParticleSystemManager;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18();
	virtual bool isUnderwater(float x, float y, float *waterZ, float *terrainZ, void *extra);	// +0x4C
};
extern TerrainLogic *TheTerrainLogic;

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass
{
public:
	virtual void Delete_This();								// +0x00
	RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03)
	RENDEROBJ_SLOT(04) RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07)
	RENDEROBJ_SLOT(08) RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11)
	RENDEROBJ_SLOT(12) RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15)
	RENDEROBJ_SLOT(16) RENDEROBJ_SLOT(17) RENDEROBJ_SLOT(18) RENDEROBJ_SLOT(19)
	virtual void Validate_Transform() const;						// +0x50
	virtual void Set_Transform(const Matrix3D &m);						// +0x54
	RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23)
	RENDEROBJ_SLOT(24) RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27)
	RENDEROBJ_SLOT(28) RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31)
	RENDEROBJ_SLOT(32) RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35)
	RENDEROBJ_SLOT(36) RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39)
	RENDEROBJ_SLOT(40) RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43)
	RENDEROBJ_SLOT(44) RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47)
	RENDEROBJ_SLOT(48) RENDEROBJ_SLOT(49)
	virtual int Get_Bone_Index(const char *bonename);					// +0xC8
	virtual Matrix3D Get_Bone_Transform(int boneindex);					// +0xCC

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return Transform;
	}
	int m_pad04[5];
	Matrix3D Transform;									// +0x18
};

class Object { public: int getIndicatorColor() const; };
class Rva00270260 { public: bool rva00270260(); };
class Rva000788D3FloatField { public: float get() const; };

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	int getCurrentClientBonePositions(const char *bone, int a, Coord3D *pos, Matrix3D *xf, int b) const;
	char m_padFC[0xFC];
	Object *m_object;
	char m_pad100[0x114 - 0x100];
	unsigned int m_flags;
	char m_pad118[0x360 - 0x118];
	unsigned int m_trigger;
};

class Rva000C65CB { public: void rva000C65CB(); };

class ParticleStateView { public: char m_pad[0x74]; _STL::list<BfmePod32> m_bones; };
class ParticleDataView { public: char m_pad[0xB4]; _STL::list<BfmePod32> m_bones; };
class ParticleModuleData { public: char m_pad[0x12A]; bool m_useClientBones; };

static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	float x = A.Row[0][0] * in.X + A.Row[0][1] * in.Y + A.Row[0][2] * in.Z + A.Row[0][3];
	float y = A.Row[1][0] * in.X + A.Row[1][1] * in.Y + A.Row[1][2] * in.Z + A.Row[1][3];
	float z = A.Row[2][0] * in.X + A.Row[2][1] * in.Y + A.Row[2][2] * in.Z + A.Row[2][3];
	out->X = x;
	out->Y = y;
	out->Z = z;
}

static __forceinline void Transform_VectorLand(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	float x = in.X * A.Row[0][0] + in.Y * A.Row[0][1] + in.Z * A.Row[0][2] + A.Row[0][3];
	float y = in.X * A.Row[1][0] + in.Y * A.Row[1][1] + in.Z * A.Row[1][2] + A.Row[1][3];
	float z = in.X * A.Row[2][0] + in.Y * A.Row[2][1] + in.Z * A.Row[2][2] + A.Row[2][3];
	out->X = x;
	out->Y = y;
	out->Z = z;
}

class DrawSecondary
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void slot6C(bool flag);
};

class Rva000C6E1A
{
public:
	void rva000C6E1A();
private:
	char m_pad00[4];
	ParticleModuleData *m_data;							// +0x04
	Drawable *m_drawable;								// +0x08
	DrawSecondary m_secondary;							// +0x0C
	void *m_pad10;
	ParticleDataView *m_particleData;						// +0x14
	ParticleStateView *m_state;							// +0x18
	char m_pad1C[0x48 - 0x1C];
	bool m_dirty;									// +0x48
	bool m_hidden;									// +0x49
	char m_pad4A[0x50 - 0x4A];
	RenderObjClass *m_renderObject;							// +0x50
	char m_pad54[0x64 - 0x54];
	_STL::list<BfmeStringRecord000B757D> m_tracked;					// +0x64
};

void Rva000C6E1A::rva000C6E1A()
{
	if (m_dirty)
	{
		Drawable *drawable = m_drawable;
		if (drawable)
		{
			if (m_state && !(drawable->m_flags & 8))
			{
				_STL::list<BfmePod32> bones;
				for (_STL::list<BfmePod32>::iterator it = m_state->m_bones.begin(); it != m_state->m_bones.end(); ++it)
					bones.push_back(*it);
				for (_STL::list<BfmePod32>::iterator it = m_particleData->m_bones.begin(); it != m_particleData->m_bones.end(); ++it)
					bones.push_back(*it);
				for (_STL::list<BfmePod32>::iterator it = bones.begin(); it != bones.end(); ++it)
				{
					BfmeStringRecord000B75AE rec(*(const BfmeStringRecord000B75AE *)&*it);
					bool skip = false;
					if (rec.persistId)
					{
						if (m_tracked.empty())
						{
							skip = (rec.persistKind == 1 || rec.persistKind == 2);
						}
						else
						{
							for (_STL::list<BfmeStringRecord000B757D>::iterator t = m_tracked.begin(); t != m_tracked.end(); ++t)
							{
								BfmeStringRecord000B757D &entry = *t;
								if (entry.word2 == rec.persistId)
								{
									int kind = rec.persistKind;
									if (kind == 3 || entry.tail)
									{
										skip = true;
										break;
									}
									if (kind == 2 || kind == 1)
									{
										BfmeParticleSystemHandle found = TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)entry.word0);
										if (found.m_system)
											found.m_system->destroy();
										if (kind == 1)
											m_tracked.erase(t);
										if (kind == 2)
											entry.tail = 1;
										skip = true;
										break;
									}
								}
							}
						}
					}
					if (skip)
						continue;
					if (!rec.sysTemplate)
						continue;
					BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(
						(const ParticleSystemTemplate *)rec.sysTemplate, true);
					if (!sys.m_system)
						continue;
					if (rec.trigger)
					{
						unsigned int current = drawable->m_trigger;
						if (current != rec.trigger)
							continue;
					}
					Coord3D pos;
					pos.x = 0.0f;
					pos.y = 0.0f;
					pos.z = 0.0f;
					float rotation = 0.0f;
					volatile int boneIndex;
					if (m_renderObject)
						boneIndex = m_renderObject->Get_Bone_Index(rec.text.str());
					else
						boneIndex = 0;
					if (m_data->m_useClientBones)
					{
						Matrix3D xf;

						Drawable *d = m_drawable;
						_ReadWriteBarrier();
						if (d->getCurrentClientBonePositions((rec.text.str()), 0, 0, &xf, 1))
							((Rva001F38C1Slot *)sys.operator->())->set(*(const Rva001F38C1Arg *)&xf);
							_ReadWriteBarrier();
					}
					else if (rec.followBone)
					{
						if (boneIndex && m_renderObject)
						{
							Matrix3D xf = __vref(m_renderObject)->Get_Bone_Transform(boneIndex);
							((Rva001F38C1Slot *)sys.operator->())->set(*(const Rva001F38C1Arg *)&xf);
						}
						else
						{
							((Rva001F3899Slot *)sys.operator->())->set(*(const Rva001F3899Arg *)&pos);
							sys->rotateLocalTransformZ(0.0f);
						}
					}
					else
					{
						if (boneIndex && m_renderObject)
						{
							Matrix3D originalTransform = m_renderObject->Get_Transform();
							Matrix3D tmp(true);
							tmp.Scale(((Rva000788D3FloatField *)m_drawable)->get());
							m_renderObject->Set_Transform(tmp);
							const Matrix3D boneTransform = m_renderObject->Get_Bone_Transform(boneIndex);
							Vector3 vpos = boneTransform.Get_Translation();
							pos = *(Coord3D *)&vpos;
							rotation = boneTransform.Get_Z_Rotation();
							m_renderObject->Set_Transform(originalTransform);
						}
						((Rva001F3899Slot *)sys.operator->())->set(*(const Rva001F3899Arg *)&pos);
						sys->rotateLocalTransformZ(rotation);
					}
					if (rec.onlyOnWater)
					{
						Vector3 in = *(Vector3 *)&pos;
						Vector3 out = *(Vector3 *)&pos;
						Transform_Vector(*drawable->getTransformMatrix(), in, &out);
						if (!TheTerrainLogic->isUnderwater(out.X, out.Y, 0, 0, 0))
						{
							sys->destroy();
							continue;
						}
					}
					else if (rec.onlyOnLand)
					{
						Vector3 in = *(Vector3 *)&pos;
						Vector3 out = *(Vector3 *)&pos;
						Transform_VectorLand(*drawable->getTransformMatrix(), in, &out);
						if (TheTerrainLogic->isUnderwater(out.X, out.Y, 0, 0, 0))
						{
							sys->destroy();
							continue;
						}
					}
					((Rva001F3C20Slot *)sys.operator->())->set((const Rva0055A88BDwordField *)drawable);
					sys->rva001F45F4(false);
					*((unsigned char *)sys.operator->() + 0x1A7) = rec.followBone;
					Object *object = drawable->m_object;
					if (object && rec.houseColor)
					{
						ParticleSystem *ps = sys.operator->();
						int color = object->getIndicatorColor();
						ParticleSystemColorSink *sink = *(ParticleSystemColorSink **)((char *)ps + 0x1AC);
						if (sink)
							sink->setColor(color);
					}
					if (((Rva00270260 *)drawable)->rva00270260() || m_hidden)
						((Rva001F3852ByteOneSetter *)sys.operator->())->enable();
					BfmeStringRecord000B757D tracker;
					tracker.word0 = *(unsigned int *)((char *)sys.operator->() + 0xA8);
					tracker.word1 = boneIndex;
					tracker.text = rec.text;
					tracker.word2 = rec.persistId;
					tracker.tail = 0;
					if (rec.callback)
						rec.callback(rec.callbackArg, *(unsigned int *)((char *)sys.operator->() + 0xA8));
					if (*((unsigned char *)sys.operator->() + 0x1A7))
						m_tracked.push_front(tracker);
					else
						m_tracked.push_back(tracker);
				}
				reinterpret_cast<Rva000C6D44ListProxy74 *>(&bones)->clear();
			}
			m_dirty = false;
		}
	}
	else
	{
		m_secondary.slot6C(true);
		((Rva000C65CB *)this)->rva000C65CB();
	}
}
