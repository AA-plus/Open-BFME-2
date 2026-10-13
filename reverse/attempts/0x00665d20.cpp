// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007FA170Slot@@@Z
// partial score=0.9812 date=2026-10-13
// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007FA170Slot@@@Z
// partial score=0.9793 date=2026-10-13
// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007FA170Slot@@@Z
// partial score=0.79 date=2026-10-02
// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007FA170Slot@@@Z
// Banked continuation: 414 compiled bytes, matching the full native extent.
// The native zero stores are preserved explicitly, but their scheduling and
// the final derived-vtable store still differ; this is not verified recovery.
// cl: /O2 /GX-
// FESL transactor: multi-part reply reassembly, retail 0x00665D20 (414 bytes;
// BFME 1 0x007F97B0, a dump there). The incoming-packet handler
// (FeslConnectionHandler::rva007F9D00) calls it for a reply whose transaction
// slot is still collecting parts. The first part allocates the slot's
// reassembly record and a buffer for the total size the hub reports. Each part's
// base64 "data" field is fetched into a scratch buffer, asserted to be a whole
// number of quads, decoded onto the end of the buffer and freed. When the buffer
// is complete, the reassembled packet is handed back to the handler (the +4
// subobject's slot 3) under a header carrying the reply's type, flags (bit 29
// cleared) and address. The assert texts name the FESL source,
// transactor.cpp, lines 0x13B and 0x13E.
//
// Names are address-derived except where BFME 2 already rows the callee.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <string.h>
template<class T> inline volatile T &__vref(T &x)

{
 return *(volatile T *)&x;
 
}
class Rva007E8810Message

{
 public:
 bool getString(const char *key, char *destination, int size);
 void *m_vtable;
 int m_04;
 int m_08;
 volatile int m_0C;
 char *volatile m_10;
 unsigned m_14;
 unsigned m_18;
 unsigned m_1C;
 int m_20;
 
}
;
class GenAlloc

{
 public:
 virtual void v0();
 virtual void v1();
 virtual void *alloc( unsigned size, int flags );
 virtual void release( void *block, int flags );
 
}
;
GenAlloc *Gen007EFFC0();
struct Rva007EB810Diag

{
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void fail( const char *expr, const char *file, int line );
 
}
;
Rva007EB810Diag *Rva007EB810Get();
int rva007FF250Decode( int length, const char *source, unsigned char *dest );
// The slot's reassembly record: total size, bytes received, buffer.
class Gen007F0130

{
 public:
 Gen007F0130() 
 
 {
  m_received = 0;
  m_total = 0;
  m_buffer = 0;
  
 }
 static void *operator new( unsigned int size );
 unsigned m_total;
 unsigned m_received;
 unsigned char *m_buffer;
 
}
;
struct Rva007FA170Slot

{
 int m_00;
 int m_04;
 Rva007E8810Message *m_08;
 void *m_0C;
 void *m_10;
 int m_14;
 Gen007F0130 *m_18;
 
}
;
class Rva007E86B0Base

{
 public:
 Rva007E86B0Base();
 virtual ~Rva007E86B0Base();
 int m_field04;
 
}
;
// The address the header carries (vftable 0x00CE0F20); this view stops at the
// three fields the header fills.
class Rva00808CB0LanGameEntry : public Rva007E86B0Base

{
 public:
 __forceinline Rva00808CB0LanGameEntry()
 
 {
  *(volatile int *)&m_field08 = 0;
  *(volatile int *)&m_field0c = 0;
  *(volatile int *)&m_field04 = 0;
  
 }
 virtual ~Rva00808CB0LanGameEntry();
 int m_field08;
 int m_field0c;
 
}
;
struct Rva00800E50Header

{
 Rva00800E50Header() : m_type( 0 ), m_flags( 0 ), m_text( 0 ), m_textLength( 0 ), m_10( false ) 
 
 {
  
 }
 unsigned m_type;
 int m_flags;
 const char *m_text;
 unsigned m_textLength;
 bool m_10;
 Rva00808CB0LanGameEntry m_entry;
 
}
;
class Rva007F9D00Handler

{
 public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void receive( Rva00800E50Header *header );
 
}
;
class Rva007F9D00Hub

{
 public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual unsigned totalSize( Rva007E8810Message *message );
 
}
;
class Rva007FA2C0

{
 public:
 void rva007F97B0( Rva007E8810Message *message, Rva007FA170Slot *slot );
 void *m_vtable;
 char m_pad04[ 0x20 ];
 Rva007F9D00Hub *m_hub;
// +0x24
 
}
;
void Rva007FA2C0::rva007F97B0( Rva007E8810Message *message, Rva007FA170Slot *slot )

{
 Gen007F0130 *record = slot->m_18;
 if( record == 0 )
 
 {
  record = new Gen007F0130;
  slot->m_18 = record;
  record->m_total = m_hub->totalSize( message );
  record->m_buffer = (unsigned char *)Gen007EFFC0()->alloc( record->m_total + 4, 1 );
  
 }
 char *text = (char *)Gen007EFFC0()->alloc( message->m_14, 0 );
 unsigned textCapacity = message->m_14;
 _ReadWriteBarrier();
 message->getString("data", text, (int)textCapacity);
 unsigned length = strlen( text );
 if( length & 3 )
 Rva007EB810Get()->fail( "(len & 0x3) == 0",
"\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp", 0x13b );
 unsigned decoded = length / 4 * 3;
 if( !rva007FF250Decode( length, text, record->m_buffer + __vref(record->m_received) ) )
 Rva007EB810Get()->fail( "result",
"\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp", 0x13e );
 record->m_received += decoded;
 Gen007EFFC0()->release( text, 0 );
 if( record->m_received >= record->m_total )
 
 {
  Rva00800E50Header header;
  header.m_type = message->m_1C;
  header.m_flags = message->m_20 & ~0x20000000;
  _ReadWriteBarrier();
  header.m_text = (const char *)record->m_buffer;
  _ReadWriteBarrier();
  header.m_textLength = record->m_total;
  header.m_entry.m_field04 = message->m_04;
  header.m_entry.m_field08 = message->m_08;
  header.m_entry.m_field0c = message->m_0C;
  ((Rva007F9D00Handler *)((char *)this + 4))->receive( &header );
  
 }
 
}
