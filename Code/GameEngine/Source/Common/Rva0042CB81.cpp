// cl: /O1 /Oi /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <algorithm>
// ?rva0042CB81@Rva0042CBB6@@QAEXH@Z @0x0042CB81 53B via conditional counter decrement plus zero-guard clear
// Evidence: layout matches Rva0042CBB6Ctor (+8 +0x30 +0x34 +0x39); callers 5 incl 0x0042CE09 0x0042D0CD; unblocks 0x0042D068
class Mouse
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17(); virtual void m18();
	virtual void m19(int x);
	char m_pad[0x4FA0];
	int m_4FA4;
};
extern Mouse *TheMouse;

class Rva0042CBB6
{
public:
	void rva0042CB81(int x);
	void rva0042CC1B();
	void rva0042CAEB(int y);
	void rva0042CB57(int x);
	void rva002B230F(int impl);
	void rva0042CAFB();
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	char m_3A[4];
	unsigned char m_3E;
	unsigned char m_3F;
	unsigned char m_40;
	unsigned char m_41;
	unsigned char m_42;
};

// The complete 10-byte body at 002B230F is folded with the rowed listener
// setters. Native 42C693 passes its new impl and the same +20 owner whose
// conditional clear42CAEB tests the +4 slot below; this establishes the
// receiver and storage relationship without claiming an original method name.
void Rva0042CBB6::rva002B230F(int impl)
{
	m_04 = impl;
}

void Rva0042CBB6::rva0042CAEB(int y)
{
	if (m_04 == y)
		m_04 = 0;
}

void Rva0042CBB6::rva0042CB81(int x)
{
	if (x == 0)
		m_08 = 0;
	else {
		int cur = m_08;
		if ((x & cur) != 0)
			m_08 = cur - x;
	}
	if (m_08 < 0)
		m_08 = 0;
	if (m_08 == 0) {
		m_39 = 0;
		m_30 = 0;
		m_34 = 0;
	}
}

// ?rva0042CB57@Rva0042CBB6@@QAEXH@Z @0x0042CB57 42B via TheMouse+0x4FA4 fill plus bit-gated add
// Evidence: same class layout as neighbours (+8 +0x0C +0x39); TheMouse at 0x009FDCA0 field +0x4FA4 per Rva0042C7B1; callers 0x0042CD88 0x0042CEC4
void Rva0042CBB6::rva0042CB57(int x)
{
	int cur = m_08;
	if (cur == 0)
		m_0C = TheMouse->m_4FA4;
	if ((x & cur) == 0)
		m_08 = cur + x;
	m_39 = 1;
}

// Native Ghidra extent 0x0042CC1B..0x0042CC7B, 96 bytes, thiscall RET0.
// The consumed offsets and reset constants agree with the rowed constructor
// at 0x0042CBB6; original class and field meanings remain unknown.
// STLport 4.5.3's generic fill with a bool value retains the runtime pointer
// span for +0x3A..+0x3D. Its char overload folds that span into a constant
// memset and does not reproduce the retail comparison and REP stores.
void Rva0042CBB6::rva0042CC1B()
{
	m_08 = 0;
	m_0C = 2;
	m_14 = 0;
	m_10 = 0;
	m_1C = 0;
	m_18 = 0;
	m_24 = 0;
	m_20 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 1;
	m_39 = 0;
	m_3E = 0;
	m_3F = 0;
	m_40 = 0;
	m_41 = 0;
	m_42 = 0;
	_STL::fill(m_3A, m_3A + 4, false);
}

// Reuse the data ledger owner at 0x009FEF18; original class identity is unknown.
class Rva002D3627Host; extern Rva002D3627Host *g_00DFEF18;
extern int g_009BA4E8;
class Rva002BE8D4 { public: bool rva002BE8D4(); };
struct CameraPoint42 { float x,y,z; };
class CameraOperations42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
 virtual void s24(); virtual float s25(int);
 virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(CameraPoint42 *);
 virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
 virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
 virtual void s38(); virtual void s39(CameraPoint42 *,float,float);
};

// Complete native 82CAFB..82CB57, 92B; WB12C1010 saves ECX as this.
// Two calls from the receiver's 1005B handler at 42CC7B and its layout
// siblings establish the owner. Original method and virtual slot names
// remain unknown. Native slots 0x74, 0x64, 0x9C respectively fill a
// three-float point, return a float for FPS/4 and accept that point plus
// zero and the returned float. Camera roles are structural inferences.
// Keep the height query nested: its vtable stays in ESI across both calls.
void Rva0042CBB6::rva0042CAFB()
{
 if(!reinterpret_cast<Rva002BE8D4 *>(g_00DFEF18)->rva002BE8D4()) {
  CameraPoint42 point;
  reinterpret_cast<CameraOperations42 *>(g_00DFEF18)->s29(&point);
  reinterpret_cast<CameraOperations42 *>(g_00DFEF18)->s39(
   &point,0.0f,reinterpret_cast<CameraOperations42 *>(g_00DFEF18)->s25(g_009BA4E8 / 4));
 }
}
