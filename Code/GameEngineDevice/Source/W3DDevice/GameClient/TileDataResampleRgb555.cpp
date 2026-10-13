// cl: /O1 /MD
// _Rva001118ECResampleRgb555, retail 0x001118EC (281 B), cdecl.
// Native 1118EC-111A05: average factor-square RGBA blocks with half-count
// rounding and saturate to 255, then quantize R/G/B to 15-bit RGB555.
// Caller 111A05 supplies factors 1,2,4,8,16,32,64 and TileData mip buffers.
// ZH TileData::doMip guides the averaging; RGB555 and direct source resampling
// are target-specific facts independently read from this complete body.
template<class T> inline const T &tileMin(const T &a,const T &b)
{ return a<b?a:b; }
extern "C" void __cdecl Rva001118ECResampleRgb555(
    const unsigned char *source,int stride,int factor,unsigned short *destination)
{
    unsigned char channels[4];
    int row=0;
    int count=factor*factor;
    for(;row<64;row+=factor) {
        const unsigned char *block=source;
        for(int column=0;column<64;column+=factor) {
            unsigned short sums[4]={0,0,0,0};
            const unsigned char *line=block;
            for(int y=0;y<factor;y++) {
                const unsigned char *pixel=line;
                for(int x=0;x<factor;x++) {
                    for(int c=0;c<4;c++)sums[c]+=pixel[c];
                    pixel+=4;
                }
                line+=stride;
            }
            for(int c=0;c<4;c++) {
                int average=(sums[c]+(count/2))/count;
                channels[c]=(unsigned char)tileMin(average,255);
            }
            unsigned short packed=(unsigned short)(((channels[2]+1)*31)/256);
            packed=(unsigned short)((packed<<5)|(((channels[1]+1)*31)/256));
            packed=(unsigned short)((packed<<5)|(((channels[0]+1)*31)/256));
            *destination++=packed;
            block+=factor*4;
        }
        source+=stride*factor;
    }
}
