// cl: /O1 /arch:SSE /G7 /Oy-
// Native25B wrappers at 0x001ECD19 and0x001ECB78 forward a vector receiver
// unchanged in ECX to0x001EC1B4. The old free stdcall declarations lost that ABI.
// Caller1ECE98 passes its +A4 vector; worker1EC1B4 reads start/finish/end at0/4/8
// and divides distances by172 before calling the owned record copy helpers.
// Thus the old basic_string<char> worker pin is refuted. Placeholder owner
// spellings remain: the original template/tag identity is not claimed here.
// The fourth worker argument is the existing address of the last pointer's
// high byte; its original empty-tag type remains unreconstructed.
struct BfmeAssignRecord172;
class Rva001EC1B4 { public: void rva001EC1B4(BfmeAssignRecord172 *,BfmeAssignRecord172 *,BfmeAssignRecord172 *,char *); };
class Rva001ECD19 { public: void rva001ECD19(BfmeAssignRecord172 *,BfmeAssignRecord172 *,BfmeAssignRecord172 *); };
class Rva001ECB78 { public: void rva001ECB78(BfmeAssignRecord172 *,BfmeAssignRecord172 *,BfmeAssignRecord172 *,int); };
void Rva001ECD19::rva001ECD19(BfmeAssignRecord172 *pos,BfmeAssignRecord172 *first,BfmeAssignRecord172 *last)
{ ((Rva001EC1B4 *)this)->rva001EC1B4(pos,first,last,(char *)&last+3); }
void Rva001ECB78::rva001ECB78(BfmeAssignRecord172 *pos,BfmeAssignRecord172 *first,BfmeAssignRecord172 *last,int ignored)
{ ((Rva001EC1B4 *)this)->rva001EC1B4(pos,first,last,(char *)&last+3); }
