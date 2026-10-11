// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport single-object _Destroy instances: nine-byte free functions
//
//     mov ecx,[esp+4] / jmp ~T
//
// _STL::_Destroy(T *) runs T's non-virtual destructor on its argument; the
// destructor call becomes a tail jump. Each instance tail-jumps to a matched
// ledger destructor whose owner class is address-named, so the element type
// is that owner (structural inference from the shape and the jump target;
// the class key follows the owner's every existing declaration). The
// emitting units are not recovered, so the instances are instantiated here.
#include <vector>

class Rva000C2980
{
public:
	~Rva000C2980();
};
class Rva00216108
{
public:
	~Rva00216108();
};
class Rva0022304A
{
public:
	~Rva0022304A();
};
class Rva0022CFE6
{
public:
	~Rva0022CFE6();
};
class Rva0022DDF4
{
public:
	~Rva0022DDF4();
};
class Rva00329D0E
{
public:
	~Rva00329D0E();
};
struct Rva00382B3F
{
public:
	~Rva00382B3F();
};
class Rva004104C9
{
public:
	~Rva004104C9();
};
class Rva00410688
{
public:
	~Rva00410688();
};
class Rva00466E23
{
public:
	~Rva00466E23();
};
class Rva004D960C
{
public:
	~Rva004D960C();
};
class Rva004E5086
{
public:
	~Rva004E5086();
};
class Rva004FF2F4
{
public:
	~Rva004FF2F4();
};
struct Rva004FABE2
{
public:
	~Rva004FABE2();
};
class Rva005011B4
{
public:
	~Rva005011B4();
};
struct Rva005F8447
{
public:
	~Rva005F8447();
};
struct Rva00600BBE
{
public:
	~Rva00600BBE();
};
class Rva00603C57
{
public:
	~Rva00603C57();
};

template void _STL::_Destroy<Rva000C2980>(Rva000C2980 *);
template void _STL::_Destroy<Rva00216108>(Rva00216108 *);
template void _STL::_Destroy<Rva0022304A>(Rva0022304A *);
template void _STL::_Destroy<Rva0022CFE6>(Rva0022CFE6 *);
template void _STL::_Destroy<Rva0022DDF4>(Rva0022DDF4 *);
template void _STL::_Destroy<Rva00329D0E>(Rva00329D0E *);
template void _STL::_Destroy<Rva00382B3F>(Rva00382B3F *);
template void _STL::_Destroy<Rva004104C9>(Rva004104C9 *);
template void _STL::_Destroy<Rva00410688>(Rva00410688 *);
template void _STL::_Destroy<Rva00466E23>(Rva00466E23 *);
template void _STL::_Destroy<Rva004D960C>(Rva004D960C *);
template void _STL::_Destroy<Rva004E5086>(Rva004E5086 *);
template void _STL::_Destroy<Rva004FF2F4>(Rva004FF2F4 *);
template void _STL::_Destroy<Rva004FABE2>(Rva004FABE2 *);
template void _STL::_Destroy<Rva005011B4>(Rva005011B4 *);
template void _STL::_Destroy<Rva005F8447>(Rva005F8447 *);
template void _STL::_Destroy<Rva00600BBE>(Rva00600BBE *);
template void _STL::_Destroy<Rva00603C57>(Rva00603C57 *);
