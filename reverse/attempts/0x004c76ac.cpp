// ?rva004C76AC@ManTheWallsSpecialPower@@QAEPAVBfmeVecAV@@PAURva004C7621Range@@PBURva004C7621Pos@@@Z
// partial score=0.94 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct BfmeE8 {float m_distSq; void *m_item;};
void Rva00030830FreeAllocation(void *);
namespace _STL {
template<> inline void allocator<BfmeE8>::deallocate(BfmeE8 *p,unsigned int) const { if(p) Rva00030830FreeAllocation(p); }
template<> _Vector_base<BfmeE8,allocator<BfmeE8> >::_Vector_base(const allocator<BfmeE8> &);
}
class Object;
struct Rva004C7621Pos;
struct Rva004C7621Range;
class BfmeVecAV {public: Object **m_begin, **m_end;};
class ManTheWallsSpecialPower {public:
 void rva004C7621(Rva004C7621Range *,const Rva004C7621Pos *,_STL::vector<BfmeE8> *);
 BfmeVecAV *rva004C76AC(Rva004C7621Range *,const Rva004C7621Pos *);
};
BfmeVecAV *ManTheWallsSpecialPower::rva004C76AC(Rva004C7621Range *range,const Rva004C7621Pos *object) {
 _STL::vector<BfmeE8> candidates;
 rva004C7621(range,object,&candidates);
 for(int count=0;count<10;++count) {
  for(_STL::vector<BfmeE8>::iterator i=candidates.begin();i!=candidates.end();++i) {
   BfmeVecAV *members=(BfmeVecAV *)i->m_item;
   if((unsigned)(members->m_end-members->m_begin)<=(unsigned)count)
    return (BfmeVecAV *)i->m_item;
  }
 }
 return (BfmeVecAV *)candidates[0].m_item;
}
