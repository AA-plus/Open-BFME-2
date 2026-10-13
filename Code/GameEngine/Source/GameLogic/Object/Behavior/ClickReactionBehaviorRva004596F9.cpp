// cl: /DNDEBUG /MD /EHsc
//
// ?rva004596F9@ClickReactionBehavior@@UAEXXZ, retail 0x004596F9 (363 bytes).
// Slot 1 of the ClickReactionBehavior interface at +0x20 (vtable 0x00841188;
// slot 0 is the unrowed 0x004543E3, slot 2 the rowed 0x00459864 that the
// matched ctor 0x0045961D's sibling slots reach). Its fields are the two the
// ctor clears and the rowed xfer 0x00459579 saves: the click count at +0x24
// and the reaction cool-down at +0x28.
//
// A click is counted when the owner has a drawable, is not in the status
// bit 8 / model conditions 162 and 172 states and is idle (AI slot 110): the
// module data's +0x08 weight is added to the count, which is clamped to five
// times the weight (std::min over addresses, as WB 0x01178F60 shows). With no
// cool-down running the reaction number is count / weight; at three or less it
// is rerolled with GetGameLogicRandomValue(1, 3). Reactions 1..5 set model
// conditions 164..168 (word +0x120 bits 4..8), the drawable's pending
// conditions are applied (0x00274176 false) and the cool-down becomes the
// module data's per-reaction frame count (+0x0C array of five).
// WB's debug body gives the order; retail's identity beyond that is not
// established, so the name stays address-derived. Retail's dec chain tests
// reactions 1..5 and has no branch after the fifth test: the switch's
// `default` repeats case 5's statement, which cl tail-merges into the same
// block (a lone default drops the fifth test, a lone case 5 keeps a jne).

class Thing;
class ModuleData;
class Drawable;

class AIUpdateInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s0A(); virtual void s0B(); virtual void s0C(); virtual void s0D(); virtual void s0E();
	virtual void s0F(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s1A(); virtual void s1B(); virtual void s1C(); virtual void s1D();
	virtual void s1E(); virtual void s1F(); virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s2A(); virtual void s2B(); virtual void s2C();
	virtual void s2D(); virtual void s2E(); virtual void s2F(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s3A(); virtual void s3B();
	virtual void s3C(); virtual void s3D(); virtual void s3E(); virtual void s3F(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s4A();
	virtual void s4B(); virtual void s4C(); virtual void s4D(); virtual void s4E(); virtual void s4F();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s5A(); virtual void s5B(); virtual void s5C(); virtual void s5D(); virtual void s5E();
	virtual void s5F(); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s6A(); virtual void s6B(); virtual void s6C(); virtual void s6D();
	virtual bool isIdle(); // slot 110 (+0x1B8)
};

static __forceinline bool testWordBit(const unsigned int *words, unsigned int bit)
{
	return (words[bit >> 5] >> (bit & 0x1f)) & 1;
}

class Rva0028B7AELeaGetter
{
public:
	void *get() const; // 0x0028B7AE
};

class Drawable
{
public:
	void rva00274176(bool flag);
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}

	unsigned int m_words[19];
};

class Object
{
public:
	Drawable *getDrawable() const; // Thing::getDrawable 0x005508E2
	void rva0028AE6D();
	bool testCondition(unsigned int bit) const
	{
		return testWordBit(m_modelConditionFlags.m_words, bit);
	}
	__forceinline void setModelConditionState(unsigned int bit)
	{
		if (m_modelConditionFlags.test(bit) == 0)
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};

struct ClickReactionBehaviorModuleData
{
	unsigned char m_pad00[0x08];
	int m_weight; // +0x08
	int m_cooldown[5]; // +0x0C
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class ClickReactionBehaviorIface
{
public:
	virtual void slot0();
	virtual void rva004596F9();
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

class UpdateModuleView : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ClickReactionBehavior : public UpdateModuleView, public ClickReactionBehaviorIface
{
public:
	virtual void slot0();
	virtual void rva004596F9();
private:
	int m_clicks; // +0x24
	int m_cooldown; // +0x28
};

static __forceinline const int &minRef(const int &a, const int &b)
{
	if (a < b)
		return a;
	return b;
}

// ?rva004596F9@ClickReactionBehavior@@UAEXXZ @0x004596F9
void ClickReactionBehavior::rva004596F9()
{
	const ClickReactionBehaviorModuleData *data = (const ClickReactionBehaviorModuleData *)m_moduleData;
	Object *obj = m_object;
	if (!obj)
		return;
	Drawable *draw = obj->getDrawable();
	if (!draw)
		return;
	if (testWordBit((const unsigned int *)((Rva0028B7AELeaGetter *)obj)->get(), 8))
		return;
	if (obj->testCondition(162))
		return;
	if (obj->testCondition(172))
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai || !ai->isIdle())
		return;
	int weight = data->m_weight;
	if (weight <= 0)
		return;
	m_clicks += weight;
	int limit = weight * 5;
	{
		const int &chosen = minRef(limit, m_clicks);
		m_clicks = chosen;
	}
	if (m_cooldown > 0)
		return;
	int reaction = m_clicks / weight;
	if (reaction <= 3)
		reaction = GetGameLogicRandomValue(1, 3, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\ClickReactionBehavior.cpp", 116);
	if (reaction <= 0)
		return;
	__assume(reaction <= 5);
	switch (reaction)
	{
	case 1:
		obj->setModelConditionState(164);
		break;
	case 2:
		obj->setModelConditionState(165);
		break;
	case 3:
		obj->setModelConditionState(166);
		break;
	case 4:
		obj->setModelConditionState(167);
		break;
	case 5:
		obj->setModelConditionState(168);
		break;
	default:
		obj->setModelConditionState(168);
		break;
	}
	draw->rva00274176(false);
	int index = reaction - 1;
	if (index >= 0 && index < 5)
		m_cooldown = data->m_cooldown[index];
}
