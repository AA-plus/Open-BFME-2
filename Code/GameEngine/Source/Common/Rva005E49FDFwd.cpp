// cl: /DNDEBUG /MD
// Native5E49FD..5E4A1B is the complete30B cdecl partition forwarder.
// Caller5E4E55 uses the returned EAX as an iterator into its int vector.
// The four-byte comparator carries the caller's army context. The fifth
// bool* is passed last and is unused by the owned75B partition provider.
// Original function names remain unknown; remove the former void alias pin.
struct Rva005E4300Context;
class Rva005E4300Cmp {
public: char operator()(int,int) const;
private: Rva005E4300Context *m_context;
};
int *__cdecl Rva005E4817Partition(int *,int *,Rva005E4300Cmp,int,bool *);

int *__cdecl rva005E49FD(int *first,int *last,Rva005E4300Cmp comp,int pivot)
{
	bool tmp;
	return Rva005E4817Partition(first,last,comp,pivot,&tmp);
}
