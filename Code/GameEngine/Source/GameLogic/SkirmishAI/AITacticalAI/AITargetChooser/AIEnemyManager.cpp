// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Full native5A9824..5A990B and WorldBuilder1525700 establish AIEnemyManager::update.
// Native source-path literal names this file; matched PlayerList, POD erase,
// sort and random providers corroborate the WorldBuilder control flow.
// Owner0, vector4, eight-byte (player index, float priority) records and selected
// index14 are native facts. Counter10 remains neutral. BfmeE8/BfmePod8 are
// existing library stand-ins: erase touches only POD storage; sort uses float4.
// Priority350B remains unrowed. Its target-proven float/thiscall/RET4 binding
// retains the neutral bank name; the unresolved Coord3D return view is not imported.
// ThePlayerList uses the sole converged global spelling. No private Player layout.
#include <vector>
#include <algorithm>
struct BfmeE8 { int a; float b; };
struct BfmePod8 { int a[2]; };
namespace _STL {
 template<> BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *);
 template<> void sort<BfmeE8 *>(BfmeE8 *,BfmeE8 *);
}
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Player;
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class Rva002AA22AByteField { public: unsigned char get()const; };
struct AIEnemyPlayerPrefix { char unknown00[0x54]; int index; };
int GetGameLogicRandomValue(int,int,char *,int);
class Rva005A9562 { public: float rva005A92DE(void *); };
class AIEnemyManager {
 void *owner;
 _STL::vector<BfmeE8> enemies;
 unsigned counter;
 int chosen;
public:
 void update();
 void DoXfer(Xfer *);
};
void AIEnemyManager::update()
{
 bool choose=chosen==-1;
 for(BfmeE8 *item=enemies.begin();item!=enemies.end();) {
  Player *player=ThePlayerList->getNthPlayer(item->a);
  if(!player || ((Rva002AA22AByteField *)player)->get()) {
   if(((AIEnemyPlayerPrefix *)player)->index==chosen)choose=true;
   item=reinterpret_cast<BfmeE8 *>(reinterpret_cast<_STL::vector<BfmePod8> *>(&enemies)->erase(reinterpret_cast<BfmePod8 *>(item)));
  }else ++item;
 }
 if(enemies.empty()) { chosen=-1; return; }
 if(!choose)return;
 for(BfmeE8 *item=enemies.begin();item!=enemies.end();++item)
  item->b=((Rva005A9562 *)this)->rva005A92DE(ThePlayerList->getNthPlayer(item->a));
 _STL::sort<BfmeE8 *>(enemies.begin(),enemies.end());
 if(enemies.size()>=2 &&
    GetGameLogicRandomValue(1,100,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AIEnemyManager.cpp",122)<=50 &&
    !(enemies[1].b-enemies[0].b>1000.0f))
  chosen=enemies[1].a;
 else chosen=enemies[0].a;
}

// Native87B and full WB1526F20 identify this transfer as AIEnemyManager::DoXfer.
// Native persists the entry count, counter10 and chosen14; WB also checks the count.
void AIEnemyManager::DoXfer(Xfer *xfer)
{
 Xfer::Version version(1, 2);
 *xfer == version;
 unsigned count = (unsigned)(enemies.end() - enemies.begin());
 *xfer == count;
 *xfer == counter;
 if(version.m_minimum >= 2) *xfer == chosen;
}
