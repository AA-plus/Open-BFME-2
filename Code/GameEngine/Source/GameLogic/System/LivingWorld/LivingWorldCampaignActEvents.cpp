// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// Recovered together from banked attempts 565148 / 5651D2 / 565261.
// Retail loops read the act's STLport vector headers at +78 / +6C / +84,
// allocate a 16-byte event, call the existing 3FD3C7 / 3FD498 / 3FD348
// constructor, then pass it to the existing 2B8AC0 appender.
// The neighboring recovered LivingWorldCampaignAct methods establish the act;
// event names remain the established address-derived names. The record
// members are storage views constrained by these constructor arguments.
// The text records are 20 bytes: string at +0C and flag at +10. The other
// records are 16 bytes, with their handle / value and flag offsets as below.
// The 5651D2 WorldBuilder twin at 143AA20 corroborates the text record layout.
#include "ascii_string.h"
// stlport
#include <vector>

class ModuleData;
class Rva002B8AC0 { public: void rva002B8AC0(const ModuleData *); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	void *m_ref;
};

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned, char);
	virtual ~BfmeBaseVNH();
	virtual void handle();
	unsigned value04;
	char flag08;
};

class BfmeRectVNH : public BfmeBaseVNH
{
public:
	BfmeRectVNH(unsigned, const AsciiString &, char);
	AsciiString text0C;
};

class Rva003FD3EF : public BfmeBaseVNH
{
public:
	Rva003FD3EF(unsigned, const Rva0036CA00Str &, char);
	virtual ~Rva003FD3EF();
	Rva0036CA00Str m_0c;
};

class Rva003FD348 : public BfmeBaseVNH
{
public:
	Rva003FD348(unsigned, unsigned, char);
	virtual ~Rva003FD348();
	unsigned m_0c;
};

struct StrRecord16
{
    int m_00;
    unsigned m_value04;
    Rva0036CA00Str m_s;
    char m_f;

    const Rva0036CA00Str &str() const { return m_s; }
    unsigned value04() const { return m_value04; }
    char flag() const { return m_f; }
};
struct ValueRecord16
{
    int m_00;
    unsigned m_value04;
    char m_f;
    unsigned m_value0C;

    unsigned value0C() const { return m_value0C; }
    unsigned value04() const { return m_value04; }
    char flag() const { return m_f; }
};
struct TextRecord20
{
    int m_00;
    unsigned m_value04;
    int m_08;
    AsciiString m_s;
    char m_f;

    const AsciiString &str() const { return m_s; }
    unsigned value04() const { return m_value04; }
    char flag() const { return m_f; }
};

typedef char StrRecord16Size[(sizeof(StrRecord16) == 16) ? 1 : -1];
typedef char ValueRecord16Size[(sizeof(ValueRecord16) == 16) ? 1 : -1];
typedef char TextRecord20Size[(sizeof(TextRecord20) == 20) ? 1 : -1];

class LivingWorldCampaignAct
{
public:
	void rva00565148();
	void rva005651D2();
	void rva00565261();
private:
	unsigned textCount() const { return m_text.size(); }
	unsigned strCount() const { return m_str.size(); }
	unsigned scaleCount() const { return m_scale.size(); }

	char m_pad00[0x6C];
	_STL::vector<TextRecord20> m_text;
	_STL::vector<StrRecord16> m_str;
	_STL::vector<ValueRecord16> m_scale;
};

void LivingWorldCampaignAct::rva00565148()
{
	for (unsigned i = 0; i < strCount(); ++i) {
		StrRecord16 &r = m_str[i];
		Rva003FD3EF *event = new Rva003FD3EF(r.value04(), r.str(), r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}

void LivingWorldCampaignAct::rva005651D2()
{
	for (unsigned i = 0; i < textCount(); ++i) {
		TextRecord20 &r = m_text[i];
		BfmeRectVNH *event = new BfmeRectVNH(r.value04(), r.str(), r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}

void LivingWorldCampaignAct::rva00565261()
{
	for (unsigned i = 0; i < scaleCount(); ++i) {
		ValueRecord16 &r = m_scale[i];
		Rva003FD348 *event = new Rva003FD348(r.value04(), r.value0C(), r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}

// Complete native565344..565436/242B and WB143AC80/440B establish the
// act's point32 and tree24 record transfers at54/60. The existing neutral
// Glo012F1024Item name is retained from its verified run caller; no original
// method spelling or mapped-value identity is asserted. Actual rowed event
// constructors and independently verified receiver borrower/tree assignment
// own every call. BF1's clean int/unsigned tree donor did not place and is
// not substituted for this retail provider. Inline field accessors preserve
// native constructor evaluation and char argument-home scheduling.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Rva005045DBTree {
public:Rva005045DBTree&assign(const Rva005045DBTree&);Rva005045DBTree&self();
int storage[3];
};
class Rva003FD2C2:public BfmeBaseVNH {
public:Rva003FD2C2(unsigned,const Coord3D*,float,unsigned,char);
Coord3D point0C;float angle18;unsigned scaled1C;
};
class BfmeBaseVNI {
public:BfmeBaseVNI(unsigned,char);virtual~BfmeBaseVNI();virtual void handle();
unsigned value04;char flag08;
};
class BfmeRectVNI:public BfmeBaseVNI {
public:BfmeRectVNI(unsigned,char);Rva005045DBTree tree0C;int at18;
};
struct ClonePointRecord32 {
int at00;unsigned value04;Coord3D point08;float angle14;unsigned scaled18;char flag1C;
unsigned value()const{return value04;}const Coord3D*point()const{return &point08;}
float angle()const{return angle14;}unsigned scaled()const{return scaled18;}char flag()const{return flag1C;}
};
struct CloneTreeRecord24 {
int at00;unsigned value04;char flag08;Rva005045DBTree tree0C; unsigned value()const{return value04;}char flag()const{return flag08;}
};
class Glo012F1024Item {
public:void j_0002a969();
private:char pad00[0x54];_STL::vector<ClonePointRecord32>points54;_STL::vector<CloneTreeRecord24>trees60;
};
void Glo012F1024Item::j_0002a969(){
for(unsigned i=0;i<points54.size();++i){
 ClonePointRecord32&r=points54[i];
 Rva003FD2C2*event=new Rva003FD2C2(r.value(),r.point(),r.angle(),r.scaled(),r.flag());
 ((Rva002B8AC0*)TheLivingWorldLogic)->rva002B8AC0((const ModuleData*)event);
}
for(CloneTreeRecord24*r=trees60.begin();r!=trees60.end();++r){
 BfmeRectVNI*event=new BfmeRectVNI(r->value(),r->flag());
 event->tree0C.assign(r->tree0C.self());
 ((Rva002B8AC0*)TheLivingWorldLogic)->rva002B8AC0((const ModuleData*)event);
}
}
