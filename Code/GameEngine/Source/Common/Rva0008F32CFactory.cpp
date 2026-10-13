// cl: /O1 /GX /MD
//
// ?rva0008F32C@@YAXXZ @0x0008F32C 69B: EH factory storing to global.
// // News 0x88 via rowed new 0x0002FDA0, ctors via pinned 0x0010461F,
// // stores to existing global theRadarWindowOverrideSource at 0x00DFF028, calls
// // virtual slot1. Honest address-derived Rva0010461F/Vtbl; proven
// // new and global; boundary verified (mov eax prologue, ret end).

class Rva0010461F { public: Rva0010461F(); virtual void vslot000(); virtual void vslot001(); private: char m_pad04[0x88 - 4]; };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
void rva0008F32C() {
	Rva0010461F *p = new Rva0010461F;
	theRadarWindowOverrideSource = (RadarWindowOverrideSource *)p;
	((Rva0010461F *)p)->vslot001();
}
