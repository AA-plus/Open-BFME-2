// ?rva0042CC7B@Rva0042CBB6@@QAEHPAVGameMessage@@@Z
// partial score=0.739303 date=2026-10-11
// cl: /O1 /Oi /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I.
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

class GameMessage;
class Rva0042CBB6
{
public:
	void rva0042CB81(int x);
	void rva0042CC1B();
	void rva0042CAEB(int y);
	void rva0042CB57(int x);
	void rva0042CAFB();
	int rva0042CC7B(GameMessage *);
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

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class Display; extern Display *TheDisplay;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Shell; extern Shell *TheShell;
class Rva0023C748 { public: char rva0023C748(); };
class Rva002B34E5 { public: void rva002B34E5(bool); };
class Rva0004224C {
 int reserved;
public:
 Rva0004224C *rva0004224C();
 Rva0004224C();
 __forceinline ~Rva0004224C() { if(TheGameLogic) --*reinterpret_cast<int *>(reinterpret_cast<char *>(TheGameLogic)+0x1B4); }
};
union GameMessageArgumentType {
 int integer; float real; int boolean; int objectID; int drawableID;
 unsigned teamID; struct Loc { float x,y,z; } location;
 struct Pix { int x,y; } pixel;
 struct PixReg { int loX,loY,hiX,hiY; } pixelRegion;
 unsigned timestamp; unsigned short wChar;
};
class GameMessage {
public:
 char pad[0x10]; int type;
 const GameMessageArgumentType *getArgument(int) const;
};
class MessageForward42 { public: virtual int translate(GameMessage *); };
class DisplayOperations42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual unsigned width(); virtual unsigned height();
};
class MessageUI42 {
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
 virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
 virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(); virtual void s22();
 virtual void s23(int,GameMessageArgumentType::Pix *);
};
int Rva0042CBB6::rva0042CC7B(GameMessage *message)
{
 if(m_04) {
  int forwarded=reinterpret_cast<MessageForward42 *>(m_04)->translate(message);
  if(forwarded==1) return forwarded;
 }
 int disposition=0;
 if(reinterpret_cast<Rva0023C748 *>(TheGameLogic)->rva0023C748()) return 0;
 Rva0004224C scope;
 if(!g_00DFEF18) return 0;
 int type=message->type;
 if(!*(reinterpret_cast<unsigned char *>(g_00DFEF18)+0x18) || TheGameLogic->isGamePaused()) return 0;
 switch(type) {
 case 14:
  if(g_00DFEF18 && !*(reinterpret_cast<unsigned char *>(TheLivingWorldManager)+0x2C0)) {
   const GameMessageArgumentType *arg=message->getArgument(0);
   m_10=arg->pixel.x; m_14=arg->pixel.y;
   arg=message->getArgument(0); m_18=arg->pixel.x; m_1C=arg->pixel.y;
   if(TheMouse->m_4FA4) { rva0042CB57(1); m_30=0; m_34=0; }
  }
  disposition=1; break;
 case 12: rva0042CB81(2); disposition=1; break;
 case 11: rva0042CAFB(); break;
 case 10:
  if(!*(reinterpret_cast<unsigned char *>(TheLivingWorldManager)+0x2C0)) {
   const GameMessageArgumentType *arg=message->getArgument(0);
   m_20=arg->pixel.x; m_24=arg->pixel.y;
   arg=message->getArgument(0); m_28=arg->pixel.x; m_2C=arg->pixel.y;
   if(TheMouse->m_4FA4) rva0042CB57(2);
  }
  disposition=1; break;
 case 3:
  if(!*(reinterpret_cast<unsigned char *>(g_00DFEF18)+0x18)) { rva0042CB81(0); break; }
  m_42=1;
  {
   const GameMessageArgumentType *arg=message->getArgument(0);
   m_18=arg->pixel.x; m_1C=arg->pixel.y;
   arg=message->getArgument(0); m_28=arg->pixel.x; m_2C=arg->pixel.y;
   unsigned height=reinterpret_cast<DisplayOperations42 *>(TheDisplay)->height();
   unsigned width=reinterpret_cast<DisplayOperations42 *>(TheDisplay)->width();
   if(!*(reinterpret_cast<unsigned char *>(TheWritableGlobalData)+0x2C)) {
    if(m_08 & 8) {
     if(m_08==8 && m_18>=3 && m_1C>=3 && (unsigned)m_1C<height-3 && (unsigned)m_18<width-3) rva0042CB81(8);
    } else if(!*(reinterpret_cast<unsigned char *>(TheLivingWorldManager)+0x2C0)) {
     if(m_18<3 || m_1C<3 || (unsigned)m_1C>=height-3 || (unsigned)m_18>=width-3) rva0042CB57(8);
    }
   }
  }
  disposition=1; break;
 case 16:
  {
   int limit=*reinterpret_cast<int *>(reinterpret_cast<char *>(TheLivingWorldManager)+0x1E0);
   m_38=m_30<limit && m_34<limit;
   rva0042CB81(1); disposition=1;
  } break;
 case 19:
  if(!reinterpret_cast<Rva002BE8D4 *>(g_00DFEF18)->rva002BE8D4()) {
   GameMessageArgumentType::Pix point=message->getArgument(0)->pixel;
   int value=message->getArgument(1)->integer;
   reinterpret_cast<MessageUI42 *>(g_00DFEF18)->s23(value,&point);
   disposition=1;
  } break;
 case 153:
  reinterpret_cast<Rva002B34E5 *>(TheLivingWorldLogic)->rva002B34E5(!*(reinterpret_cast<unsigned char *>(TheLivingWorldLogic)+0x10B));
  break;
 case 23: case 1104: disposition=1; break;
 case 21: case 22:
  {
   unsigned char key=(unsigned char)message->getArgument(0)->integer;
   unsigned char down=(unsigned char)(~message->getArgument(1)->integer)&1;
   if(TheShell && *(reinterpret_cast<unsigned char *>(TheShell)+0x5C)) break;
   switch(key) {
    case 72:m_40=down;break; case 75:m_3E=down;break;
    case 76:rva0042CAFB();break; case 77:m_3F=down;break;
    case 80:m_41=down;break; case 200:m_3A[0]=down;break;
    case 203:m_3A[2]=down;break; case 205:m_3A[3]=down;break;
    case 208:m_3A[1]=down;break;
   }
   int pressed=0;
   for(int i=0;i<4;++i) if(m_3A[i]) ++pressed;
   if(pressed) rva0042CB57(4); else rva0042CB81(4);
   disposition=1;
  } break;
 }
 return disposition;
}
