// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// VectorClass<HAnimComboDataClass*>::~VectorClass() at 0x00196B50, split out
// of the hanim.cpp instantiation chain (built /G7 like hanim_vector_float_ctor.cpp).
// HAnimComboClass ctors 0x196B80/0x197650 install DynamicVectorClass vtable
// 0xBD5E88; its deleting dtor 0x197470 calls this body, which restores the
// VectorClass base vtable 0xBD5E58. The (int, T const *) ctor this TU once
// claimed at 0x001A36D0 installs 0xBD6C0C and belongs to the AggregateDefClass
// subobject list (VectorClass<W3dAggregateSubobjectStruct*>, agg_def.cpp).
// Only WWLib's real vector template is needed. Keeping the instantiations
// explicit avoids unrelated animation helpers and nonvirtual vector methods.
// The pointer element needs no array-constructor iterator or optimization anchor.
#include "always.h"
#include "vector.h"
class HAnimComboDataClass;

template VectorClass<HAnimComboDataClass*>::~VectorClass();

// ??_G?$DynamicVectorClass@PAVHAnimComboDataClass@@@@UAEPAXI@Z at 0x00197470 (30B):
// slot 0 of DynamicVectorClass vtable 0x7D5E88 installed by HAnimComboClass
// ctors 0x196B80/0x197650; calls rowed ??1 VectorClass 0x196B50 then delete.
template DynamicVectorClass<HAnimComboDataClass*>::DynamicVectorClass(unsigned, HAnimComboDataClass* const*);
template DynamicVectorClass<HAnimComboDataClass*>::~DynamicVectorClass();
template VectorClass<HAnimComboDataClass*>::VectorClass(int, HAnimComboDataClass* const*);
