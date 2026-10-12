// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z
// partial score=0.987 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z: ZH x/MAP_XY_FACTOR through an inline WWMath::Floor wrapper; second floor now exact, only the first call keeps fstp ahead of the first cleanup pop ecx (4 bytes). The RGB555 unpack is still inline asm from the earlier bank (not admissible as is).
extern "C" __declspec(dllimport) double __cdecl floor(double);
__forceinline long round_float(float f) { long i; __asm { fld [f]
 fistp [i] } return i; }
struct WWMath { static __forceinline float Floor(float val) { return (float)floor(val); } };
struct RGBColor { float red,green,blue; };
class Rva000ABD00 { public: int rva000ABD00(unsigned int); };
struct Tile { char pad[0x2ab0]; unsigned short pixel; };
class WorldHeightMap { public: void getTerrainColorAt(float,float,RGBColor*); private: char pad[8]; int width,height,border; char pad14[0x20-0x14]; int dataSize; char pad24[0x98-0x24]; short *tileNdxes; };
void WorldHeightMap::getTerrainColorAt(float x,float y,RGBColor* out) {
 int ix=round_float(WWMath::Floor(x/10.0f));
 int iy=round_float(WWMath::Floor(y/10.0f));
 ix+=border; iy+=border;
 out->red=out->green=out->blue=0;
 if(ix<0)ix=0;if(iy<0)iy=0;
 if(ix>=width)ix=width-1;
 if(iy>=height)iy=height-1;
 int ndx=iy*width+ix;
 if(ndx<0||ndx>=dataSize)return;
 short tileNdx=tileNdxes[ndx];
 tileNdx=tileNdx>>2;
 Tile* tile=(Tile*)((Rva000ABD00*)this)->rva000ABD00(tileNdx);
 if(tile) {
  unsigned int rgb;
  unsigned short color=tile->pixel;
  unsigned int *dest=&rgb;
  __asm {
   movzx eax, color
   mov ebx, eax
   shr eax, 0Ah
   shl ebx, 3
   shl eax, 13h
   shl bh, 3
   mov ax, bx
   mov ebx, eax
   shr ebx, 5
   and ebx, 3F3F3Fh
   add eax, ebx
   mov edi, dest
   mov [edi], eax
  }
  unsigned char *data=(unsigned char*)&rgb;
  out->red=data[0]*(1.0/255.0);
  out->green=data[1]*(1.0/255.0);
  out->blue=data[2]*(1.0/255.0);
 }
}
