// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva003B8802Set@@QAE@XZ @0x003B7167 77B
// Target set copy constructor independently fixes the32-byte two-vector view.
// The original class name remains unknown; unify its neutral constructor owner.
// Destruction clears records at+C and frees sorted storage at0 last:
// destroys the range at +0xC (rowed destroyRva003B678ARange 0x003B678A), then
// the vector at +0xC (rowed ~vector 0x003B7057), then frees the pointer at +0
// through the base destructor (pinned Rva00030830FreeAllocation 0x00030830).
#include <stdlib.h>
void Rva00030830FreeAllocation(void *block);
#define free Rva00030830FreeAllocation
#include <vector>

struct BfmeStringRecord003B3F78;
namespace _STL {template<> vector<BfmeStringRecord003B3F78>::~vector();}


struct Rva003B678ARange
{
	void *m_start;
	void *m_finish;
};

void destroyRva003B678ARange(Rva003B678ARange *range);

class Rva003B8802Set {
public:
 Rva003B8802Set(const Rva003B8802Set&);
 ~Rva003B8802Set();
private:
 _STL::vector<unsigned int> sorted;
 _STL::vector<BfmeStringRecord003B3F78> records;
 int freeHead,tail;
};
typedef char Rva003B8802SetExtent[sizeof(Rva003B8802Set)==32?1:-1];

Rva003B8802Set::~Rva003B8802Set()
{
	destroyRva003B678ARange(reinterpret_cast<Rva003B678ARange *>(&records));
}
