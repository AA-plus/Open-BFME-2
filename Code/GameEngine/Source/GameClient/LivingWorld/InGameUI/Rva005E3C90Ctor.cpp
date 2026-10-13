// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Native 0x005E3C90..0x005E3D22, the unit-icon sibling of Rva005E3BD5.
// WB 0x015FB850 witnesses virtual-base, ArmyUnitIcon, Rva005E39F3 order.
// Shared virtual base is at +0x30, reference view at +0x1C; sizeof is 0x3C.
// The five constructor arguments include the compiler's virtual-base flag.
// Pointer types and address names remain the existing providers' ABI views.
class Rva005F3F73
{
public:
	Rva005F3F73(void *, void *) throw();
private:
	char storage[0x18];
};

class Rva005F4096
{
public:
	void clear();
	Rva005F4096(Rva005F3F73 *p) : m_ptr(p) {}
private:
	Rva005F3F73 *m_ptr;
};

class Rva005F4179Base
{
public:
	Rva005F4179Base() : m_04(0) {}
	virtual ~Rva005F4179Base() {}
protected:
	int m_04;
};

class ArmyHeroIconMovieClip;

class Rva005F4179 : public Rva005F4179Base
{
public:
	Rva005F4179(void *clip);
	virtual ~Rva005F4179();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	Rva005F4096 m_08;
};

struct Rva005F38D8Ref
{
	void *m_ptr;
	~Rva005F38D8Ref();
};

class Rva005F38D8
{
public:
	Rva005F38D8Ref rva005F38D8(int position);
	void *unknown00;
	void *implementation;
};

struct Rva005E39F3Arg
{
	char m_pad[0x10];
	void *m_10;
	char m_pad14[0x4];
	Rva005F38D8 *m_18;
};

class Rva005E39F3 : public virtual Rva005F4179
{
public:
	Rva005E39F3(Rva005E39F3Arg *arg, void *clip, int count);
	virtual void DoUpdate();
private:
	Rva005E39F3Arg *m_04;
	int m_08;
	Rva005F38D8Ref m_0c;
};

class ArmyHeroIconMovieClip;

namespace StrategicInGameUI
{
class ArmyHeroIcon : public virtual Rva005F4179
{
public:
	ArmyHeroIcon(void *owner, void *clip, void *entry);
	virtual ~ArmyHeroIcon();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	void *m_owner;
	void *m_hero;
	void *m_clip;
};
}

// ArmyDetailsPanel icon ctor family member 2: retail 0x005E3BD5 (146B,
// RET 0x14). ArmyHeroIcon base at +0, virtual Rva005E39F3 at +0x10 and the
// shared virtual Rva005F4179 base at +0x24 (vtordisp +0x20). The ctor
// constructs the shared virtual base first, then the ArmyHeroIcon base from
// the arg's +0x10 owner, then the icon base.
class Rva005E3BD5 : public StrategicInGameUI::ArmyHeroIcon, public Rva005E39F3
{
public:
	Rva005E3BD5(Rva005E39F3Arg *arg, void *clip, int count, void *entry);
	virtual void DoUpdate();
};


struct UnitView;
namespace StrategicInGameUI {
class ArmyUnitIcon:public virtual Rva005F4179 {
public:
 ArmyUnitIcon(void*,void*,UnitView*);
 virtual ~ArmyUnitIcon();
 virtual void DoUpdate();
private:char storage[0x18];
};
}
class Rva005E3C90:public StrategicInGameUI::ArmyUnitIcon,public Rva005E39F3 {
public:
 Rva005E3C90(Rva005E39F3Arg*,void*,int,UnitView*);
 virtual void DoUpdate();
};
Rva005E3C90::Rva005E3C90(Rva005E39F3Arg *arg,void *clip,int count,UnitView *entry)
 :Rva005F4179(clip),StrategicInGameUI::ArmyUnitIcon(arg->m_10,clip,entry),Rva005E39F3(arg,clip,count){}

typedef char IconSizeIs60[sizeof(Rva005E3C90)==60?1:-1];
