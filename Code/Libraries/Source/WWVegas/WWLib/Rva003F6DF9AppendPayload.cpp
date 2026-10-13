// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Dedicated TU: NestedRecordLookupRva003F6D35.cpp carries the matched
// 0x3F6D35 row under its own /EHsc /MD flags; this body needs /O1 /G7.
// R1 template visibility: dropping the three explicit vector/find
// specialization declarations restores retail's base-load order. Exact 168B.
#include <vector>
#include <algorithm>
class ModuleData;
class CreateAHeroData;
struct BfmePod104 { int data[26]; };
namespace _STL {



}
struct Rva003F6DF9Child {char pad98[0x98];unsigned field98;char pad9c[0xc];bool flaga8;};
struct Rva003F6DF9Entry {unsigned word;Rva003F6DF9Child *child;};
struct Rva003F6DF9Data {char pad2c[0x2c];unsigned dirty;char pad30[0x10];_STL::vector<Rva003F6DF9Entry> entries;char pad4c[0x1c];};
struct Rva002BA8F1Listener {char opaque[4];};
struct Rva003F6DF9OwnerBase {virtual void interface0()=0;};
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);private:void*words[3];};
struct Rva003F6DF9Payload {char pad8[8];Rva005A0B4CList listeners;char pad14[0x64];Rva003F6DF9Data *data;};
class Rva0040CB2CIndexedField {public:int get(int)const;};
struct Rva003F6D35Inner {
 unsigned word;_STL::vector<const ModuleData*> payloads;_STL::vector<BfmePod104> data;unsigned tail[5];
};
class Rva003F6D35Owner:public Rva003F6DF9OwnerBase,public Rva002BA8F1Listener {public:
 Rva003F6D35Inner *findOrCreateRva003F6D35(void*);
 void appendPayloadRva003F6DF9(void*,Rva003F6DF9Payload*);
};
void Rva003F6D35Owner::appendPayloadRva003F6DF9(void *input,Rva003F6DF9Payload *payload){
 Rva003F6D35Inner *inner=findOrCreateRva003F6D35(input);
 Rva003F6DF9Data *data=payload->data;
 if(data)data->dirty=0;
 input=payload; CreateAHeroData *&search=(CreateAHeroData*&)input;
 if(_STL::find((CreateAHeroData**)inner->payloads.begin(),(CreateAHeroData**)inner->payloads.end(),search)==(CreateAHeroData**)inner->payloads.end()){
  input=payload; const ModuleData *&entry=(const ModuleData*&)input;
  inner->payloads.push_back(entry);
  inner->data.push_back(*(BfmePod104*)data);
  if(data){
   int count=data->entries.size();
   for(int i=0;i<count;++i){
    Rva003F6DF9Child *child=(Rva003F6DF9Child*)((Rva0040CB2CIndexedField*)data)->get(i);
    child->field98=0;child->flaga8=false;
   }
  }
  payload->listeners.append(static_cast<Rva002BA8F1Listener*>(this));
 }
}
