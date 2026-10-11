// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// String-slot cluster around 0x000B82F9. Members carry a flag byte, a raw
// name pointer and AsciiString slots; destruction of by-value AsciiString
// parameters emits the shared releaseBuffer worker (0x00036410) through the
// shim destructor, and slot fills go through StringBase::set (0x000366F0)
// via AsciiString::operator= (the operator= inline schedules the member-add
// ahead of the argument push where a direct set call does not).
// Class and member names are address-derived. Probe 0xB82F9 is verified;
// sibling 0xB83A7 follows the record110 string through the same counted probe.

#include "ascii_string.h"
template<> bool StringBase<char>::isEmpty() const;

class Rva000B4BED
{
public:
	void *rva000B4C9D(const void *entry);
	void *rva000B4CBE(const void *entry);
};

class Matrix3D;struct Coord3D;class Object;
class Drawable {public:const Matrix3D*getTransformMatrix()const;const Coord3D*getPosition()const;char pad00[0xFC];Object*object;char pad100[0x14];unsigned char flags114;};
class FXList {public:static void doFXObj(const FXList*,const Object*,const Object*);static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);};
struct AnimationStateBF9FC {char pad00[0x68];const FXList*fx68;char pad6C[0x9C-0x6C];bool repeat9C;};
class Rva000BF9FCHeader {public:virtual void slot0();void*data;Drawable*drawable;};
class Rva000BF9FCModelInterface {public:
virtual void v00();virtual void v01();virtual void v02();virtual void v03();virtual void v04();virtual void v05();virtual void v06();virtual void v07();virtual void v08();virtual void v09();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();virtual void v27();virtual void v28();virtual void refresh();};
struct Rva000B8F5AOuter:public Rva000BF9FCHeader,public Rva000BF9FCModelInterface
{
 bool rva000BF9FC(void *entry,bool force,int options);
 void rva000BEE25(void*,float,int,int,int);
 void rva000BFB51(float);void rva000C0386();
private:
 char pad10[8];AnimationStateBF9FC*m_18;
 char pad1C[0x48-0x1C];bool flag48;char pad49[0x68-0x49];
 void *begin68,*end6C,*cap70,*begin74,*end78,*cap7C;
 char pad80[0xB8-0x80];unsigned syncB8;
 char padBC[0x1C8-0xBC];bool flag1C8,flag1C9;
 char pad1CA[0x25C-0x1CA];bool flag25C;
 char pad25D[0x28C-0x25D];bool m_flag28C;
};

struct Rva000C144AEntry
{
	void *m_ptr00;
	char m_pad04[0x1C - 0x04];
};

struct Rva000C14BDTarget
{
	virtual void v00();
	virtual void v01();
	virtual const char *v02();
	virtual void *v03();
};

class Rva000B8F5A
{
public:
	AsciiString rva000C146D(int i);
	void rva000B8F5A(char *a, AsciiString b);
	void rva000BFD77();
	void rva000BFD9F();
	int rva000C144A();
	int rva000B82F9();
	int rva000B83A7();
	void *rva000C14BD(int i);

private:
	char m_pad00[0x0C];
	void *m_ptr0C;
	char m_pad10[0x94 - 0x10];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0x104 - 0xAC];
	Rva000C144AEntry m_entries104[3];
	char m_pad158[0x254 - 0x158];
	AsciiString m_name254;
	char m_pad258[0x280 - 0x258];
	bool m_flag280;
};

// ?rva000B8F5A@Rva000B8F5A@@QAEXPADVAsciiString@@@Z @0x000B8F5A 71B
void Rva000B8F5A::rva000B8F5A(char *a, AsciiString b)
{
	m_98 = a;
	m_94 = false;
	m_A8 = b;
}

// ?rva000BFB51@Rva000B8F5AOuter@@QAEXM@Z @0x000BFB51 37B
// Refill setter: when the +0x18 entry is live, clears the +0x28C flag first
// and refills through the outer 0xBEE25 body with (entry, value, 0, 1, 1).
void Rva000B8F5AOuter::rva000BFB51(float value)
{
	void *entry = m_18;
	if (entry != 0)
	{
		m_flag28C = false;
		rva000BEE25(entry, value, 0, 1, 1);
	}
}

// ?rva000BFD77@Rva000B8F5A@@QAEXXZ @0x000BFD77 40B
// Table-probe refill: looks the +0x0C entry up in the outer table; on a hit
// raises the +0x280 flag first and refills through the outer 0xBF9FC body.
void Rva000B8F5A::rva000BFD77()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4C9D(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000BFD9F@Rva000B8F5A@@QAEXXZ @0x000BFD9F 40B
// Twin of 0xBFD77 through the get-next sibling probe (0xB4CBE).
void Rva000B8F5A::rva000BFD9F()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4CBE(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000C144A@Rva000B8F5A@@QAEHXZ @0x000C144A 35B
// Leading-live counter: runs the outer 0xC0386 probe, then counts the
// leading non-null +0x104 entries (3 x 0x1C, testing the first pointer).
int Rva000B8F5A::rva000C144A()
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	unsigned n = 0;
	Rva000C144AEntry *e = m_entries104;
	do
	{
		if (e->m_ptr00 == 0)
			break;
		n++;
		e++;
	} while (n < 3);
	return n;
}

// ?rva000C14BD@Rva000B8F5A@@QAEPAXH@Z @0x000C14BD 56B
// Indexed entry fetch: runs the outer 0xC0386 probe, bounds-checks the
// index against the 3 x 0x1C +0x104 entries, and returns the entry target's
// slot-3 virtual (or null when out of range or empty).
void *Rva000B8F5A::rva000C14BD(int i)
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	if (i < 0 || (unsigned)i >= 3)
		return 0;
	Rva000C144AEntry *e = &m_entries104[i];
	// Volatile view: retail tests the slot in memory (cmp [eax],0) and
	// reloads it for the call instead of forwarding one load.
	Rva000C144AEntry volatile *ve = e;
	if (ve->m_ptr00 == 0)
		return 0;
	return ((Rva000C14BDTarget *)ve->m_ptr00)->v03();
}

