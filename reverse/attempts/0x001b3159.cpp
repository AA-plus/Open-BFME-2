// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.8 date=2026-10-13
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.8 date=2026-10-13
// ?UnknownSlot4@BFME2Encoding0MotionChannel@@UAEXMPAVVector3@@PAPAE@Z
// partial score=0.80 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// Retail 0x001B3159 (442B). Port target: Code/Libraries/Source/WWVegas/WW3D2/BFME2Encoding0MotionChannelCtor.cpp
// (append after the dtor; MERGE with its BFME2MotionChannel/views - do NOT redefine; reuse its base/derived,
// add only FindIndex (IN-CLASS: out-of-line defs trip find_declared_unmatched even though rowed at 0x1B2EFC -
// in-class is exempt and inlines identically) + virtual UnknownSlot4 + Vector3; NO present-unmatched marker (hatch)).
// 440/442 in the TU (existing ctor/dtor rows re-verified). Interpolation (SSE lerps) is exact modulo cascade.
// FIXED HERE vs prior bank: low=0 before high=Count-2 in the search arm (was high-first; retail ands low first).
// WALL (single allocator decision + cascade): retail puts the cursor param in EBX (pushes 3 regs) and derives
// timecodes/masked/index around it; ours keeps cursor in EDX (2 regs) rotating the rest (timecodesEDI/maskedEBX).
// Everything downstream (including the exact SSE lerps) follows from that one choice. Tried/neutral: decl order,
// ai-style splits (N/A here), xor elimination (retail HAS the xor; keep index^low order).
// Prescription (U1 T-probe): cursor is ~6 deref uses vs masked-temps; find what tips ebx (likely the masked-temp
// web merging vs cursor web weight at FindIndex entry). Sibling slots 3/5 share this blocker; fix rolls forward.
// t=25 model=muse-spark (seat W7-MP6).
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass &); virtual ~BFME2MotionChannel(); virtual int UnknownSlot2();
 virtual void UnknownSlot3(float, float *, unsigned char **);
 virtual void UnknownSlot4(float, Vector3 *, unsigned char **);
 virtual void UnknownSlot5(float, Quaternion *, unsigned char **); virtual int UnknownSlot6();
 int Type, Pivot, Count, Components;
};
class BFME2Encoding0MotionChannel : public BFME2MotionChannel {
public:
 unsigned short *TimeCodes; float *Samples;
 __forceinline int FindIndex(unsigned time, int **cursor)
 {
  int low = 0;
  int index;
  if (cursor && (unsigned int)(index = **cursor) < (unsigned int)Count) {
   while (index && (TimeCodes[index] & ~0x8000) > time) --index;
   while (index < Count - 1 && (TimeCodes[index + 1] & ~0x8000) <= time) ++index;
   **cursor = index; ++*cursor;
   return index;
  } else {
   if (time <= (unsigned int)(TimeCodes[0] & ~0x8000)) index = 0;
   else if (time >= (unsigned int)(TimeCodes[Count - 1] & ~0x8000)) index = Count - 1;
   else {
    low = 0; int high = Count - 2;
    for (;;) {
     index = (low + high) / 2;
     if (time < (unsigned int)(TimeCodes[index] & ~0x8000)) high = index;
     else if (time >= (unsigned int)(TimeCodes[index + 1] & ~0x8000)) {
      int diff = index ^ low; if (diff) low = index; else ++low;
     } else break;
    }
   }
  }
  if (cursor) { **cursor = index; ++*cursor; }
  return index;
 }
 virtual void UnknownSlot3(float, float *, unsigned char **);
 virtual void UnknownSlot4(float, Vector3 *, unsigned char **);
 virtual void UnknownSlot5(float, Quaternion *, unsigned char **);
};
static __forceinline float lerpMotion(float a, float b, float t) { return (b - a) * t + a; }
void BFME2Encoding0MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
 int index = FindIndex((unsigned int)frame, reinterpret_cast<int **>(cursor));
 if (index == Count - 1 || (TimeCodes[index + 1] & 0x8000)) {
  float *samples = Samples + index * Components;
  value->X = samples[0]; value->Y = samples[1]; value->Z = samples[2]; return;
 }
 float t0 = float(TimeCodes[index] & ~0x8000), t1 = float(TimeCodes[index + 1] & ~0x8000);
 float ratio = (frame - t0) / (t1 - t0);
 float *samples = Samples + index * Components;
 value->X = lerpMotion(samples[0], samples[Components], ratio);
 value->Y = lerpMotion(samples[1], samples[Components + 1], ratio);
 value->Z = lerpMotion(samples[2], samples[Components + 2], ratio);
}
