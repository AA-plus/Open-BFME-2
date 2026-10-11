// cl: /MD /EHsc
// ??1MissileUpdate@@MAE@XZ @0x004A76DE 84B: restores five vtables then clear 0x4A7512 then pinned base 0x45BF6E; caller 0x4A789C deleting dtor; then 0x4A789C
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Thing;
class ModuleData;
class Object
{
public:
	unsigned char m_pad[0x38];
	Coord3D m_pos;
};
class Rva004A76DEBase0 { public: virtual ~Rva004A76DEBase0(); const ModuleData *m_moduleData; Object *m_object; };
class Rva004A76DEBase1 { public: virtual ~Rva004A76DEBase1(); };
class Rva004A76DEBase2 { public: virtual ~Rva004A76DEBase2(); unsigned char m_pad[12]; };
class Rva004A76DEBase3 { public: virtual ~Rva004A76DEBase3(); };
class Rva004A76DEBase4 { public: virtual ~Rva004A76DEBase4(); };
class BezierProjectileBehavior : public Rva004A76DEBase0, public Rva004A76DEBase1, public Rva004A76DEBase2, public Rva004A76DEBase3, public Rva004A76DEBase4
{
public:
	virtual ~BezierProjectileBehavior();
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
protected:
	unsigned char m_pad28[0x88 - 0x28];
};
class MissileUpdate : public BezierProjectileBehavior
{
protected:
	virtual ~MissileUpdate();
public:
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
	void Rva004A7512Clear();
	void Rva004A7530Set(int val);
private:
	int m_88;
	unsigned int m_frame;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	unsigned char m_padA0[0xAC - 0xA0];
	Coord3D m_AC;
	unsigned char m_padB8[0xC4 - 0xB8];
	int m_C4;
	int m_C8;
	unsigned char m_CC;
	unsigned char m_CD;
	unsigned char m_CE;
};
MissileUpdate::~MissileUpdate()
{
	Rva004A7512Clear();
}
void MissileUpdate::projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos)
{
	BezierProjectileBehavior::projectileFireAtObjectOrPosition(victim, victimPos);
	Rva004A7530Set(1);
	m_CC = 0;
	m_AC = m_object->m_pos;
}

