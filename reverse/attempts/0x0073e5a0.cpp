// ?GetNearestGroupWithValue@ShroudManagerImpl@@QAE_NPBUCoord3D@@IHIPAU2@@Z
// partial score=0.9491956 date=2026-10-12
// cl: /O2 /G6 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// Target identity: WB17E83B0 Libraries/Source/shroudmanager/shroudmanager_impl.cpp,
// asserts 783..785, native wrapper739820 and ScriptActions3C0F44 support boolean search.
// Real whole boundary73E5A0..73EA3D: early false tail73EA36..73EA3D follows main return.
// Candidate parser identity at this RVA is refuted by shroud cells/20-player value loop.
// Native fields: scale1C,width24,height28,elements2C; cellsA8, players8B,value+6+index*2.
// Prefix725B exact; final output/cleanup sequences exact; two vertical enqueue schedules
// and add/xor ordering differ. Native startup does not mark the initial point visited.
// BfmeE8 and Rva0073E4C0Record names are existing opaque8B views, not recovered retail types.
// Donor semantic lead: BF1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 ZH
// PartitionManager getNearestGroupWithValue/iterateCellsBreadthFirst. Native differs
// in mask/value-index/threshold and left,right,up,down ordering; donor names/layouts
// are not claimed as target facts. No new pin or tracked source was changed.
#include <vector>
#include <deque>
struct Coord3D { float x,y,z; };
struct BfmeE8 { int a,b; };
struct Rva0073E4C0Record { Rva0073E4C0Record(); Rva0073E4C0Record(const Rva0073E4C0Record&); ~Rva0073E4C0Record(); Rva0073E4C0Record&operator=(const Rva0073E4C0Record&); private: char bytes[8]; };
namespace _STL {
template<> vector<bool>::vector(unsigned,bool,const allocator<bool>&);
template<> deque<BfmeE8>::~deque();
template<> void _Deque_base<BfmeE8,allocator<BfmeE8> >::_M_initialize_map(unsigned);
template<> void deque<Rva0073E4C0Record>::push_back(const Rva0073E4C0Record&);
}
static __forceinline void pushShroudCell(_STL::deque<BfmeE8>& q,const BfmeE8& p) {
    ((_STL::deque<Rva0073E4C0Record>*)&q)->push_back(*(const Rva0073E4C0Record*)&p);
}
class Gen_008F7CD0 { public: int bfmeCellX(float)const; int bfmeCellY(float)const; };
struct ShroudCell { void *nodes; unsigned short playerStates[20][4]; unsigned trailing; };
class ShroudManagerImpl {
public: bool GetNearestGroupWithValue(const Coord3D*,unsigned,int,unsigned,Coord3D*);
private: unsigned char prefix[0x1c]; float cellSize, inverse; unsigned width,height;ShroudCell* elements;
};
bool ShroudManagerImpl::GetNearestGroupWithValue(const Coord3D* source,unsigned mask,int valueIndex,unsigned required,Coord3D* output)
{
 if(!mask || valueIndex<0 || valueIndex>=3)return false;
 mask&=0xfffff;
 int cellX=((const Gen_008F7CD0*)this)->bfmeCellX(source->x);
 int cellY=((const Gen_008F7CD0*)this)->bfmeCellY(source->y);
 if(cellX<0)cellX=0;else if(cellX>=(int)width)cellX=width-1;
 if(cellY<0)cellY=0;else if(cellY>=(int)height)cellY=height-1;
 _STL::vector<bool> visited(width*height,false);
 const _STL::vector<bool>& tested=visited;
 _STL::deque<BfmeE8> queue;
 { BfmeE8 initial={cellX,cellY};pushShroudCell(queue,initial); }
 while(!queue.empty()) {
  unsigned x=queue.front().a, y=queue.front().b;
  unsigned cell=y*width+x;
  queue.pop_front();
  if(x>0 && !tested[cell-1]) { visited[cell-1]=true;BfmeE8 p={x-1,y};pushShroudCell(queue,p); }
  if(x<width-1 && !tested[cell+1]) { visited[cell+1]=true;BfmeE8 p={x+1,y};pushShroudCell(queue,p); }
  if(y>0 && !tested[cell-width]) { visited[cell-width]=true;BfmeE8 p={x,y-1};pushShroudCell(queue,p); }
  if(y<height-1 && !tested[cell+width]) { visited[cell+width]=true;BfmeE8 p={x,y+1};pushShroudCell(queue,p); }
  unsigned value=0;
  ShroudCell *current=&elements[cell];
  unsigned bits=mask;
  if(bits) { unsigned short *word=&current->playerStates[0][valueIndex+1];do { if(bits&1)value+=*word;bits>>=1;word+=4; } while(bits); }
  if(value>=required) { output->x=(cell%width)*cellSize;output->y=(cell/width)*cellSize;output->z=0;return true; }
 }
 return false;
}
