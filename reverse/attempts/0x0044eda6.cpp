// ?rva0044EDA6@SpecialAbilityUpdate@@UAE_NH@Z
// partial score=0.8872761801410743 date=2026-10-11
// cl: /O1 /DNDEBUG /MD
//
// ?rva0044EDA6@Rva00492C59@@UAE_NH@Z, retail 0x00492E79 (132 bytes): slot 8
// of the +0x20 interface table of the teleport special ability update whose
// constructor is rowed as Rva00492C59 (its xfer 0x00492E10 and update
// 0x00492D11 share the class), so `this` is that subobject (module data at
// -0x1C, the Object at -0x18). With a target position and a positive maximum
// distance in the module data (+0xD4), a target farther than that from the
// Object's position (+0x38) is refused; otherwise the SpecialAbilityUpdate
// +0x20 slot-8 base 0x0044EDA6 decides. Named by the base's address, like
// WeaponFireSpecialAbilityUpdateSlot8.cpp.
typedef bool Bool;
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
typedef float Real;
class Object
{
public:
	unsigned char m_pad000[0x38];
	Coord3D m_38; // +0x38
};
struct Rva00492C59ModuleData
{
	unsigned char m_pad000[0xD4];
	Real m_maxDistance; // +0xD4
};
class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	const Rva00492C59ModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};
class SpecialPowerUpdateInterface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual Bool rva0044EDA6(int value);
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual Bool rva0044EDA6(int value);
};
class Rva00492C59 : public SpecialAbilityUpdate
{
public:
	virtual Bool rva0044EDA6(int value);
};
Bool Rva00492C59::rva0044EDA6(int value)
{
	const Coord3D *pos = (const Coord3D *)value;
	if (pos)
	{
		const Rva00492C59ModuleData *data = m_moduleData;
		if (data && data->m_maxDistance > 0.0f)
		{
			Object *obj = m_object;
			if (obj)
			{
				Real dx = pos->x - obj->m_38.x;
				Real dy = pos->y - obj->m_38.y;
				Real dz = pos->z - obj->m_38.z;
				if (dz * dz + dy * dy + dx * dx > data->m_maxDistance * data->m_maxDistance)
					return false;
			}
		}
	}
	return SpecialAbilityUpdate::rva0044EDA6(value);
}

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad00[0x1C];
	int m_val1C;
};

class Rva0044E7A8
{
public:
	bool rva0044E7A8(int arg);
};

class Rva0044EDA6Virt
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual unsigned int s28();
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
	virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
	virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
	virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual unsigned int s69(int v);
};

struct Rva0044EDA6Outer
{
	char m_pad00[0x38];
	Overridable *m_over38; // +0x38
};


extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Bool SpecialAbilityUpdate::rva0044EDA6(int arg)
{
 const Rva0044EDA6Outer *data=(const Rva0044EDA6Outer *)m_moduleData;
 if (!data || !((Rva0044E7A8 *)this)->rva0044E7A8(arg)) return false;
 const Overridable *fin=data->m_over38->friend_getFinalOverride();
 int value=fin->m_val1C;
 if(value!=0x28 && value!=0x27) {_ReadWriteBarrier(); return true;}
 Rva0044EDA6Virt *virt=*(Rva0044EDA6Virt **)((char *)m_object+0x250);
 if(!virt)return false;
 unsigned a=virt->s69(0);unsigned b=virt->s28();
 if(a>=b)return false;
 _ReadWriteBarrier(); return true;
}
