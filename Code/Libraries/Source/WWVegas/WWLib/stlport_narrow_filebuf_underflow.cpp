// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ob0
// stlport
//
// The narrow twin of stlport_wide_filebuf_underflow.cpp - same instantiation as
// stlport_narrow_filebuf.cpp built without inline expansion, because retail's
// underflow is a plain forwarder to _Underflow::_M_doit and cl folds _M_doit
// into it at the default level.

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_input_error(); }
namespace _STL { template <> int basic_filebuf<char, char_traits<char> >::_M_underflow_aux(); }
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::open(char const *, int); }
// bfme link decl-only end

// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}


template class _STL::basic_filebuf<char, _STL::char_traits<char> >;
