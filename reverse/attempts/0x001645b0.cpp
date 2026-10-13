// ?Blend_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimClass@@M1MM@Z
// partial score=0.5856347628183083 date=2026-10-13
// Provenance: ZH HTreeClass::Blend_Update and BFME1 htree.cpp at
// cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 provide animation blend semantics.
// Target0x1645B0..0x165818 RET24 proves two paths, frame0xA0, native0x58 pivots,
// 24-byte compressed node records at HAnim+0x58 and six channel slots.
// The native first-animation Class_ID==1 path uses stream-channel cursor state;
// target fallback calls virtual translation/orientation/visibility/fade.
// Quaternion+translation transform replaces donor Matrix3D pivot storage.
// BFME2MotionChannel declaration follows existing stream-channel owner.
// Capture_Update0x1622B0 remains banked; its preexisting pin resolves this trial.
// Current source has no new pins, globals, asm, or optimizer pragmas.
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
// Target0x1645B0,4712B Blend_Update; ZH algorithm plus native compressed channel path.
class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 &operator=(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
 float X, Y, Z;
};

__forceinline Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

class Matrix3D
{
public:
	float Row[3][4];
};

class Quaternion
{
public:
	Quaternion() {}
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	Quaternion &operator=(const Quaternion &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
 float X, Y, Z, W;
};

__forceinline Vector3 Rotate_Vector(const Vector3 &v, const Quaternion &q)
{
	float x = (v.Z*q.Y - q.Z*v.Y) + q.W*v.X;
	float y = q.W*v.Y - (v.Z*q.X - q.Z*v.X);
	float z = (q.X*v.Y - v.X*q.Y) + v.Z*q.W;
	float w = -((v.X*q.X + v.Z*q.Z) + v.Y*q.Y);

	return Vector3
	(
		(z*q.Y - q.Z*y) + (q.W*x - q.X*w),
		(q.W*y - w*q.Y) - (q.X*z - q.Z*x),
		(q.X*y - x*q.Y) + (q.W*z - q.Z*w)
	);
}


__forceinline Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
	return Quaternion
	(
		a.W*b.X + b.W*a.X + (a.Y*b.Z - b.Y*a.Z),
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		a.W*b.Z + b.W*a.Z + (a.X*b.Y - b.X*a.Y),
		a.W*b.W - (a.X*b.X + a.Y*b.Y + a.Z*b.Z)
	);
}

Quaternion Build_Quaternion(const Matrix3D &mat);

// BFME 2 pivot transform: rotation quaternion plus translation.
struct PivotTransform
{
	Quaternion Rotation;
	Vector3 Translation;
};

__forceinline PivotTransform operator * (const PivotTransform &parent, const PivotTransform &child)
{
	PivotTransform result;
	result.Translation = Rotate_Vector(child.Translation, parent.Rotation) + parent.Translation;
	result.Rotation = parent.Rotation * child.Rotation;
	return result;
}

struct PivotClass
{
	char Name[16];
	PivotClass *Parent;					// +0x10
	PivotTransform BaseTransform;		// +0x14
	PivotTransform Transform;			// +0x30
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};


