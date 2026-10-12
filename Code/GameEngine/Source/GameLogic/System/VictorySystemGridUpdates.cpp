// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>
// BFME1 semantic source: VictorySystemApplyCells.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Target independently fixes
// root cell +78, twenty player slots, grids12C/130 and values at grid+18.
// Native callbacks 4050CE..4051BC and 405258..405315 use rowed Object,
// root-cell and CellGrid providers. Original method names remain unknown.
class Object;
class Player { public: char pad[0x54]; int index; };
struct VictoryObjectTemplate { char pad[0x109]; unsigned char flags109; char pad10a[9]; unsigned char flags113; };
class Object { public: Player *getControllingPlayer() const; char pad0[4]; VictoryObjectTemplate *tmpl; char pad8[0x438-8]; unsigned char flags438; };

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct VictoryDeathInfo { char pad[8]; ObjectID killer; };
struct Vec3 { float x,y,z; };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Rva00404781 { public: void rva00404781(float,int,int); int rva00404CF5(bool); float a[20],b[20]; unsigned int masks[2]; };
class Rva0056C4D3 { public: void rva0056C4D3(void*,float,int,int); };
class Rva0056C0F0 { public: void rva0056C0F0(unsigned int,Vec3*); };
class Rva004051BC { public: void rva004051BC(int,const Coord3D*); };
class CellGrid { public: int rva0056C16D(); unsigned width,height,count; float size,offset; Rva00404781 *cells; unsigned int *values; };
class Rva00404927
{
public:
	int rva00404927(Rva00404781 *, int);
private:
	char data[24];
};
// The 24-byte parameter record is established by the existing 404927 consumer
// and the native faction parameter table. Its application class name is unknown.
class Rva00404C26
{
public:
	Rva00404927 *rva00404C26(int player);
private:
	char unknown00[0x28];
	unsigned playerParameters[62];
	_STL::vector<Rva00404927> parameters;
};

Rva00404927 *Rva00404C26::rva00404C26(int player)
{
	unsigned index = playerParameters[player] & 0x7fffffff;
	if (index < parameters.size())
	 return &parameters[index];
	return 0;
}

class Rva0056C3EA { public: void rva0056C3EA(int,void*); };
struct VictoryGridParameter { float fields[5]; float weight; };
class VictorySystemGridUpdateView {
public: void rva004050CE(Object*,const VictoryDeathInfo*); void rva00405258(); void rva00405094();
private:
 char pad0[0x28]; int playerIndices[20]; Rva00404781 root;
 VictoryGridParameter *parameters,*parametersEnd,*parametersCapacity;
 CellGrid *grids[2];
 bool initialized; char pad135[3]; unsigned int activeGrid; int currentPlayer;
};
void VictorySystemGridUpdateView::rva004050CE(Object *victim,const VictoryDeathInfo *info) {
 if (!victim || !info || (victim->flags438 & 8)) return;
 Player *victimPlayer;
 Object *killer=TheGameLogic->findObjectByID(info->killer);
 if (!killer) return;
 victimPlayer=victim->getControllingPlayer();
 Player *killerPlayer=killer->getControllingPlayer();
 if (!victimPlayer || !killerPlayer) return;
 int victimIndex=victimPlayer->index;
 int parameterIndex=playerIndices[victimIndex];
 if ((unsigned)parameterIndex & 0x80000000) return;
 VictoryGridParameter *parameter=&parameters[parameterIndex];
 float weight;
 if ((victim->tmpl->flags109 & 4) || (victim->tmpl->flags113 & 4)) weight=parameter->weight;
 else weight=1.0f;
 root.rva00404781(weight,victimIndex,killerPlayer->index);
 for (unsigned i=0;i<2;++i) {
  if (grids[i]) ((Rva0056C4D3*)grids[i])->rva0056C4D3(victim,weight,victimPlayer->index,killerPlayer->index);
 }
}

// Native405094..4050CE RET0. BFME1 VictorySystemUpdate.cpp is the semantic
// source. Visible byte-verified parameter lookup preserves its readonly call
// contract, the shared case tail and native EDI grid / ESI player allocation.
void VictorySystemGridUpdateView::rva00405094()
{
 switch (activeGrid) {
 case 0:
  if (!grids[0]) return;
  ((Rva0056C3EA *)grids[0])->rva0056C3EA(
   currentPlayer, ((Rva00404C26 *)this)->rva00404C26(currentPlayer));
  break;
 case 1:
  if (!grids[1]) return;
  ((Rva0056C3EA *)grids[1])->rva0056C3EA(
   currentPlayer, ((Rva00404C26 *)this)->rva00404C26(currentPlayer));
  break;
 }
}
