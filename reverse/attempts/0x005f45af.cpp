// ?appendUpgradeList@@YAXAAVUnicodeString@@PBUUpgradeRecordView@@@Z
// partial score=0.9886685552407932 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include <bitset>
template<> bool _STL::_Base_bitset<32>::_M_is_any() const;
class GameTextInterface {
public:
 virtual ~GameTextInterface() {}
 virtual void s00()=0; virtual void s04()=0; virtual void s08()=0;
 virtual void s0c()=0; virtual void s10()=0; virtual void s14()=0;
 virtual void s18()=0; virtual void s1c()=0; virtual void s20()=0;
 virtual void s24()=0; virtual void s28()=0; virtual void s2c()=0;
 virtual void s30()=0;
 virtual UnicodeString fetch(const char*,bool *exists=0)=0;
 virtual UnicodeString fetch(const AsciiString&,bool *exists=0)=0;
};
extern GameTextInterface *TheGameText;
class UpgradeTemplate;
class UpgradeCenter { public: const UpgradeTemplate *rva0026EEA0(int) const; };
extern UpgradeCenter *TheUpgradeCenter;
struct UpgradeLabelView { char pad[0x2c]; AsciiString label; };
struct UpgradeRecordView { char pad[0x10]; _STL::_Base_bitset<32> flags; };
static __declspec(noinline) void appendUpgradeList(UnicodeString &out,const UpgradeRecordView *record)
{
 const _STL::_Base_bitset<32> &flags=record->flags;
 if(flags._M_is_any()) {
  UnicodeString names;
  UnicodeString separator=TheGameText->fetch("LW:ListSeparator");
  for(int i=0;i<1024;++i) {
   if(flags._M_w[(unsigned int)i>>5] & (1UL<<(i&31))) {
    const UpgradeTemplate *upgrade=TheUpgradeCenter->rva0026EEA0(i);
    if(upgrade) {
     const AsciiString &label=((const UpgradeLabelView*)upgrade)->label;
     if(!label.isEmpty()) {
      if(*(void**)&names && *(unsigned short*)((char*)*(void**)&names+4)!=0) names.concat(separator);
      names.concat(TheGameText->fetch(label));
     }
    }
   }
  }
  if(*(void**)&names && *(unsigned short*)((char*)*(void**)&names+4)!=0) {
   UnicodeString title=TheGameText->fetch("LW:UnitUpgradeListHeader");
   title.format(&title,names.str());
   out.concat((const unsigned short*)L"\n\n");
   out.concat(title);
  }
 }
}
void useUpgradeList(UnicodeString &out,const UpgradeRecordView *record){appendUpgradeList(out,record);}
