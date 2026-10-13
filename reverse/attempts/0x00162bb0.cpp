// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimClass@@M@Z
// partial score=0.5535265037759391 date=2026-10-14
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
// HTreeClass::Anim_Update, native0x162BB0..0x163A79 RET12.
// ZH/BF1 htree.cpp at cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 supplies the algorithm.
// Native proves58-byte quaternion/translation pivots, two paths and channel cursor state.
// Complete3783/3785-byte bank; large register and scheduling residue remains.
// Capture_Update1622B0 is still unrowed; its preexisting pin resolves this trial.
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
class TimeCodedBitChannelClass {public:int Get_Bit(int);};
struct BlendNodeMotion {BFME2MotionChannel *X,*Y,*Z,*Q,*Fade;TimeCodedBitChannelClass *Vis;};
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
 void Anim_Update(const Matrix3D &,HAnimClass *,float);
 int Capture_Update(int);
 char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;
 struct CapturedBone{int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 CapturedBone *CapturedBegin,*CapturedEnd,*CapturedCapacity;
 HAnimClass *CachedMotion;unsigned char *ChannelCache;int CacheCapacity;
};


void HTreeClass::Anim_Update(const Matrix3D &root,HAnimClass *motion,float frame) {
 if(motion->Get_Class_ID()==1 && motion->Nodes) {
  BlendNodeMotion *nodes=motion->Nodes;
  ((Rva00160FC0*)this)->rva00160FC0((Rva00160FC0Input*)motion);
  PivotTransform &initial=Pivot[0].Transform;
  initial.Rotation=Build_Quaternion(root);
  initial.Translation.X=root.Row[0][3];initial.Translation.Y=root.Row[1][3];initial.Translation.Z=root.Row[2][3];
  Pivot[0].IsVisible=true;Pivot[0].m_bfme54=1.0f;
  unsigned char *cache=ChannelCache;
  int count=motion->Get_Num_Pivots();
  int captured=CapturedBegin==CapturedEnd?-1:CapturedBegin->Index;
  BlendNodeMotion *node=nodes+1;
  for(int piv_idx=1;piv_idx<NumPivots;++piv_idx,++node) {
   PivotClass *pivot=&Pivot[piv_idx];
   const PivotTransform &parent=pivot->Parent->Transform;
   pivot->Transform.Translation=parent.Translation+Rotate_Vector(pivot->BaseTransform.Translation,parent.Rotation);
   pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;
   if(piv_idx<count) {
    const float scale=ScaleFactor;
    Vector3 trans;
    if(node->X)__vref(node->X)->UnknownSlot3(frame,&trans.X,&cache);else trans.X=0;
    if(node->Y)node->Y->UnknownSlot3(frame,&trans.Y,&cache);else trans.Y=0;
    if(node->Z)node->Z->UnknownSlot3(frame,&trans.Z,&cache);else trans.Z=0;
    trans.X*=scale;trans.Y*=scale;trans.Z*=scale;
    Quaternion rotation;
    bool gotRotation=node->Q!=0;
    if(gotRotation)node->Q->UnknownSlot5(frame,&rotation,&cache);
    if(gotRotation) {
     pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
     pivot->Transform.Rotation=pivot->Transform.Rotation*rotation;
    } else {
     pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
    }
    if(node->Fade)node->Fade->UnknownSlot3(frame,&pivot->m_bfme54,&cache);else pivot->m_bfme54=1.0f;
    pivot->IsVisible=node->Vis?node->Vis->Get_Bit((int)frame)!=0:true;
   }
   if(piv_idx==captured)captured=Capture_Update(piv_idx);
  }
 } else {
  CachedMotion=0;
  PivotTransform &initial=Pivot[0].Transform;
  initial.Rotation=Build_Quaternion(root);
  initial.Translation.X=root.Row[0][3];initial.Translation.Y=root.Row[1][3];initial.Translation.Z=root.Row[2][3];
  Pivot[0].IsVisible=true;Pivot[0].m_bfme54=1.0f;
  int count=motion->Get_Num_Pivots();
  int captured=CapturedBegin==CapturedEnd?-1:CapturedBegin->Index;
  for(int piv_idx=1;piv_idx<NumPivots;++piv_idx) {
   PivotClass *pivot=&Pivot[piv_idx];
   const PivotTransform &parent=pivot->Parent->Transform;
   pivot->Transform.Translation=parent.Translation+Rotate_Vector(pivot->BaseTransform.Translation,parent.Rotation);
   pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;
   if(piv_idx<count) {
    Vector3 trans; motion->Get_Translation(trans,piv_idx,frame);
    if(ScaleFactor!=1.0f){trans.X*=ScaleFactor;trans.Y*=ScaleFactor;trans.Z*=ScaleFactor;}
    Quaternion rotation;
    bool gotRotation=motion->Get_Orientation(rotation,piv_idx,frame);
    if(gotRotation) {
     pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
     pivot->Transform.Rotation=pivot->Transform.Rotation*rotation;
    } else {
     pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
    }
    pivot->IsVisible=motion->Get_Visibility(piv_idx,frame);
    pivot->m_bfme54=motion->Get_Fade(piv_idx,frame);
   }
   if(piv_idx==captured)captured=Capture_Update(piv_idx);
  }
 }
}
