// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
// cl: /Ireference/shims/bfmealloc /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// BFME1 cee35b7d8 FXListStoreParse.cpp and ZH FXList.cpp identify the parser.
// Native1E2CAE..1E2DB3 independently proves the pointer map at0C and override
// vector20 plus the 40-byte named record and full 19-entry field table7DC720.
// The retail override branch reads the saved node after the erase call; keep
// that order rather than replacing it with the BFME1 value-map clear path.
// Native constructor1E2747 owns the record class; its original spelling is
// uncertain. No payload-type claim is made by the pointer-vector ABI view.
#include <hash_map>
#include <vector>
#include "ascii_string.h"
struct FieldParse;class INI;
struct FieldParse {const char*name;void(*parse)(INI*,void*,void*,const void*);const void*data;int offset;};
class INI {public:const char*getNextToken(const char*);void initFromINI(void*,const FieldParse*);static void parseBool(INI*,void*,void*,const void*);char opaque00[8];int loadType;};
enum NameKeyType{NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
namespace rts {template<class T>struct hash {size_t operator()(const T&x)const{return (size_t)x;}};}
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
class FXList {public:static void parseCullingInfo(INI*,void*,void*,const void*);};
class Rva001E2747:public FXList {public:Rva001E2747(const AsciiString&);virtual ~Rva001E2747();char opaque04[0x20];bool override24;};
class SoundFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class EvaEventFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class RayEffectFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class LightPulseFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class CameraShakerVolumeFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class ViewShakeFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class AttachedModelFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class TerrainScorchFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class ParticleSystemFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class FXListAtBonePosFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class CursorParticleSystemFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class DynamicDecalFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class LaserFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class TintDrawableFXNugget{public:static void parse(INI*,void*,void*,const void*);};
class BuffNuggetFXNugget{public:static void parse(INI*,void*,void*,const void*);};
void Rva001E1890Parse(INI*,void*,void*,const void*);
// Canonical table owner, following BFME1's extern FieldParse declaration.
extern const FieldParse TheFXListFieldParse[]={
{"Sound",SoundFXNugget::parse,0,0},
{"EvaEvent",EvaEventFXNugget::parse,0,0},
{"RayEffect",RayEffectFXNugget::parse,0,0},
{"LightPulse",LightPulseFXNugget::parse,0,0},
{"CameraShakerVolume",CameraShakerVolumeFXNugget::parse,0,0},
{"ViewShake",ViewShakeFXNugget::parse,0,0},
{"AttachedModel",AttachedModelFXNugget::parse,0,0},
{"TerrainScorch",TerrainScorchFXNugget::parse,0,0},
{"ParticleSystem",ParticleSystemFXNugget::parse,0,0},
{"ParticleSysBone",Rva001E1890Parse,0,0},
{"FXListAtBonePos",FXListAtBonePosFXNugget::parse,0,0},
{"CursorParticleSystem",CursorParticleSystemFXNugget::parse,0,0},
{"DynamicDecal",DynamicDecalFXNugget::parse,0,0},
{"Laser",LaserFXNugget::parse,0,0},
{"CullingInfo",FXList::parseCullingInfo,0,0},
{"TintDrawable",TintDrawableFXNugget::parse,0,0},
{"BuffNugget",BuffNuggetFXNugget::parse,0,0},
{"PlayEvenIfShrouded",INI::parseBool,0,0x10},
{0,0,0,0}};
class ModuleData;
typedef _STL::hash_map<NameKeyType,Rva001E2747*,rts::hash<NameKeyType>,_STL::equal_to<NameKeyType> > FXListMap;
class FXListStore{public:static void parseFXListDefinition(INI*);char opaque00[0xc];FXListMap fxmap;_STL::vector<Rva001E2747*> overrides;};extern FXListStore*TheFXListStore;
void FXListStore::parseFXListDefinition(INI*ini){
 const char*c=ini->getNextToken(0);
 NameKeyType key=TheNameKeyGenerator->nameToKey(c);
 FXListMap::iterator it=TheFXListStore->fxmap.find(key);
 if(it!=TheFXListStore->fxmap.end()&&ini->loadType==5){
  TheFXListStore->fxmap.erase(it);
  Rva001E2747*old=it->second;
  // Retail uses the existing four-byte pointer-vector provider. It accesses
  // only pointer storage; the stored object remains the target FX-list record.
  if(old){old->override24=true;((_STL::vector<const ModuleData*>*)&TheFXListStore->overrides)->push_back(*(const ModuleData**)&old);}
 }
 Rva001E2747*fxl=new Rva001E2747(c);
 TheFXListStore->fxmap[key]=fxl;
 ini->initFromINI(fxl,TheFXListFieldParse);
}
