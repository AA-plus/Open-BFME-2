// ?rva00596908@FadeInTextRender@@UAEXPAVText004721F0@@PBUICoord2D@@I@Z
// partial score=0.9305 date=2026-10-13
// ?rva00596908@FadeInTextRender@@UAEXPAVText004721F0@@PBUICoord2D@@I@Z
// partial score=0.9 date=2026-10-13
// Target Ghidra5967B3+341; same 54-byte owner as constructor/dtor5966DD/59675A.
// BF1 9cbfb551fe20 FadeInTextRender.cpp initialize is the primary source lead:
// font scaling plus TextElvenClouds allocation. Target uses one animation and three phases.
// Target facts: Display slot40 unsigned width; FontLibrary getFont; Anim2D allocation34,
// template/collection call providers; oldScale20/font4; width4C and animation-derived height50.
// 0.75 and .00125 are compiler constants verified against retail data, not global escape hatches.
// Phase stores straddle two reads of canonical g_009BA4E8; preserve that alias-sensitive order.
// Existing address-derived constructor argument views retain provider identity uncertainty.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/ICoord2D.h"

class Text004721F0 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual UnicodeString getText();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void colors(unsigned, unsigned);
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void draw(int,int,int,int);
 virtual void size(int*,int*);
};

struct Template004721F0 { char field00[16]; unsigned short field10;
 unsigned short getNumFrames() const { return field10; } };
class Anim2DCallView { public:
 void draw(int,int,int,int);
 char field00[12]; Template004721F0* field0c; char field10[12]; float field1c;
 const Template004721F0* getAnimTemplate() const { return field0c; }
 void setAlpha(float a) { field1c = a; }
};
class Gen_00470870 {public:void bfmeExtend(int,int,int,int);};

class Display;extern Display *TheDisplay;
class FadeDisplayCalls {public:
 virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void p2c();virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual unsigned width();};
class GameFont;class FontLibrary {public:GameFont*getFont(const AsciiString*,float,bool);};extern FontLibrary*TheFontLibrary;
class Anim2DTemplate;class Anim2DCollection;extern Anim2DCollection*TheAnim2DCollection;
// The collection's template lookup is rowed under its address class.
struct Rva002D752DNode;class Rva002D752D {public:Rva002D752DNode*rva002D752D(const StringBase<char>&);};
static inline const StringBase<char>&fadeTextBase(const AsciiString&s){return *(const StringBase<char>*)&s;}
class Anim2D {public:void setCurrentFrame(unsigned short);void draw(int,int,int,int);Anim2D(Anim2DTemplate*,Anim2DCollection*);unsigned getCurrentFrameHeight() const;char pad[0x34];};
extern int g_009BA4E8;
// Slot 1 of FadeInTextRender's vftable 0x00C70A70 (slot 0 is its deleting
// destructor), as WB's LoadAssets is slot 1 of its table: virtual.
class FadeInTextRender {public:
 virtual ~FadeInTextRender();virtual void LoadAssets();virtual void rva00596908(Text004721F0*,const ICoord2D*,unsigned);
 GameFont*font;int minX,minY,maxX,maxY;unsigned effectColor;Anim2D*anim;float oldScale;AsciiString fontName;unsigned color;int delay;unsigned fontSize;unsigned starts[3],ends[3];int width,height;
};
void FadeInTextRender::LoadAssets() {
 float naturalWidth=(float)((FadeDisplayCalls*)TheDisplay)->width();
 float scale=naturalWidth*0.00125f;scale*=0.75f;
 if(scale!=oldScale){font=0;oldScale=scale;}
 if(!font)font=TheFontLibrary->getFont(&fontName,(float)fontSize*scale,false);
 if(!anim){
  anim=new Anim2D((Anim2DTemplate*)((Rva002D752D*)TheAnim2DCollection)->rva002D752D(fadeTextBase(AsciiString("TextElvenClouds"))),TheAnim2DCollection);
  starts[1]=0;int end=g_009BA4E8;ends[2]=~0u;
  ends[1]=end;starts[2]=end+1;
  starts[0]=starts[2]+g_009BA4E8/2;ends[0]=~0u;
 }
 width=(int)naturalWidth;
 height=(int)((float)anim->getCurrentFrameHeight()*scale);
}

// Native596908..596AE9 is FadeInTextRender tableC70A70 slot2. BF1 cee35b7d8
// FadeInTextRenderDraw004721F0 is the semantic guide; target bounds worker
// 59668D and the single cloud animation are target-specific. Original method
// spelling is retained as unknown; the class follows the named LoadAssets slot.
void FadeInTextRender::rva00596908(Text004721F0* text, const ICoord2D* pos, unsigned frame) {
 int w, h;
 text->size(&w, &h);
 UnicodeString s = text->getText();
 const ICoord2D &point = *pos;
 volatile int y=point.y-(height-h)/2;
 int x = point.x;
 int width = 0;
 text->size(&width, 0);
 int bottom = y + height;
 int right = x + width;
 ((Gen_00470870*)this)->bfmeExtend(x,y,right,bottom);
 for(int i=0;i<3;++i) {
  unsigned start=starts[i], end=ends[i];
  if(frame>=start && frame<=end) {
   float progress=float(frame-start)/float(end-start);
   switch(i) {
   case 0: {
    unsigned frames=((Anim2DCallView*)anim)->getAnimTemplate()->getNumFrames();
    if(frames) {
     anim->setCurrentFrame(((frame-start)/4)%frames);
     unsigned color=effectColor;
     ((Anim2DCallView*)anim)->setAlpha(float(color>>24)/255.0f);
     anim->draw(x-width/2,y,width*2,height);
     anim->draw(x-width/2,y,width*2,height);
    }
    break;
   }
   case 1: {
    unsigned alpha=(unsigned)(int)((1.0f<progress ? 1.0f:progress)*255.0f)<<24;
    unsigned textColor=(color&0xffffff)|alpha;
    text->colors(textColor,alpha);
    text->draw(point.x,point.y,1,1);
    break;
   }
   case 2:
    text->colors(color|effectColor,effectColor);
    text->draw(point.x,point.y,1,1);
    break;
   }
  }
 }
}
