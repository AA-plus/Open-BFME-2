// ?rva004ACF1D@RousingSpeechUpdate@@QAEXXZ
// partial score=0.83 date=2026-10-01
// cl: /O1 /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva004ACF1D@RousingSpeechUpdate@@QAEXXZ retail 0x004ACF1D (89 bytes): the
// RousingSpeechUpdate twin of the matched GloriousChargeUpdate list helper
// 0x004AD613 (walks the +0x88 ObjectID list clearing condition bit 6*32+9 and
// the +0x44C dword of each live object, then resets the list), called only by
// the matched RousingSpeechUpdate::update 0x004AD019. Same model as
// RousingSpeechUpdateUpdate.cpp; this body is exact except that cl gives the
// list address edi and the object ebx where retail uses ebx and edi (15 bytes).
// Tried: reference or pointer local for the list, continue form, while loop,
// object and iterator declared at function scope, a forceinline Object member
// for the clear-and-zero.
#include "../../../Common/GameLogicObjectLookupView.h"
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
class Drawable;
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
enum KindOfType
{
	KINDOF_FIRST = 0
};
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
	bool isKindOf(KindOfType t) const;
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x44C - 0x15C];
	int m_44C; // +0x44C
};
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
extern GameLogic *TheGameLogic;
namespace {
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHashVF;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectPtrHashVF &m = *(ObjectPtrHashVF *)((char *)this + 0xB4);
	ObjectPtrHashVF::iterator it = m.find(id);
	if (it == m.end())
		return 0;
	return (*it).second;
}
class Rva00270619
{
public:
	void Rva00270619Clear(int bit);
};
struct Rva004AD613Node
{
	Rva004AD613Node *m_next;
	Rva004AD613Node *m_prev;
	ObjectID m_id;
};
struct Rva004AD613Iterator
{
	Rva004AD613Node *m_node;
	ObjectID &operator*() const { return m_node->m_id; }
	Rva004AD613Iterator &operator++() { m_node = m_node->m_next; return *this; }
	bool operator!=(const Rva004AD613Iterator &other) const { return m_node != other.m_node; }
};
class Rva0029FB3BMember
{
public:
	bool empty() const { return m_head->m_next == m_head; }
	Rva004AD613Iterator begin() const { Rva004AD613Iterator it; it.m_node = m_head->m_next; return it; }
	Rva004AD613Iterator end() const { Rva004AD613Iterator it; it.m_node = m_head; return it; }
	void reset();
	Rva004AD613Node *m_head;
};
class Thing;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};
// Primary-vtable slots 1..17 of SpecialAbilityUpdate (vtable 0x00C3FBA8);
// only the positions of slots 15 and 17 matter to this unit.
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14();
	virtual void slot15(); // 0x00450D9A, GloriousChargeUpdate 0x004AD554
	virtual void slot16();
	virtual void slot17(); // 0x0045108D, GloriousChargeUpdate 0x004AD8E3
private:
	unsigned char m_pad24[0x88 - 0x24];
};
class RousingSpeechUpdateModuleData
{
public:
	unsigned char m_pad[0xC8];
	float m_C8; // +0xC8
	unsigned int m_CC; // +0xCC
	int m_D0; // +0xD0
	unsigned char m_padD4[0xDC - 0xD4];
	bool m_DC; // +0xDC
	float m_E0; // +0xE0
};
class RousingSpeechUpdate : public SpecialAbilityUpdate
{
public:
	void rva004ACF1D();
	virtual UpdateSleepTime update();
private:
	const RousingSpeechUpdateModuleData *getRousingSpeechData() const
	{
		return (const RousingSpeechUpdateModuleData *)m_moduleData;
	}
	Rva0029FB3BMember m_88; // +0x88
	unsigned int m_8C; // +0x8C
	bool m_90; // +0x90
	float m_94; // +0x94
	float m_98; // +0x98
};
void RousingSpeechUpdate::rva004ACF1D()
{
	if (!m_88.empty())
	{
		for (Rva004AD613Iterator it = m_88.begin(); it != m_88.end(); ++it)
		{
			Object *object = TheGameLogic->findObjectByID(*it);
			if (object)
			{
				clearModelConditionBit(object, 6 * 32 + 9);
				object->m_44C = 0;
			}
		}
		m_88.reset();
	}
}