// ?rva000C146D@Rva000B8F5A@@QAE?AVAsciiString@@H@Z @0x000C146D 80B
// Returns a string by value: runs the outer 0xC0386 probe; when the index hits
// a live +0x104 entry, builds it from the entry target's slot-2 text (0x37BA0),
// otherwise returns an empty string. The return-object flag at [ebp-4] is the
// by-value return; indexing the entry twice keeps retail's test-then-reload.
AsciiString Rva000B8F5A::rva000C146D(int i)
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	if (i >= 0 && (unsigned)i < 3)
	{
		if (m_entries104[i].m_ptr00 != 0)
			return AsciiString(((Rva000C14BDTarget *)m_entries104[i].m_ptr00)->v02());
	}
	return AsciiString();
}

// TargetB82F9 establishes secondary view(-C), outer slot49, state(-8)
// string10C and override254. Provider slot32 returns a counted handle;
// slot5 yields a32-bit result and only the zero result releases its handle.
// Original class and result semantic names remain unresolved.
class ProbeHandleB83A7 {
public:
    virtual void Delete_This();
    virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual int probe();
    int refs;
    void Release_Ref() { if(--refs==0) Delete_This(); }
};
class ProbeProviderB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual ProbeHandleB83A7 *find(const char *, bool);
};
class ProbeOuterB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual ProbeProviderB83A7 *get();
};
struct ProbeStateB83A7 {
    char unknown[0x10C];
    AsciiString name10C,name110;
};

// ?rva000B82F9@Rva000B8F5A@@QAEHXZ
int Rva000B8F5A::rva000B82F9()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        if(!reinterpret_cast<const StringBase<char> *>(&m_name254)->isEmpty()) name=m_name254;
        else name=(*reinterpret_cast<ProbeStateB83A7 **>((char *)this-8))->name10C;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}

// ?rva000B83A7@Rva000B8F5A@@QAEHXZ
// Retail B83A7..B8440 uses the same secondary receiver and probe slots as
// B82F9 but always selects state+110. Reassigning the typed address view
// preserves the native source pointer in ESI. The result role is unproven.
int Rva000B8F5A::rva000B83A7()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        const ProbeStateB83A7 *state = reinterpret_cast<const ProbeStateB83A7 *>(this);
        state = *reinterpret_cast<ProbeStateB83A7 *const *>((const char *)state - 8);
        name = state->name110;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}

extern int g_bfmeDisplayAnimationSyncClock;
class Rva000BC9B1 {public:void rva000BC9B1(bool);};
class Rva000B2EB5 {public:float rva000B2EB5();};
class Rva000B9A0E {public:void rva000B9A0E(void*,int,int);};
// Full nativeBF9FC..BFB51 RET12: WB931DE0 animation-state transition.
// Reference W3DModelDraw state/animation sequence is semantic context only;
// target owns added state callbacks, effects, tick synchronization and vectors.
bool Rva000B8F5AOuter::rva000BF9FC(void*entry,bool force,int options){
 AnimationStateBF9FC*next=(AnimationStateBF9FC*)entry;
 if(m_18==next){
  if(m_18 && m_18->repeat9C && force)m_18=next;
  else if(force)refresh();else return false;
 }
 unsigned now=(unsigned)g_bfmeDisplayAnimationSyncClock;
 if(now>syncB8)flag25C=false;
 syncB8=now;
 if(!(drawable->flags114&8))flag48=true;
 ((Rva000BC9B1*)this)->rva000BC9B1(true);
 AnimationStateBF9FC*previous=m_18;
 float fraction=((Rva000B2EB5*)this)->rva000B2EB5();
 m_18=next;
 rva000BEE25(previous,fraction,0,0,options);
 if(previous!=m_18){
  if(previous)((Rva000B9A0E*)previous)->rva000B9A0E(drawable->object,2,0);
  if(m_18)((Rva000B9A0E*)m_18)->rva000B9A0E(drawable->object,1,0);
 }
 if(m_18!=next)return true;
 if(next && next->fx68){
  Drawable*draw=drawable;
  if(draw->object)FXList::doFXObj(next->fx68,draw->object,0);
  else FXList::doFXPos(next->fx68,draw->getPosition(),draw->getTransformMatrix(),0.0f,0);
 }
 if((begin74!=end78 && flag1C9)||(begin68!=end6C && flag1C8))refresh();
 return true;
}
