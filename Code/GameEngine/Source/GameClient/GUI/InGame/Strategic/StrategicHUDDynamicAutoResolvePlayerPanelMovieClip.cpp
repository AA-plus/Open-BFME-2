// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// WB1612790 lines260..282; native005FBA3C..005FBAFE, RET8.
// Keep the exact125-byte Apt int/bool forwarder visible. Its input reads
// allow MSVC to reuse the dead image argument for the key and flag locals.
#include "ascii_string.h"

class Image;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

AsciiString Rva00222834Get(int val);


static __forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

// Primary owner: Rva005FFF62Family.cpp; this COMDAT copy is independently
// verified against the same complete 125-byte body and relocations.
// Retail 0x00577C23 125B, the next body: the same forward with an int and a
// bool, the bool as "0"/"1" through the rowed 0x004E678B (argc 2). Caller
// 0x005F31E0 ("SetUnitIconSlotVisibility", with the slot's Apt index).
char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00577C23Flag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

inline __declspec(noinline) int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, bool *pFlag)
{
	return target->rva00222B19(level, prefix, function, 2, GetStr(Rva00222834Get(*pInt)), (void *)Rva00577C23Flag(*pFlag), 0, 0, 0);
}



class Rva00524306 {
public:
    void rva00524306(const StringBase<char> &);
    void rva00524725(const AsciiString &,const Image *);
private:
    void *m_start,*m_finish,*m_end;
};

namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip { public: class Impl; };
}
class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl {
public:
    void ShowBanner(int slot,const Image *image);
private:
    void *m_owner;
    int m_level;
    AsciiString m_name;
    char m_pad0C[0x18-0x0C];
    Rva00524306 m_images;
    char m_pad24[0x3C-0x24];
    struct Banner { const Image *image; bool visible; char pad[3]; } m_banners[2];
};
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::ShowBanner(int slot,const Image *image)
{
    Banner *banner=&m_banners[slot];
    if(image!=banner->image){
        AsciiString key;
        key.format("_level%u.%s_Banner%d",m_level,m_name.str(),slot);
        if(image) m_images.rva00524725(key,image);
        else m_images.rva00524306(*(const StringBase<char> *)&key);
        banner->image=image;
    }
    if(!banner->visible){
        bool visible=true;
        Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,(void *)m_level,m_name.str(),"SetBannerVisibility",&slot,&visible);
        banner->visible=true;
    }
}
