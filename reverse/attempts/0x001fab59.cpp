// ?update@Rva001FAB59@@QAE_NH@Z
// partial score=0.956 date=2026-10-13
// ?update@Rva001FAB59@@QAE_NH@Z
// partial score=0.9614 date=2026-10-11
// cl: /O1 /Ob2 /Oy- /MD /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii
// ?update@Rva001FAB59@@QAE_NH@Z  retail 0x001FAB59..0x001FB201 (1704 B) RET 4
// Intended home: Code/GameEngine/Source/GameClient/System/ParticleSystemUpdate.cpp
// (includes are written relative to that path). ZH ParticleSystem::update shape
// plus BFME2 profiling/bone attachment from WB debug body 0xB11B60.
// Status 2026-10-11: compiles 1709 B; everything matches except the Matrix3D::mul
// row-0 Z term in all four columns (retail movaps xmm3,xmm2; mulss xmm3,[esi+8];
// ours movss xmm3,[esi+8]; mulss xmm3,xmm2) and the column-W row-1 X term.
// Levers found: Vector3 Get_Translation + forceinline set through a pointer fixes
// the translation copies; const Real *r = &row.X indexing in submul flips the Y
// terms; Bool transformSet declared before parentXfrm (ZH order) matters.
// Object transform is at +0x8. Canonical Coord3D only, no dead throw block.
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Vector3
{
public:
	__forceinline Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X, Y, Z;
};

class Vector4
{
public:
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	Real X, Y, Z, W;
};

static __forceinline Real submul(const Vector4 &row, Real tmp1, Real tmp2, Real tmp3)
{
	const Real *r = &row.X;
	return r[0] * tmp1 + r[1] * tmp2 + r[2] * tmp3;
}

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}
	__forceinline Vector3 Get_Translation() const { return Vector3(Row[0].W, Row[1].W, Row[2].W); }
	__forceinline void Set_X_Translation(Real x) { Row[0].W = x; }
	__forceinline void Set_Y_Translation(Real y) { Row[1].W = y; }
	__forceinline void Set_Z_Translation(Real z) { Row[2].W = z; }

	// does "this = A * B"
	__forceinline void mul(const Matrix3D &A, const Matrix3D &B)
	{
		Real tmp1, tmp2, tmp3;

		tmp1 = B.Row[0].X;
		tmp2 = B.Row[1].X;
		tmp3 = B.Row[2].X;

		this->Row[0].X = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].X = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].X = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].Y;
		tmp2 = B.Row[1].Y;
		tmp3 = B.Row[2].Y;

		this->Row[0].Y = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].Y = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].Y = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].Z;
		tmp2 = B.Row[1].Z;
		tmp3 = B.Row[2].Z;

		this->Row[0].Z = submul(A.Row[0], tmp1, tmp2, tmp3);
		this->Row[1].Z = submul(A.Row[1], tmp1, tmp2, tmp3);
		this->Row[2].Z = submul(A.Row[2], tmp1, tmp2, tmp3);

		tmp1 = B.Row[0].W;
		tmp2 = B.Row[1].W;
		tmp3 = B.Row[2].W;

		this->Row[0].W = submul(A.Row[0], tmp1, tmp2, tmp3) + A.Row[0].W;
		this->Row[1].W = submul(A.Row[1], tmp1, tmp2, tmp3) + A.Row[1].W;
		this->Row[2].W = submul(A.Row[2], tmp1, tmp2, tmp3) + A.Row[2].W;
	}

	Vector4 Row[3];
};

static __forceinline void setCoord(Coord3D *c, Real x, Real y, Real z)
{
	c->x = x;
	c->y = y;
	c->z = z;
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct ParticleGlobalDataView
{
	char pad[0x9AF];
	Bool m_useFX;		// +0x9AF
	char pad9B0[0x9C2 - 0x9B0];
	Bool m_profileFX;	// +0x9C2
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	Int getCurrentClientBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;
	Bool isShroudedDrawable() const { return m_shrouded; }
	Bool isVisibleDrawable() const { return m_visible; }
private:
	char pad[0x440];
	Bool m_shrouded;	// +0x440
	Bool m_visible;		// +0x441
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};

class Object : public Thing
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	char pad[0x8];
	Matrix3D m_transform;	// +0x8
};

class GameClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual Drawable *findDrawableByID(Int id);	// +0x40
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual UnsignedInt getFrame();	// +0x7C
};
extern GameClient *TheGameClient;
extern GameLogic *TheGameLogic;

struct Rva001F38C1Arg { int v[12]; };
class Rva001F38C1Slot { public: void set(const Rva001F38C1Arg &); };
class Rva001F3C9A { public: bool rva001F3C9A(); };
class Rva001FA7F8 { public: void rva001FA7F8(); };
class ParticleSystem { public: void destroy(); void rva001F4696(void *, void *, bool, void *); };

class ControlParticleView
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	char pad[0x1C];
	Coord3D m_pos;	// +0x1C
};

class Rva001FAB59
{
public:
	Bool update(Int localPlayerIndex);
private:
	Int getPriority() const { return m_priority; }

	char pad0[0x7C];
	Int m_priority;			// +0x7C
	char pad80[0xAC - 0x80];
	Real m_updateTime;		// +0xAC
	Int m_attachedToDrawableID;	// +0xB0
	ObjectID m_attachedToObjectID;	// +0xB4
	AsciiString m_attachedBoneName;	// +0xB8
	Matrix3D m_localTransform;	// +0xBC
	Matrix3D m_transform;		// +0xEC
	UnsignedInt m_burstDelayLeft;	// +0x11C
	UnsignedInt m_delayLeft;	// +0x120
	UnsignedInt m_startTimestamp;	// +0x124
	UnsignedInt m_systemLifetimeLeft;	// +0x128
	char pad12C[0x144 - 0x12C];
	Coord3D m_pos;			// +0x144
	Coord3D m_lastPos;		// +0x150
	char pad15C[0x16C - 0x15C];
	void *m_masterSystem;		// +0x16C
	char pad170[0x19C - 0x170];
	ControlParticleView *m_controlParticle;	// +0x19C
	Bool m_isLocalIdentity;		// +0x1A0
	Bool m_isIdentity;		// +0x1A1
	Bool m_isForever;		// +0x1A2
	Bool m_isStopped;		// +0x1A3
	Bool m_isDestroyed;		// +0x1A4
	Bool m_1A5;
	Bool m_1A6;
	Bool m_1A7;
	Bool m_skipParentXfrm;		// +0x1A8
	char pad1A9[3];
	Rva001FA7F8 m_modules;		// +0x1AC
};

