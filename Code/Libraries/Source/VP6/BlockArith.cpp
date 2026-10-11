// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7d60.md 001b7aa0.md plus retail
// only. No decoder source was consulted.
//
// Scalar 8x8 block arithmetic (retail 0x001B7AA0 and 0x001B7D60), written out
// four rows per pass and two passes, as retail has them.

// AverageBlock_C retail 0x001B7AA0 (582 bytes): the average of two byte planes
// into a packed 8x8 block of 16-bit values.
extern "C" void __cdecl AverageBlock_C(const unsigned char *first,const unsigned char *second,unsigned short *dst,int stride) {
 int groups=2;
 do {
  dst[0]=(first[0]+second[0])>>1;
  dst[1]=(first[1]+second[1])>>1;
  dst[2]=(first[2]+second[2])>>1;
  dst[3]=(first[3]+second[3])>>1;
  dst[4]=(first[4]+second[4])>>1;
  dst[5]=(first[5]+second[5])>>1;
  dst[6]=(first[6]+second[6])>>1;
  dst[7]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[8]=(first[0]+second[0])>>1;
  dst[9]=(first[1]+second[1])>>1;
  dst[10]=(first[2]+second[2])>>1;
  dst[11]=(first[3]+second[3])>>1;
  dst[12]=(first[4]+second[4])>>1;
  dst[13]=(first[5]+second[5])>>1;
  dst[14]=(first[6]+second[6])>>1;
  dst[15]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[16]=(first[0]+second[0])>>1;
  dst[17]=(first[1]+second[1])>>1;
  dst[18]=(first[2]+second[2])>>1;
  dst[19]=(first[3]+second[3])>>1;
  dst[20]=(first[4]+second[4])>>1;
  dst[21]=(first[5]+second[5])>>1;
  dst[22]=(first[6]+second[6])>>1;
  dst[23]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst[24]=(first[0]+second[0])>>1;
  dst[25]=(first[1]+second[1])>>1;
  dst[26]=(first[2]+second[2])>>1;
  dst[27]=(first[3]+second[3])>>1;
  dst[28]=(first[4]+second[4])>>1;
  dst[29]=(first[5]+second[5])>>1;
  dst[30]=(first[6]+second[6])>>1;
  dst[31]=(first[7]+second[7])>>1;
  first+=stride; second+=stride;
  dst+=32;
 } while (--groups);
}

// SubtractBlock_C retail 0x001B7D60 (450 bytes): the byte block minus the
// existing 16-bit block, stored back into the 16-bit block.
extern "C" void __cdecl SubtractBlock_C(const unsigned char *src, unsigned short *dst, int stride) {
 int groups=2;
 do {
  dst[0]=src[0]-dst[0];
  dst[1]=src[1]-dst[1];
  dst[2]=src[2]-dst[2];
  dst[3]=src[3]-dst[3];
  dst[4]=src[4]-dst[4];
  dst[5]=src[5]-dst[5];
  dst[6]=src[6]-dst[6];
  dst[7]=src[7]-dst[7];
  src+=stride;
  dst[8]=src[0]-dst[8];
  dst[9]=src[1]-dst[9];
  dst[10]=src[2]-dst[10];
  dst[11]=src[3]-dst[11];
  dst[12]=src[4]-dst[12];
  dst[13]=src[5]-dst[13];
  dst[14]=src[6]-dst[14];
  dst[15]=src[7]-dst[15];
  src+=stride;
  dst[16]=src[0]-dst[16];
  dst[17]=src[1]-dst[17];
  dst[18]=src[2]-dst[18];
  dst[19]=src[3]-dst[19];
  dst[20]=src[4]-dst[20];
  dst[21]=src[5]-dst[21];
  dst[22]=src[6]-dst[22];
  dst[23]=src[7]-dst[23];
  src+=stride;
  dst[24]=src[0]-dst[24];
  dst[25]=src[1]-dst[25];
  dst[26]=src[2]-dst[26];
  dst[27]=src[3]-dst[27];
  dst[28]=src[4]-dst[28];
  dst[29]=src[5]-dst[29];
  dst[30]=src[6]-dst[30];
  dst[31]=src[7]-dst[31];
  src+=stride;
  dst+=32;
 } while (--groups);
}