void BFME2_Nlerp(Quaternion &,const Quaternion &,const Quaternion &,float);
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass &); virtual ~BFME2MotionChannel(); virtual int UnknownSlot2();
 virtual void UnknownSlot3(float,float *,unsigned char **);
 virtual void UnknownSlot4(float,Vector3 *,unsigned char **); virtual void UnknownSlot5(float,Quaternion *,unsigned char **);
 virtual int UnknownSlot6();
 int Type,Pivot,Count,Components;
};
struct BlendNodeMotion {BFME2MotionChannel *X,*Y,*Z,*Q,*Fade;void *Vis;};
class HAnimClass {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual void Get_Translation(Vector3 &,int,float);
 virtual bool Get_Orientation(Quaternion &,int,float);
 virtual void slot10(); virtual bool Get_Visibility(int,float); virtual float Get_Fade(int,float);
 virtual int Get_Num_Pivots();
 virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
 virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual int Get_Class_ID();
 char pad[0x54]; BlendNodeMotion *Nodes;
};
class Rva00160FC0Input;
class Rva00160FC0 {public:void rva00160FC0(Rva00160FC0Input*);};
class HTreeClass {
public:
 void Blend_Update(const Matrix3D &,HAnimClass *,float,HAnimClass *,float,float);
 int Capture_Update(int);
 char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;
 struct CapturedBone{int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 CapturedBone *CapturedBegin,*CapturedEnd,*CapturedCapacity;
 HAnimClass *CachedMotion;unsigned char *ChannelCache;int CacheCapacity;
};

void HTreeClass::Blend_Update(const Matrix3D &root,HAnimClass *motion0,float frame0,HAnimClass *motion1,float frame1,float percentage){

 if(motion0->Get_Class_ID()==1 && motion0->Nodes){

  BlendNodeMotion *nodeMotion=motion0->Nodes;

  ((Rva00160FC0*)this)->rva00160FC0((Rva00160FC0Input*)motion0);


 PivotTransform &initial=Pivot[0].Transform;

 initial.Rotation=Build_Quaternion(root);

 initial.Translation.X=root.Row[0][3];

 initial.Translation.Y=root.Row[1][3];

 initial.Translation.Z=root.Row[2][3];

 Pivot[0].IsVisible=true;
Pivot[0].m_bfme54=1.0f;


  unsigned char *cache=ChannelCache;

  int num_anim_pivots=motion0->Get_Num_Pivots()<motion1->Get_Num_Pivots()?motion0->Get_Num_Pivots():motion1->Get_Num_Pivots();

  int captured=CapturedBegin==CapturedEnd?-1:CapturedBegin->Index;

  ++nodeMotion;

  for(int piv_idx=1;
piv_idx<NumPivots;
++piv_idx,++nodeMotion){


   PivotClass * volatile pivot = &Pivot[piv_idx];

   const PivotTransform &parent=pivot->Parent->Transform;

   pivot->Transform.Translation=parent.Translation+Rotate_Vector(pivot->BaseTransform.Translation,parent.Rotation);

   pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;

   if(piv_idx<num_anim_pivots){


    Vector3 trans0,trans1;

    if(nodeMotion->X)__vref(nodeMotion->X)->UnknownSlot3(frame0,&trans0.X,&cache);
else trans0.X=0;

    if(nodeMotion->Y)nodeMotion->Y->UnknownSlot3(frame0,&trans0.Y,&cache);
else trans0.Y=0;

    if(nodeMotion->Z)nodeMotion->Z->UnknownSlot3(frame0,&trans0.Z,&cache);
else trans0.Z=0;

    motion1->Get_Translation(trans1,piv_idx,frame1);


    PivotTransform local;

    Vector3 &trans=local.Translation;

    trans=Vector3((trans1.X-trans0.X)*percentage+trans0.X,(trans1.Y-trans0.Y)*percentage+trans0.Y,(trans1.Z-trans0.Z)*percentage+trans0.Z);

    trans.X*=ScaleFactor;
trans.Y*=ScaleFactor;
trans.Z*=ScaleFactor;

    Quaternion q0,q1;


    bool got0=nodeMotion->Q!=0;

    if(got0)nodeMotion->Q->UnknownSlot5(frame0,&q0,&cache);


    bool got1=motion1->Get_Orientation(q1,piv_idx,frame1);

    if(!got0 && !got1){

      pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;

    }
else{

      if(!got0)q0=Quaternion(0,0,0,1);

      if(!got1)q1=Quaternion(0,0,0,1);

      BFME2_Nlerp(local.Rotation,q0,q1,percentage);

      pivot->Transform.Translation=Rotate_Vector(local.Translation,pivot->Transform.Rotation)+pivot->Transform.Translation;

      pivot->Transform.Rotation=pivot->Transform.Rotation*local.Rotation;

    }


    float fade0;

    if(nodeMotion->Fade)nodeMotion->Fade->UnknownSlot3(frame0,&fade0,&cache);
else fade0=1.0f;

    pivot->m_bfme54=fade0+(motion1->Get_Fade(piv_idx,frame1)-fade0)*percentage;


    pivot->IsVisible=motion0->Get_Visibility(piv_idx,frame0)||motion1->Get_Visibility(piv_idx,frame1);


   }

   if(piv_idx==captured)captured=Capture_Update(piv_idx);


  }

 }
else{

  CachedMotion=0;


 PivotTransform &initial=Pivot[0].Transform;

 initial.Rotation=Build_Quaternion(root);

 initial.Translation.X=root.Row[0][3];

 initial.Translation.Y=root.Row[1][3];

 initial.Translation.Z=root.Row[2][3];

 Pivot[0].IsVisible=true;
Pivot[0].m_bfme54=1.0f;


  int num_anim_pivots=motion0->Get_Num_Pivots()<motion1->Get_Num_Pivots()?motion0->Get_Num_Pivots():motion1->Get_Num_Pivots();

  int captured=CapturedBegin==CapturedEnd?-1:CapturedBegin->Index;

  for(int piv_idx=1;
piv_idx<NumPivots;
++piv_idx){


   PivotClass *pivot=&Pivot[piv_idx];

   const PivotTransform &parent=pivot->Parent->Transform;

   pivot->Transform.Translation=parent.Translation+Rotate_Vector(pivot->BaseTransform.Translation,parent.Rotation);

   pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;

   if(piv_idx<num_anim_pivots){


    Vector3 trans0,trans1;

    motion0->Get_Translation(trans0,piv_idx,frame0);
motion1->Get_Translation(trans1,piv_idx,frame1);


    PivotTransform local;

    Vector3 &trans=local.Translation;

    trans=Vector3((trans1.X-trans0.X)*percentage+trans0.X,(trans1.Y-trans0.Y)*percentage+trans0.Y,(trans1.Z-trans0.Z)*percentage+trans0.Z);

    if(ScaleFactor!=1.0f){
trans.X*=ScaleFactor;
trans.Y*=ScaleFactor;
trans.Z*=ScaleFactor;
}

    Quaternion q0,q1;


    bool got0=motion0->Get_Orientation(q0,piv_idx,frame0);


    bool got1=motion1->Get_Orientation(q1,piv_idx,frame1);

    if(!got0 && !got1){

      pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;

    }
else{

      if(!got0)q0=Quaternion(0,0,0,1);

      if(!got1)q1=Quaternion(0,0,0,1);

      BFME2_Nlerp(local.Rotation,q0,q1,percentage);

      pivot->Transform.Translation=Rotate_Vector(local.Translation,pivot->Transform.Rotation)+pivot->Transform.Translation;

      pivot->Transform.Rotation=pivot->Transform.Rotation*local.Rotation;

    }


    pivot->IsVisible=motion0->Get_Visibility(piv_idx,frame0)||motion1->Get_Visibility(piv_idx,frame1);


    float fade1=motion1->Get_Fade(piv_idx,frame1);
float fade0=motion0->Get_Fade(piv_idx,frame0);

    pivot->m_bfme54=fade0+(fade1-fade0)*percentage;


   }

   if(piv_idx==captured)captured=Capture_Update(piv_idx);


  }

 }

}

