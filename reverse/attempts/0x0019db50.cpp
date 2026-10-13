// ?Update_Obj_Space_Bounding_Volumes@HLodClass@@MAEXXZ
// partial score=0.9898779124713751 date=2026-10-13
// ?Update_Obj_Space_Bounding_Volumes@HLodClass@@MAEXXZ
// partial score=0.9899 date=2026-10-06
// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Update_Obj_Space_Bounding_Volumes, RVA19DB50, 2501B: near miss.
// Identity as the bank: HLod definition constructor 19FF2F and installed table
// 7D6780 slot114; OBBOX class1B / "BOUNDINGBOX" search then child sphere/box
// combine in base pose. Pivot transform is quaternion+translation at 30/40,
// stride 58; the rotation expansion is the Add_Lod_Model recovery.
// The loop-only pivotMatrixLoop uses a volatile q.X read to preserve retail's
// q.X then q.Y order for the xy product. Current explain: exact 2501B extent,
// 17 differing instruction rows, with the first remaining difference at
// +0x6A0 in tmpsphere.Transform register allocation. Not byte-verified progress.
// Similarity is measured on the relocation-patched byte sequence.
#define Matrix4x4 Matrix4
#include <sweep/winbase_shim.h>
#include <string.h>
#define _CRTIMP
#include "rendobj.h"
#include "winbase_shim.h"
#include "hlod.h"
#include "assetmgr.h"
#include "hmdldef.h"
#include "w3derr.h"
#include "chunkio.h"
#include "predlod.h"
class CameraClass;
#include "rinfo.h"
#include "sphere.h"
#include "boxrobj.h"

struct HlodTransformView
{
    float X, Y, Z, W;
    Vector3 Position;
};
struct HlodPivotView
{
    unsigned char unaccessed[0x30];
    HlodTransformView Transform;
    int Index;
    bool IsVisible;
    unsigned char tail[7];
};
typedef char HlodPivotStride[(sizeof(HlodPivotView) == 0x58) ? 1 : -1];
struct HlodTreeView
{
    char Name[16];
    int NumPivots; // +0x10
    HlodPivotView *Pivot; // +0x14
};
static __forceinline Matrix3D &pivotMatrix(const HlodTransformView &q, Matrix3D &m)
{
    const float xx = q.X * q.X * 2.0f;
    const float xy = q.X * q.Y * 2.0f;
    const float xz = q.Z * q.X * 2.0f;
    const float wx = q.W * q.X * 2.0f;
    const float yy = q.Y * q.Y * 2.0f;
    const float yz = q.Z * q.Y * 2.0f;
    const float wy = q.W * q.Y * 2.0f;
    const float zz = q.Z * q.Z * 2.0f;
    const float wz = q.W * q.Z * 2.0f;

    m[0][0] = 1.0f - yy - zz;
    m[0][1] = xy - wz;
    m[0][2] = xz + wy;
    m[1][0] = xy + wz;
    m[1][1] = 1.0f - zz - xx;
    m[1][2] = yz - wx;
    m[2][0] = xz - wy;
    m[2][1] = yz + wx;
    m[2][2] = 1.0f - yy - xx;
    m[0][3] = q.Position.X;
    m[1][3] = q.Position.Y;
    m[2][3] = q.Position.Z;
    return m;
}

