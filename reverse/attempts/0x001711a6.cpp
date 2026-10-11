// ?rva001711a6@Rva00171024@@QAEXXZ
// partial score=0.57 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Full semantic reconstruction of native 1711A6..171522 (892B).
// WB A12EB0 names TexturePacker::UpdateResultTexture in texturepacker.cpp.
// The existing receiver spelling remains address-derived while its providers
// are reconciled. No guessed callee pins accompany this reconstruction.
#include <map>
#include <algorithm>

class TextureClass {
public:
    void Release_Ref();
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
};
class AssetReference {
public:
    TextureClass *object;
    AssetReference() : object(0) {}
    AssetReference(const AssetReference &a) : object(a.object) { if(object) object->Add_Ref(); }
    ~AssetReference() { if(object) object->Release_Ref(); }
    bool operator<(const AssetReference &a) const { return (unsigned)object < (unsigned)a.object; }
};
struct Rva00170999Data { unsigned left,top,right,bottom; };
class Rva00170BFF {
public:
    Rva00170999Data *rva00171128(const AssetReference &);
};
class Rva001333C6 { public: void f(); };
struct IDirect3DBaseTexture8;
class TextureBaseClass {
public:
    int rva0013275A() const;
    int rva00132784() const;
    IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};
class Rva00131DFC {
public: void rva00131DFC(void *,void *,void *,void *,int,int);
};
class W3DRadarResetSurface {
public:
    void *surface;
    ~W3DRadarResetSurface();
    void clear(unsigned);
};
class CursorTextureSlot {
public: W3DRadarResetSurface Get_Surface_Level();
};
class TextureInitializationView {
public:
    virtual void slot0()=0; virtual void slot1()=0;
    virtual void slot2()=0; virtual void slot3()=0;
    virtual void slot4()=0; virtual void slot5()=0;
    virtual void slot6()=0; virtual void slot7()=0;
    virtual void slot8()=0; virtual void slot9()=0;
    virtual bool Is_Initialized() const=0;
};
extern "C" long __stdcall D3DXLoadSurfaceFromSurface(void *,void *,const Rva00170999Data *,void *,void *,const Rva00170999Data *,unsigned,unsigned);
extern "C" long __stdcall D3DXFilterTexture(void *,void *,unsigned,unsigned);

typedef _STL::map<AssetReference,Rva00170999Data> RectangleMap;
typedef _STL::multimap<unsigned,AssetReference> AreaMap;
class Rva00171024 {
public:
    void rva001711a6();
    unsigned maxSize;
    unsigned format;
    RectangleMap rectangles;
    RectangleMap::iterator current;
    AssetReference result;
    bool dirty;
    bool blackWhite;
    float inverseWidth,inverseHeight;
};

void Rva00171024::rva001711a6()
{
    dirty=false;
    reinterpret_cast<Rva001333C6 *>(&result)->f();
    inverseWidth=inverseHeight=1.0f;
    AreaMap byArea;
    for(RectangleMap::iterator it=rectangles.begin(); it!=rectangles.end(); ++it) {
        const TextureBaseClass *texture=reinterpret_cast<const TextureBaseClass *>(&it->first);
        unsigned area=(unsigned)texture->rva00132784()*(unsigned)texture->rva0013275A();
        byArea.insert(AreaMap::value_type(area,it->first));
    }
    int side=1;
    int skyline[64];
    skyline[0]=0;
    for(AreaMap::reverse_iterator it=byArea.rbegin(); it!=byArea.rend(); ++it) {
        AssetReference texture(it->second);
        TextureBaseClass *handle=reinterpret_cast<TextureBaseClass *>(&texture);
        int width=((unsigned)handle->rva0013275A()+31u)>>5;
        int height=((unsigned)handle->rva00132784()+31u)>>5;
        int y;
        for(;;) {
            for(y=0; y<=side-height; ++y) {
                int j;
                for(j=0; j<height; ++j)
                    if(skyline[y+j]+width>side) break;
                if(j==height) break;
            }
            if(y<=side-height) break;
            if((unsigned)(side<<6)>maxSize) return;
            for(int n=side; n<side*2; ++n) skyline[n]=0;
            side*=2;
        }
        int x=0;
        for(int j=0; j<height; ++j) if(skyline[y+j]>x) x=skyline[y+j];
        for(int j=0; j<height; ++j) skyline[y+j]=x+width;
        Rva00170999Data *rect=reinterpret_cast<Rva00170BFF *>(&rectangles)->rva00171128(texture);
        rect->left=x<<5;
        rect->top=y<<5;
        rect->right=rect->left+handle->rva0013275A();
        rect->bottom=rect->top+handle->rva00132784();
    }
    int pixels=side<<5;
    reinterpret_cast<Rva00131DFC *>(&result)->rva00131DFC((void *)pixels,(void *)pixels,(void *)format,0,1,0);
    if(!result.object || !reinterpret_cast<TextureInitializationView *>(result.object)->Is_Initialized()) return;
    inverseWidth=inverseHeight=1.0f/pixels;
    W3DRadarResetSurface destination=reinterpret_cast<CursorTextureSlot *>(&result)->Get_Surface_Level();
    destination.clear(blackWhite);
    for(RectangleMap::iterator it=rectangles.begin(); it!=rectangles.end(); ++it) {
        AssetReference texture(it->first);
        Rva00170999Data rect=it->second;
        W3DRadarResetSurface source=reinterpret_cast<CursorTextureSlot *>(&texture)->Get_Surface_Level();
        D3DXLoadSurfaceFromSurface(destination.surface,0,&rect,source.surface,0,0,1,0);
    }
    D3DXFilterTexture(reinterpret_cast<TextureBaseClass *>(&result)->Peek_D3D_Base_Texture(),0,~0u,~0u);
}

