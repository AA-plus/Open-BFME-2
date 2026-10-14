// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// WaterTracksObj::init, ported from Open-BFME-1 9cbfb551fe20
// GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp and
// guided by Zero Hour's W3DWaterTracks.cpp.
//
// Target facts (native FE379..FE8FC, RET 0x1C, seven arguments from the
// editor callers): bounds +0x08..+0x2C, wave type +0x30, start +0x40,
// initial start/end +0x58/+0x60, time offset +0x68 and the timing block
// +0x6C..+0xAC. BFME 2 adds an optional map-settings object whose values
// override the per-type wave table; its class is unknown, so its getters
// are reached through the providers already rowed at their addresses
// (0x30C934/0x30C8CC/0x30C8E6/0x30C900 address-named float-to-int getters,
// 0x30C8A7 and 0x5508E2 ICF-folded int getters at +0x80/+0x84).
// BFME 2 also computes timeToStop before timeToReachBeach (retail's x87
// load order of the total-time sum needs that statement order).
#include "vector2.h"
#include "vector3.h"
#include "sphere.h"
#include <math.h>
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr { public: T *m_ptr; const RefCountPtr &operator=(const RefCountPtr &); ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();} };
class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass> {};
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *,int,int);
};
float GetGameClientRandomValueReal(float,float,char *,int);
class Rva0030C934IntGetter { public: int get()const; };
class Rva0030C8CCIntGetter { public: int get()const; };
class Rva0030C8E6IntGetter { public: int get()const; };
class Rva0030C900IntGetter { public: int get()const; };
class RenderObjClass { public: virtual void *Get_User_Data(); };
class Drawable; class Thing { public: Drawable *getDrawable()const; };
struct waveInfo { float finalWidth,finalHeight,distance,velocity; int fadeMs; float widthFraction,heightFraction; int compressMs,secondOffset; char *textureName,*typeName; };
// Zero Hour's per-type wave table, unchanged in BFME 2: retail 0x009B5C18 holds
// these five 44-byte entries and a zero WaveTypeStationary slot (WaveTypeMax 6),
// both texture pointers on one pooled "wave256.tga" literal.
waveInfo waveTypeInfo[6]= //TODO: Move this into INI
{
	{	28.0f,	18.0f,	25.0f,	0.018f,	900,	0.01f,	0.18f,	1500,	0,		"wave256.tga",	"Pond"},	//pond
	{	28.0f,	18.0f,	40.0f,	0.005f,	2000,	0.5f,	1.0f,	1000,	6267,	"wave256.tga",	"Ocean"},	//ocean
	{	55.0f,	36.0f,	80.0f,	0.015f,	2000,	0.05f,	0.18f,	1000,	6267,	"wave256.tga",	"Close Ocean"},	//close ocean
	{	55.0f,	36.0f,	80.0f,	0.015f,	4000,	0.01f,	0.18f,	2000,	6267,	"wave256.tga",	"Close Ocean Double"},	//close ocean double
	{	55.0f,	27.0f,	80.0f,	0.015f,	2000,	0.01f,	8.0f,	2000,	5367,	"wave256.tga",	"Radial"},	//radial
};
// The bounding sphere is a real SphereClass (its out-of-line copy is what the
// bounds getter calls); init() keeps the inline field-wise Init it was
// matched with.
struct InitSphere : SphereClass { void Init(const Vector3 &v,float r) {Center=v;Radius=r;} };
struct InitBox { Vector3 Center,Extent; };
class WaterTracksObj {
public:
 BFME2ParticleTextureHandle texture;
 InitSphere sphere; InitBox box;
 int type,x,y; bool bound; Vector2 startPos,waveDir,perpDir,initStart,initEnd;
 int initOffset,fadeMs,totalMs,elapsedMs;
 float initialWidth,initialHeight,finalWidth,peakFraction,finalHeight;
 float velocity,distance,timeToBeach,frontAcc,timeToStop,timeToRetreat,backAcc,timeToCompress,flipU;
 WaterTracksObj *next,*previous;
 void init(float,float,Vector2&,Vector2&,char*,int,void*);
 virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &out) const;
};
// Target FE440..FE488 evaluates cos before sin, then Y*cos + X*sin.
// Keep that arithmetic visible locally without changing the shared donor header.
static __forceinline void rotateInit(Vector2 &v,float angle)
{
 float c=WWMath::Cos(angle);float s=WWMath::Sin(angle);
 float x=v.X*c-v.Y*s;float y=v.Y*c+v.X*s;
 v.X=x;v.Y=y;
}
// Retail 0x000FE359 (16 bytes), the vftable slot after the destructor: the
// Zero Hour body, a SphereClass copy of the +0x08 bounds.
void WaterTracksObj::Get_Obj_Space_Bounding_Sphere(SphereClass &out) const
{
 out=sphere;
}
void WaterTracksObj::init(float width,float length,Vector2 &start,Vector2 &end,char *textureName,int timeOffset,void *settings)
{
 initStart=start;initEnd=end;initOffset=timeOffset;
 sphere.Init(Vector3(0,0,0),400);
 box.Center.Set(0,0,0);box.Extent.Set(400,400,1);
 x=2;y=2;elapsedMs=-initOffset;
 startPos=start;perpDir=waveDir=end-start;
 rotateInit(perpDir,-1.57079632679f);perpDir.Normalize();
 waveDir=perpDir;waveDir.Rotate(1.57079632679f);
 char *randomFile="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Water\\W3DWaterTracks.cpp";
 distance=settings?reinterpret_cast<Rva0030C934IntGetter*>(settings)->get():waveTypeInfo[type].distance;
 distance*=GetGameClientRandomValueReal(0.9f,1.1f,randomFile,219);
 waveDir*=distance;startPos-=waveDir;
 velocity=settings?reinterpret_cast<Rva0030C8CCIntGetter*>(settings)->get()*0.001f:waveTypeInfo[type].velocity;
 totalMs=distance/velocity;
 fadeMs=settings?reinterpret_cast<Rva0030C8E6IntGetter*>(settings)->get():waveTypeInfo[type].fadeMs;
 fadeMs*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,228);
 initialWidth=settings?reinterpret_cast<int>(reinterpret_cast<RenderObjClass*>(settings)->RenderObjClass::Get_User_Data())*0.01f:waveTypeInfo[type].widthFraction;
 initialWidth*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,231)*length;
 initialHeight=settings?reinterpret_cast<int>(reinterpret_cast<Thing*>(settings)->getDrawable())*0.01f:waveTypeInfo[type].heightFraction;
 initialHeight*=GetGameClientRandomValueReal(0.5f,1.0f,randomFile,233)*width;
 finalWidth=length*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,234);
 finalHeight=width*GetGameClientRandomValueReal(0.5f,1.1f,randomFile,235);
 frontAcc=-(velocity*velocity)/(2*finalHeight);
 timeToStop=-velocity/frontAcc;
 timeToBeach=(distance-finalHeight)/velocity;
 timeToRetreat=sqrt(fabs(2.0f*finalHeight/frontAcc));
 totalMs=timeToBeach+timeToStop+timeToRetreat;
 backAcc=(2.0f*initialHeight)/(timeToStop*timeToStop);
 timeToCompress=settings?reinterpret_cast<Rva0030C900IntGetter*>(settings)->get():waveTypeInfo[type].compressMs;
 timeToCompress*=GetGameClientRandomValueReal(0.5f,1.1f,randomFile,245);
 if(type==5) {timeToRetreat=1000;totalMs=timeToBeach+timeToStop+fadeMs+timeToRetreat;startPos=start;fadeMs=1000;}
 texture=TextureAsset::Get(textureName,0,0);
}
