// ?rva003F7260@Rva003F7260@@QAEXPAH@Z
// partial score=0.8183094098883572 date=2026-10-12
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "string_base.h"
#include <vector>
class Rva0020E89C;
class Rva002E2903Player;
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret *rva00318C32();};
class Rva002BA8F1Logic {public:Rva002E2903Player *find(int,unsigned *);Rva002E2903Player *rva002B52A8(int);};
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct RegionCostRecord {int region;char unmodelled04[0x20];float cost;int getRegion()const{return region;}};
struct RegionOwnerView {char unmodelled00[0x13c];int owner;};
struct RegionAnchorView {char unmodelled00[0x18];StringBase<char> name;char unmodelled1c[0x58];unsigned char flag74;};
struct WorldPlayerRegionView {char unmodelled00[0x1b8];_STL::vector<RegionAnchorView *> anchors;};
struct WorldLogicRegionView {char unmodelled00[0x8c];_STL::vector<Rva002E2903Player *> players;char unmodelled98[0x18];Rva0020EAF6View *regions;Rva0020EAF6View *getRegions()const{return regions;}};
class Rva003F7260 {
public:
 void rva003F7260(int *input);
 void *unknown00;int owner04;
 float otherNamed08,otherAny0c,ownNamed10,ownAny14,otherRegion18;
 RegionAnchorView *selected1c,*otherAny20,*ownNamed24;
 Rva0020E89C *neutral28;float neutral2c;Rva0020E89C *owned30;float owned34;
};
void Rva003F7260::rva003F7260(int *input)
{
 RegionCostRecord *cost=(RegionCostRecord *)input;
 Rva0020E89C *region=((WorldLogicRegionView *)TheLivingWorldLogic)->getRegions()->rva0020EAF6(cost->getRegion());
 Rva002E2903Player *owner=((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(owner04,0);
 if(((RegionOwnerView *)region)->owner!=owner04) {
  if(otherRegion18>cost->cost)otherRegion18=cost->cost;
  if(((RegionOwnerView *)region)->owner==-1 && neutral2c>cost->cost) {neutral28=region;neutral2c=cost->cost;}
  else if(((RegionOwnerView *)region)->owner!=-1 && owned34>cost->cost) {owned30=region;owned34=cost->cost;}
 }
 for(int p=0;p<(int)((WorldLogicRegionView *)TheLivingWorldLogic)->players.size();++p) {
  Rva002E2903Player *player=((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(p);
  WorldPlayerRegionView *view=(WorldPlayerRegionView *)player;
  for(unsigned a=0;a<view->anchors.size();++a) {
   if(((Rva00318C79Owner *)view->anchors[a])->rva00318C32()==(Rva00318C32Ret *)region) {
    RegionAnchorView *anchor=view->anchors[a];
    if(!anchor->name.isEmpty()) {
     if(player==owner) {
      if(ownNamed10>cost->cost) {ownNamed10=cost->cost;ownNamed24=view->anchors[a];if(ownAny14>cost->cost)ownAny14=cost->cost;}
     } else {
      if(otherNamed08>cost->cost) {otherNamed08=cost->cost;if(otherAny0c>cost->cost) {otherAny0c=cost->cost;otherAny20=view->anchors[a];selected1c=view->anchors[a];}}
     }
    } else if(!anchor->flag74 && player==owner) {
     if(ownAny14>cost->cost) {ownAny14=cost->cost;selected1c=view->anchors[a];}
    }
   }
  }
 }
}