static __forceinline Matrix3D &pivotMatrixLoop(const HlodTransformView &q, Matrix3D &m)
{
    const float xx = q.X * q.X * 2.0f;
    // Retail reloads q.X before multiplying the xy term by q.Y.
    const volatile float &x_for_xy = q.X;
    const float xy = x_for_xy * q.Y * 2.0f;
    const float xz = q.Z * q.X * 2.0f;
    const float wx = q.W * q.X * 2.0f;
    const float yy = q.Y * q.Y * 2.0f;
    const float yz = q.Z * q.Y * 2.0f;
    const float wy = q.W * q.Y * 2.0f;
    const float zz = q.Z * q.Z * 2.0f;
    const float wz = q.W * q.Z * 2.0f;

    m[0][0] = 1.0f - yy - zz;
    m[0][1] = xy - wz;
    m[0][2] = xz + wy;
    m[1][0] = xy + wz;
    m[1][1] = 1.0f - zz - xx;
    m[1][2] = yz - wx;
    m[2][0] = xz - wy;
    m[2][1] = yz + wx;
    m[2][2] = 1.0f - yy - xx;
    m[0][3] = q.Position.X;
    m[1][3] = q.Position.Y;
    m[2][3] = q.Position.Z;
    return m;
}

static __forceinline Matrix3D &treeMatrix(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrix(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
static __forceinline Matrix3D &treeMatrixB(const HTreeClass *tree, int index, Matrix3D &m) { const HlodTransformView &q = reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform; return pivotMatrix(q,m); }
static __forceinline Matrix3D &treeMatrixU(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrixLoop(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
{
	//
	//	Do we still have a valid bounding box index?
	//
	ModelArrayClass &high_lod = Lod[LodCount - 1];
	const int count = high_lod.Count ();
	if (	BoundingBoxIndex < 0 ||
			BoundingBoxIndex >= count ||
			high_lod[BoundingBoxIndex].Model->Class_ID () != RenderObjClass::CLASSID_OBBOX)
	{
		BoundingBoxIndex = -1;
	}

	//
	//	Attempt to find an OBBox mesh inside the heirarchy
	//
	unsigned int index = high_lod.Count ();
	while (index -- && BoundingBoxIndex == -1) {
		RenderObjClass *model = high_lod[index].Model;

		//
		//	Is this an OBBox mesh?
		//
		if (model->Class_ID () == RenderObjClass::CLASSID_OBBOX)
		{
			const char *name = model->Get_Name ();
			const char *name_seg = ::strchr (name, '.');
			if (NULL != name_seg) {
				name = name_seg + 1;
			}

			//
			//	Does the name match the designator we are looking for?
			//
			if (::stricmp (name, "BOUNDINGBOX") == 0) {
				BoundingBoxIndex = index;
			}
		}
	}


	RenderObjClass * robj = NULL;
	int i;

	// if we don't have any sub objects, just set default bounds
	if (Get_Num_Sub_Objects() <= 0) {
		ObjSphere.Init(Vector3(0,0,0),0);
		ObjBox.Center.Set(0,0,0);
		ObjBox.Extent.Set(0,0,0);
		return;
	}

	// loop through all sub-objects, combining their object-space bounding spheres and boxes.
	// Put our HTree in its base pose at the origin.
	AABoxClass obj_aabox;
	MinMaxAABoxClass box;
	SphereClass sphere;

	HTree->Base_Update(Matrix3D(1));

	WWASSERT(robj);
	robj = Get_Sub_Object(0);

	Matrix3D bonetm;
	treeMatrixB(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	sphere.Transform(bonetm);
	robj->Get_Obj_Space_Bounding_Box(obj_aabox);

	box.Init(obj_aabox);
	box.Transform(bonetm);

	robj->Release_Ref();

	for (i=1; i<Get_Num_Sub_Objects(); i++) {
		WWASSERT(robj);
		robj = Get_Sub_Object(i);

		Matrix3D bonetm;
	treeMatrixU(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);

		SphereClass tmpsphere;
		robj->Get_Obj_Space_Bounding_Sphere(tmpsphere);
		tmpsphere.Transform(bonetm);
		sphere.Add_Sphere(tmpsphere);

		AABoxClass tmpbox;
		robj->Get_Obj_Space_Bounding_Box(tmpbox);
		tmpbox.Transform(bonetm);
		box.Add_Box(tmpbox);

		robj->Release_Ref();
	}

	ObjSphere = sphere;
	ObjBox = box;

   Invalidate_Cached_Bounding_Volumes();
	Set_Hierarchy_Valid(false);

   // Now update the object space bounding volumes of this object's container:
   RenderObjClass *container = Get_Container();
   if (container) container->Update_Obj_Space_Bounding_Volumes();
}

// W7-ASTRA 2026-10-13: preserved best standalone2501B/.989878 bank after owner trials.
// Current scorer reports21 rows (older scorer17); normalized residue remains loop
// sphere center loads. Real owner is WW3D2/hlod.cpp, NOT picker neighbor TU.
// Owner integration needs donor-equivalent local MinMax Init/Add_Box/AABox Init,
// and base_tm.Make_Identity() to retain its rowed COMDAT. Exact-extent owner trial
// is2501B/36 rows/.979095;156/156 existing rows,19floats,1string,2imports PASS.
// A const-ref local sphere transform helper only in loop gives2505B/21rows;
// chain3,beam2,80 duplicate reads,64 operand variants,12 snapshots plateau.
// Owner patch below is evidence, not progress; earlier better bank above retained.
// OWNER-PATCH diff --git a/Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp b/Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp
// OWNER-PATCH index 9a1a6ecdbc..3ba37a77cd 100644
// OWNER-PATCH --- a/Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp
// OWNER-PATCH +++ b/Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp
// OWNER-PATCH @@ -3668,13 +3668,100 @@ void HLodClass::Get_Snap_Point(int index,Vector3 * set)
// OWNER-PATCH   *   1/26/00    gth : Created.                                                                 *
// OWNER-PATCH   *=============================================================================================*/
// OWNER-PATCH  // ?HLodClass::Update_Obj_Space_Bounding_Volumes present-unmatched
// OWNER-PATCH +struct HlodTransformView
// OWNER-PATCH +{
// OWNER-PATCH +    float X, Y, Z, W;
// OWNER-PATCH +    Vector3 Position;
// OWNER-PATCH +};
// OWNER-PATCH +struct HlodPivotView
// OWNER-PATCH +{
// OWNER-PATCH +    unsigned char unaccessed[0x30];
// OWNER-PATCH +    HlodTransformView Transform;
// OWNER-PATCH +    int Index;
// OWNER-PATCH +    bool IsVisible;
// OWNER-PATCH +    unsigned char tail[7];
// OWNER-PATCH +};
// OWNER-PATCH +typedef char HlodPivotStride[(sizeof(HlodPivotView) == 0x58) ? 1 : -1];
// OWNER-PATCH +struct HlodTreeView
// OWNER-PATCH +{
// OWNER-PATCH +    char Name[16];
// OWNER-PATCH +    int NumPivots; // +0x10
// OWNER-PATCH +    HlodPivotView *Pivot; // +0x14
// OWNER-PATCH +};
// OWNER-PATCH +static __forceinline Matrix3D &pivotMatrix(const HlodTransformView &q, Matrix3D &m)
// OWNER-PATCH +{
// OWNER-PATCH +    const float xx = q.X * q.X * 2.0f;
// OWNER-PATCH +    const float xy = q.X * q.Y * 2.0f;
// OWNER-PATCH +    const float xz = q.Z * q.X * 2.0f;
// OWNER-PATCH +    const float wx = (*(const volatile float *)&q.W) * q.X * 2.0f;
// OWNER-PATCH +    const float yy = q.Y * q.Y * 2.0f;
// OWNER-PATCH +    const float yz = q.Z * q.Y * 2.0f;
// OWNER-PATCH +    const float wy = q.W * q.Y * 2.0f;
// OWNER-PATCH +    const float zz = q.Z * q.Z * 2.0f;
// OWNER-PATCH +    const float wz = q.W * q.Z * 2.0f;
// OWNER-PATCH +
// OWNER-PATCH +    m[0][0] = 1.0f - yy - zz;
// OWNER-PATCH +    m[0][1] = xy - wz;
// OWNER-PATCH +    m[0][2] = xz + wy;
// OWNER-PATCH +    m[1][0] = xy + wz;
// OWNER-PATCH +    m[1][1] = 1.0f - zz - xx;
// OWNER-PATCH +    m[1][2] = yz - wx;
// OWNER-PATCH +    m[2][0] = xz - wy;
// OWNER-PATCH +    m[2][1] = yz + wx;
// OWNER-PATCH +    m[2][2] = 1.0f - yy - xx;
// OWNER-PATCH +    m[0][3] = q.Position.X;
// OWNER-PATCH +    m[1][3] = q.Position.Y;
// OWNER-PATCH +    m[2][3] = q.Position.Z;
// OWNER-PATCH +    return m;
// OWNER-PATCH +}
// OWNER-PATCH +
// OWNER-PATCH +static __forceinline Matrix3D &pivotMatrixLoop(const HlodTransformView &q, Matrix3D &m)
// OWNER-PATCH +{
// OWNER-PATCH +    const float xx = q.X * q.X * 2.0f;
// OWNER-PATCH +    // Retail reloads q.X before multiplying the xy term by q.Y.
// OWNER-PATCH +    const volatile float &x_for_xy = q.X;
// OWNER-PATCH +    const float xy = x_for_xy * q.Y * 2.0f;
// OWNER-PATCH +    const float xz = q.Z * q.X * 2.0f;
// OWNER-PATCH +    const float wx = q.W * q.X * 2.0f;
// OWNER-PATCH +    const float yy = q.Y * q.Y * 2.0f;
// OWNER-PATCH +    const float yz = q.Z * q.Y * 2.0f;
// OWNER-PATCH +    const float wy = q.W * q.Y * 2.0f;
// OWNER-PATCH +    const float zz = q.Z * q.Z * 2.0f;
// OWNER-PATCH +    const float wz = q.W * q.Z * 2.0f;
// OWNER-PATCH +
// OWNER-PATCH +    m[0][0] = 1.0f - yy - zz;
// OWNER-PATCH +    m[0][1] = xy - wz;
// OWNER-PATCH +    m[0][2] = xz + wy;
// OWNER-PATCH +    m[1][0] = xy + wz;
// OWNER-PATCH +    m[1][1] = 1.0f - zz - xx;
// OWNER-PATCH +    m[1][2] = yz - wx;
// OWNER-PATCH +    m[2][0] = xz - wy;
// OWNER-PATCH +    m[2][1] = yz + wx;
// OWNER-PATCH +    m[2][2] = 1.0f - yy - xx;
// OWNER-PATCH +    m[0][3] = q.Position.X;
// OWNER-PATCH +    m[1][3] = q.Position.Y;
// OWNER-PATCH +    m[2][3] = q.Position.Z;
// OWNER-PATCH +    return m;
// OWNER-PATCH +}
// OWNER-PATCH +
// OWNER-PATCH +static __forceinline Matrix3D &treeMatrix(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrix(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
// OWNER-PATCH +static __forceinline Matrix3D &treeMatrixB(const HTreeClass *tree, int index, Matrix3D &m) { const HlodTransformView &q = reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform; return pivotMatrix(q,m); }
// OWNER-PATCH +static __forceinline Matrix3D &treeMatrixU(const HTreeClass *tree, int index, Matrix3D &m) { return pivotMatrixLoop(reinterpret_cast<const HlodTreeView *>(tree)->Pivot[index].Transform,m); }
// OWNER-PATCH +// Donor WWMath/aabox.h operations kept local: owner header externalizes these for other bodies.
// OWNER-PATCH +struct HlodMinMaxBox : MinMaxAABoxClass {
// OWNER-PATCH + __forceinline void Init(const AABoxClass &b) { MinCorner=b.Center-b.Extent; MaxCorner=b.Center+b.Extent; }
// OWNER-PATCH + __forceinline void Add_Box(const AABoxClass &b) { if(b.Extent==Vector3(0,0,0))return; MinCorner.Update_Min(b.Center-b.Extent); MaxCorner.Update_Max(b.Center+b.Extent); }
// OWNER-PATCH +};
// OWNER-PATCH +static __forceinline void assignHlodAABox(AABoxClass &out,const MinMaxAABoxClass &b) {
// OWNER-PATCH + out.Center=(b.MaxCorner+b.MinCorner)*0.5f; out.Extent=(b.MaxCorner-b.MinCorner)*0.5f;
// OWNER-PATCH +}
// OWNER-PATCH  void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  {
// OWNER-PATCH  	//
// OWNER-PATCH  	//	Do we still have a valid bounding box index?
// OWNER-PATCH  	//
// OWNER-PATCH  	ModelArrayClass &high_lod = Lod[LodCount - 1];
// OWNER-PATCH -	int count = high_lod.Count ();
// OWNER-PATCH +	const int count = high_lod.Count ();
// OWNER-PATCH  	if (	BoundingBoxIndex < 0 ||
// OWNER-PATCH  			BoundingBoxIndex >= count ||
// OWNER-PATCH  			high_lod[BoundingBoxIndex].Model->Class_ID () != RenderObjClass::CLASSID_OBBOX)
// OWNER-PATCH @@ -3685,10 +3772,10 @@ void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  	//
// OWNER-PATCH  	//	Attempt to find an OBBox mesh inside the heirarchy
// OWNER-PATCH  	//
// OWNER-PATCH -	int index = high_lod.Count ();
// OWNER-PATCH +	unsigned int index = high_lod.Count ();
// OWNER-PATCH  	while (index -- && BoundingBoxIndex == -1) {
// OWNER-PATCH  		RenderObjClass *model = high_lod[index].Model;
// OWNER-PATCH -		
// OWNER-PATCH +
// OWNER-PATCH  		//
// OWNER-PATCH  		//	Is this an OBBox mesh?
// OWNER-PATCH  		//
// OWNER-PATCH @@ -3696,22 +3783,22 @@ void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  		{
// OWNER-PATCH  			const char *name = model->Get_Name ();
// OWNER-PATCH  			const char *name_seg = ::strchr (name, '.');
// OWNER-PATCH -			if (name_seg != NULL) {
// OWNER-PATCH +			if (NULL != name_seg) {
// OWNER-PATCH  				name = name_seg + 1;
// OWNER-PATCH  			}
// OWNER-PATCH  
// OWNER-PATCH  			//
// OWNER-PATCH  			//	Does the name match the designator we are looking for?
// OWNER-PATCH  			//
// OWNER-PATCH -			if (::stricmp (name, "BOUNDINGBOX") == 0) {				
// OWNER-PATCH +			if (::stricmp (name, "BOUNDINGBOX") == 0) {
// OWNER-PATCH  				BoundingBoxIndex = index;
// OWNER-PATCH  			}
// OWNER-PATCH  		}
// OWNER-PATCH  	}
// OWNER-PATCH  
// OWNER-PATCH  
// OWNER-PATCH -	int i;
// OWNER-PATCH  	RenderObjClass * robj = NULL;
// OWNER-PATCH +	int i;
// OWNER-PATCH  
// OWNER-PATCH  	// if we don't have any sub objects, just set default bounds
// OWNER-PATCH  	if (Get_Num_Sub_Objects() <= 0) {
// OWNER-PATCH @@ -3723,37 +3810,39 @@ void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  
// OWNER-PATCH  	// loop through all sub-objects, combining their object-space bounding spheres and boxes.
// OWNER-PATCH  	// Put our HTree in its base pose at the origin.
// OWNER-PATCH -	SphereClass sphere;
// OWNER-PATCH  	AABoxClass obj_aabox;
// OWNER-PATCH -	MinMaxAABoxClass box;
// OWNER-PATCH +	HlodMinMaxBox box;
// OWNER-PATCH +	SphereClass sphere;
// OWNER-PATCH  
// OWNER-PATCH  	{ Matrix3D base_tm; base_tm.Make_Identity(); HTree->Base_Update(base_tm); }
// OWNER-PATCH -	
// OWNER-PATCH -	robj = Get_Sub_Object(0);
// OWNER-PATCH +
// OWNER-PATCH  	WWASSERT(robj);
// OWNER-PATCH -	
// OWNER-PATCH -	const Matrix3D & bonetm = HTree->Get_Transform(Get_Sub_Object_Bone_Index(robj));
// OWNER-PATCH +	robj = Get_Sub_Object(0);
// OWNER-PATCH +
// OWNER-PATCH +	Matrix3D bonetm;
// OWNER-PATCH +	treeMatrixB(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);
// OWNER-PATCH  	robj->Get_Obj_Space_Bounding_Sphere(sphere);
// OWNER-PATCH  	sphere.Transform(bonetm);
// OWNER-PATCH  	robj->Get_Obj_Space_Bounding_Box(obj_aabox);
// OWNER-PATCH -	
// OWNER-PATCH +
// OWNER-PATCH  	box.Init(obj_aabox);
// OWNER-PATCH  	box.Transform(bonetm);
// OWNER-PATCH  
// OWNER-PATCH  	robj->Release_Ref();
// OWNER-PATCH  
// OWNER-PATCH  	for (i=1; i<Get_Num_Sub_Objects(); i++) {
// OWNER-PATCH -		robj = Get_Sub_Object(i);
// OWNER-PATCH  		WWASSERT(robj);
// OWNER-PATCH -		
// OWNER-PATCH -		const Matrix3D & bonetm = HTree->Get_Transform(Get_Sub_Object_Bone_Index(robj));
// OWNER-PATCH -		
// OWNER-PATCH +		robj = Get_Sub_Object(i);
// OWNER-PATCH +
// OWNER-PATCH +		Matrix3D bonetm;
// OWNER-PATCH +	treeMatrixU(HTree, Get_Sub_Object_Bone_Index(robj), bonetm);
// OWNER-PATCH +
// OWNER-PATCH  		SphereClass tmpsphere;
// OWNER-PATCH  		robj->Get_Obj_Space_Bounding_Sphere(tmpsphere);
// OWNER-PATCH  		tmpsphere.Transform(bonetm);
// OWNER-PATCH  		sphere.Add_Sphere(tmpsphere);
// OWNER-PATCH  
// OWNER-PATCH -		AABoxClass tmpbox; 
// OWNER-PATCH +		AABoxClass tmpbox;
// OWNER-PATCH  		robj->Get_Obj_Space_Bounding_Box(tmpbox);
// OWNER-PATCH  		tmpbox.Transform(bonetm);
// OWNER-PATCH  		box.Add_Box(tmpbox);
// OWNER-PATCH @@ -3762,7 +3851,7 @@ void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  	}
// OWNER-PATCH  
// OWNER-PATCH  	ObjSphere = sphere;
// OWNER-PATCH -	ObjBox = box;
// OWNER-PATCH +	assignHlodAABox(ObjBox,box);
// OWNER-PATCH  
// OWNER-PATCH     Invalidate_Cached_Bounding_Volumes();
// OWNER-PATCH  	Set_Hierarchy_Valid(false);
// OWNER-PATCH @@ -3773,6 +3862,7 @@ void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
// OWNER-PATCH  }
// OWNER-PATCH  
// OWNER-PATCH  
// OWNER-PATCH +
// OWNER-PATCH  /***********************************************************************************************
// OWNER-PATCH   * HLodClass::Add_Lod_Model -- adds a model to one of the lods                                 *
// OWNER-PATCH   *                                                                                             *
