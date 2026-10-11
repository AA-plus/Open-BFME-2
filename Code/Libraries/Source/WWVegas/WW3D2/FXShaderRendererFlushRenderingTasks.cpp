// cl: /O1 /G7 /MD /EHsc
// Native comparator0017368A..001736A7 follows a RET4 at00173687.
// Both range flushers001748B3 and00174A57 pass this address to the owned
// STLport sort over32-byte rendering tasks. Only the mesh pointer at task0
// and its unsigned ordering word at meshC4 are read here. The names below
// describe an address-derived ABI view; the original record and method
// spelling are unknown. Native EAX is the complete zero/one result.
struct Rva0017368AMesh { char unknown[0xc4]; unsigned key; };
struct Rva0017368ATask { Rva0017368AMesh *mesh; char unknown[28]; };

unsigned Rva0017368ACompare(const Rva0017368ATask &a, const Rva0017368ATask &b)
{
    return a.mesh->key < b.mesh->key;
}

// Native001748B3..001748E8 is a RET0 range flusher, rather than the
// unrelated vector::resize suggested by the drift queue. Its three calls
// are sort00174870, rendering0017438B and erase00173FB6. The rendering
// worker's existing address-derived two-word declaration is retained;
// WB names that worker FXShaderRenderer::PerformRendering. No original
// name or complete renderer layout is claimed for this receiver view.
void rva00174870(int, int, int);
class Rva0017438B {public:void rva0017438B(int,int);};
struct BfmeAssignRecord32 {char unknown[32];};
namespace _STL {
template<class T>class allocator {};
template<class T,class A>class vector {public:T*erase(T*,T*);};
}
class Rva001748B3 {
public:void rva001748B3();
private:int start,finish,limit;
};

void Rva001748B3::rva001748B3()
{
    if(start==finish)return;
    rva00174870(start,finish,(int)&Rva0017368ACompare);
    ((Rva0017438B*)this)->rva0017438B(start,finish);
    ((_STL::vector<BfmeAssignRecord32,_STL::allocator<BfmeAssignRecord32> >*)this)->erase((BfmeAssignRecord32*)start,(BfmeAssignRecord32*)finish);
}