Bool Rva001FAB59::update(Int localPlayerIndex)
{
	m_updateTime = 0.0f;
	__int64 startTime, frequency, endTime;
	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_profileFX)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);
	}

	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_useFX == false)
		return false;

	// do initial delay ... note, this currently delays the lifetime
	if (m_delayLeft)
	{
		--m_delayLeft;

		// system actually "starts" once initial delay is over
		if (m_delayLeft == 0)
			m_startTimestamp = TheGameClient->getFrame();

		return true;
	}

	Bool isHidden = false;
	Bool isShrouded = false;

	if (m_masterSystem == NULL)
	{
		Bool transformSet = false;
		const Matrix3D *parentXfrm = NULL;

		if (m_attachedToDrawableID)
		{
			Drawable *attachedTo = TheGameClient->findDrawableByID(m_attachedToDrawableID);

			if (attachedTo)
			{
				if (!attachedTo->isVisibleDrawable())
					isHidden = true;
				if (attachedTo->isShroudedDrawable())
					isShrouded = true;

				parentXfrm = attachedTo->getTransformMatrix();

				m_lastPos = m_pos;
				Vector3 pos = parentXfrm->Get_Translation();
				setCoord(&m_pos, pos.X, pos.Y, pos.Z);

				if (!m_attachedBoneName.isEmpty())
				{
					Matrix3D boneXfrm;
					if (attachedTo->getCurrentClientBonePositions(m_attachedBoneName.str(), 0, NULL, &boneXfrm, 1))
						((Rva001F38C1Slot *)this)->set((const Rva001F38C1Arg &)boneXfrm);
				}
			}
			else
			{
				// Drawable has been destroyed - lose our attachment to it
				m_attachedToDrawableID = 0;

				// destroy ourselves
				((ParticleSystem *)this)->destroy();
			}
		}
		else if (m_attachedToObjectID)
		{
			Object *objectAttachedTo = TheGameLogic->findObjectByID(m_attachedToObjectID);

			if (objectAttachedTo)
			{
				if (!isShrouded)
					isShrouded = (objectAttachedTo->getShroudStatusForPlayer(localPlayerIndex) >= CELLSHROUD_COUNT);

				Drawable *draw = objectAttachedTo->getDrawable();
				if (draw)
				{
					if (!draw->isVisibleDrawable())
						isHidden = true;
					parentXfrm = draw->getTransformMatrix();

					if (!m_attachedBoneName.isEmpty())
					{
						Matrix3D boneXfrm;
						if (draw->getCurrentClientBonePositions(m_attachedBoneName.str(), 0, NULL, &boneXfrm, 1))
							((Rva001F38C1Slot *)this)->set((const Rva001F38C1Arg &)boneXfrm);
					}
				}
				else
					parentXfrm = objectAttachedTo->getTransformMatrix();

				m_lastPos = m_pos;
				Vector3 pos = parentXfrm->Get_Translation();
				setCoord(&m_pos, pos.X, pos.Y, pos.Z);
			}
			else
			{
				// Object has been destroyed - lose our attachment to it
				m_attachedToObjectID = INVALID_OBJECT_ID;

				// destroy ourselves
				((ParticleSystem *)this)->destroy();
			}
		}

		if (parentXfrm)
		{
			if (m_skipParentXfrm)
			{
				// this particle system is already in world space so no need to apply parent xform.
				m_transform = m_localTransform;
			}
			else
			{
				// if system has its own local transform, concatenate them
				if (m_isLocalIdentity == false)
					m_transform.mul(*parentXfrm, m_localTransform);
				else
					m_transform = *parentXfrm;
			}

			m_isIdentity = false;
			transformSet = true;
		}

		if (transformSet == false)
		{
			if (m_isLocalIdentity == false)
			{
				m_transform = m_localTransform;
				m_isIdentity = false;
			}
			else
			{
				m_isIdentity = true;
			}
		}

		// if we are controlled by a particle, its position is local origin
		if (m_controlParticle)
		{
			const Coord3D *controlPos = m_controlParticle->getPosition();
			m_transform.Set_X_Translation(controlPos->x);
			m_transform.Set_Y_Translation(controlPos->y);
			m_transform.Set_Z_Translation(controlPos->z);
			m_isIdentity = false;
			m_lastPos = m_pos;
			m_pos = *controlPos;
		}

		if (m_isDestroyed == false)
		{
			if (m_isForever || (m_isForever == false && m_systemLifetimeLeft > 0))
			{
				if (!isShrouded && m_isStopped == false && !isHidden)
					((ParticleSystem *)this)->rva001F4696(&m_pos, (void *)getPriority(), m_isIdentity, &m_transform);
			}
		}
	}

	m_modules.rva001FA7F8();
	Bool result = ((Rva001F3C9A *)this)->rva001F3C9A();

	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_profileFX)
	{
		QueryPerformanceCounter(&endTime);
		m_updateTime = (Real)((endTime - startTime) * 1000.0f / frequency);
	}

	return result;
}
