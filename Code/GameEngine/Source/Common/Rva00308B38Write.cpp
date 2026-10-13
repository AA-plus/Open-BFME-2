// cl: /O1 /G7 /Oy- /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
#include <utility>
#include <vector>
#include "ascii_string.h"
class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void writeInt(int v);
	void writeReal(float v);
	void writeAsciiString(const AsciiString &s);
	void closeDataChunk();
};
struct Rva0007E394Element {unsigned opaque;bool operator<(const Rva0007E394Element&)const;bool operator==(const Rva0007E394Element&)const;};
class Rva00537EAD { public: void rva00537EAD(DataChunkOutput *output); };
class Rva0030B2FE { public: void rva0030B2FE(DataChunkOutput *output); };
struct Rva00308B38Water : Rva00537EAD
{
	char m_pad[0x38];
	Rva0030B2FE m_38;
	char m_pad39[0x78 - 0x38 - 1];
	AsciiString m_78[2];
	AsciiString m_80;
	char m_pad84[8];
	AsciiString m_8c;
};
struct Rva00308B38Iterator {void *set;int index;Rva00308B38Iterator(void *p,int i):set(p),index(i){} };
struct Rva00308B38Entry {int key;Rva00308B38Water *water;};
struct Rva00308B38Set {char pad00[0x14];_STL::vector<Rva00308B38Entry> entries; Rva00308B38Iterator begin(){return Rva00308B38Iterator(this,0);} Rva00308B38Iterator end(){return Rva00308B38Iterator(this,(int)entries.size());}};
typedef _STL::pair<const unsigned,Rva0007E394Element*> BfmeEqualityWords;
static __forceinline bool EqualIterators(const Rva00308B38Iterator &a,const Rva00308B38Iterator &b) {
 return *reinterpret_cast<const BfmeEqualityWords*>(&a)==*reinterpret_cast<const BfmeEqualityWords*>(&b);
}
void __cdecl Rva00308B38Write(Rva00308B38Set *set, DataChunkOutput *out)
{
	out->openDataChunk("StandingWaterAreas", 2);
	out->writeInt((int)set->entries.size());
	Rva00308B38Iterator end = set->end();
	Rva00308B38Iterator current = set->begin();
	for (; !EqualIterators(current, end); ++current.index) {
		Rva00308B38Entry &entry = reinterpret_cast<Rva00308B38Set*>(current.set)->entries[current.index];
		Rva00308B38Water *water = entry.water;
		out->writeInt(entry.key);
		water->rva00537EAD(out);
		for (int i = 0; i < 2; ++i)
			out->writeAsciiString(water->m_78[i]);
		water->m_38.rva0030B2FE(out);
		out->writeAsciiString(water->m_80);
		out->writeAsciiString(water->m_8c);
	}
	out->closeDataChunk();
}
