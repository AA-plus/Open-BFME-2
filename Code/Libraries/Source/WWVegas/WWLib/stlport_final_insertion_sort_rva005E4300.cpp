// The comparator carries the army context at +0 (native 5E4300); keep
// its four-byte state and class spelling consistent through the sort family.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__final_insertion_sort@PAHVRva005E4300Cmp@@@_STL@@YAXPAH0VRva005E4300Cmp@@@Z @0x005E4C2F 68B _STL::__final_insertion_sort<int *, Rva005E4300Cmp>.
// Over 16 elements guarded insertion sort of the head plus unguarded tail else guarded whole range.
// Evidence: chain from just-landed 0x005E4A1B and 0x005E4A48; same 68B shape as 0x004243D4 precedent.
struct Rva005E4300Context;
class Rva005E4300Cmp
{
public:
 char operator()(int a, int b) const;
private:
 Rva005E4300Context *m_context;
};
namespace _STL {
const int __stl_threshold = 16;
template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp);
template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp);
template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (last - first > __stl_threshold)
	{
		__insertion_sort(first, first + __stl_threshold, comp);
		__unguarded_insertion_sort(first + __stl_threshold, last, comp);
	}
	else
		__insertion_sort(first, last, comp);
}
template void __final_insertion_sort<int *, Rva005E4300Cmp>(int *, int *, Rva005E4300Cmp);
}
