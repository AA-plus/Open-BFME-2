// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?getModelVertices@W3DBridge@@IAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z,
// retail 0x000DDE13..0x000DE2AE (1179B), thiscall ret 0x28.
//
// Zero Hour's W3DBridge::getModelVertices in its BFME 2 form: an 8000-vertex
// cap, the normal array from MeshGeometryClass::Get_Vertex_Normal_Array,
// the UVs copied first, the rotated model normal stored in the vertex before
// the bridge-space normal is built and lit through the six-argument
// BaseHeightMapRenderObjClass::doTheLight (alpha 1, skip-first-light true).
//
// Evidence (target): native body 0x000DDE13 with its sole fixed-bridge
// caller getModelVerticesFixed 0x000DE2AE and the span loop of
// getIndicesNVertices 0x000DF11E; callees are the matched
// Get_Vertex_Normal_Array 0x0016AB90, MeshMatDescClass::Get_UV_Array_By_Index
// 0x000D1F40, WWMath::Inv_Sqrt 0x0004233A and doTheLight 0x000694A3. Retail
// builds this body /G7 while its neighbours in
// W3DBridgeGetModelVerticesFixed.cpp are /O1 without /G7, so it lives in its
// own unit. Semantic donors: ZH and BFME 1 W3DBridgeBuffer.cpp.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;

#include "../../../../../reference/shims/wwmath/Vector2.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"



class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline Vector3() {}
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }

	__forceinline Real Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		Real len2 = Length2();
		if (len2 != 0.0f)
		{
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	// Declared here, defined out of class as in WWMath vector3.h: in-class
	// friend bodies shift cl's SSE operand tie-breaks in the vertex blend.
	__forceinline friend Vector3 operator * (float k, const Vector3 &a);
	__forceinline friend Vector3 operator + (const Vector3 &a, const Vector3 &b);
};

__forceinline Vector3 operator * (float k, const Vector3 &a)
{
	return Vector3((a.X * k),(a.Y * k),(a.Z * k));
}

__forceinline Vector3 operator + (const Vector3 &a,const Vector3 &b)
{
	return Vector3(
		a.X+b.X,
		a.Y+b.Y,
		a.Z+b.Z
	);
}

class Vector4
{
public:
	Real X, Y, Z, W;
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
};

class Matrix3D
{
public:
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }

	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) { tmp = in; v = &tmp; } else { v = (Vector3 *)&in; }
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	static __forceinline void Rotate_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) { tmp = in; v = &tmp; } else { v = (Vector3 *)&in; }
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z);
	}
	Vector4 Row[3];
};


struct VertexFormatXYZDUV2
{
	Real x, y, z;
	unsigned int diffuse;
	Real u1, v1, u2, v2;
};
typedef VertexFormatXYZDUV2 VERTEX_FORMAT;

struct VertexFormatXYZNDUV1
{
	Real x, y, z;
	Real nx, ny, nz;
	unsigned int diffuse;
	Real u1, v1;
};

class RenderObjClass;
template <class ObjectType> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

template <class T> class ShareBufferClass
{
public:
	__forceinline T *Get_Array() { return Array; }
private:
	char m_pad00[0x0C];
	T *Array;				// +0x0C
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array_By_Index(Int index, Bool create);
};

class MeshGeometryClass
{
public:
	__forceinline Int Get_Vertex_Count() const { return VertexCount; }
	__forceinline Vector3 *Get_Vertex_Array() { return Vertex->Get_Array(); }
	const Vector3 *Get_Vertex_Normal_Array(Bool create);
private:
	char m_pad00[0x28];
	Int VertexCount;			// +0x28
	char m_pad2C[0x30 - 0x2C];
	ShareBufferClass<Vector3> *Vertex;	// +0x30
};

class MeshModelClass : public MeshGeometryClass
{
public:
	__forceinline const Vector2 *Get_UV_Array_By_Index(Int index) { return CurMatDesc->Get_UV_Array_By_Index(index, false); }
private:
	char m_pad34[0x94 - 0x34];
	MeshMatDescClass *CurMatDesc;		// +0x94
};

class MeshClass
{
public:
	__forceinline MeshModelClass *Peek_Model() { return Model; }
private:
	char m_pad00[0xC4];
	MeshModelClass *Model;			// +0xC4
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct BridgeLightingGlobals
{
	char m_pad000[0x920];
	Coord3D m_terrainLightPos[3];		// +0x920
	char m_pad944[0x988 - 0x944];
	Int m_numGlobalLights;			// +0x988
};
#define TheGlobalLighting ((const BridgeLightingGlobals *)TheWritableGlobalData)

class BaseHeightMapRenderObjClass
{
public:
	void doTheLight(VERTEX_FORMAT *vb, Vector3 *light, Vector3 *normal, RefRenderObjListIterator *pLightsIterator, UnsignedByte alpha, Bool skipFirstLight);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DBridge
{
protected:
	Int getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
		Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
		const Matrix3D &mtx, MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator);

	Vector3 m_start;			// +0x00
};

Int W3DBridge::getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
																Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
																const Matrix3D &mtx,
																MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == 0)
		return(0);

	Int i;
	MeshModelClass *model = pMesh->Peek_Model();
	Int numVertex = model->Get_Vertex_Count();
	Vector3 *pVert = model->Get_Vertex_Array();
	const Vector3 *pNormal = model->Get_Vertex_Normal_Array(false);

	// If we happen to have too many bridges, stop.
	if (curVertex + numVertex + 2 >= 8000) {
		return(0);
	}

	Vector3 lightRay[3];
	const Coord3D *lightPos;

	for (Int lightIndex = 0; lightIndex < TheGlobalLighting->m_numGlobalLights; lightIndex++)
	{
		lightPos = &TheGlobalLighting->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].Set(-lightPos->x, -lightPos->y, -lightPos->z);
		lightRay[lightIndex].Normalize();
	}

	const Vector2 *uvs = pMesh->Peek_Model()->Get_UV_Array_By_Index(0);
	VertexFormatXYZNDUV1 *curVb = destination_vb + curVertex;

	for (i = 0; i < numVertex; i++) {
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;

		Vector3 vLoc;
		Vector3 vertex;
		Matrix3D::Transform_Vector(mtx, pVert[i], &vertex);
		vLoc = (vertex.X + xOffset) * vec + vertex.Y * vecNormal + vertex.Z * vecZ;

		vLoc.X += m_start.X;
		vLoc.Y += m_start.Y;
		vLoc.Z += m_start.Z;

		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;

		VERTEX_FORMAT vb;
		vb.x = vLoc.X;
		vb.y = vLoc.Y;
		vb.z = vLoc.Z;

		Vector3 normal;
		Matrix3D::Rotate_Vector(mtx, pNormal[i], &normal);
		// The three named locals are load-bearing: they move cl's tie-break for
		// the inlined Transform_Vector / Rotate_Vector sums to retail's.
		Real nx = normal.X;
		Real ny = normal.Y;
		Real nz = normal.Z;
		curVb->nx = nx;
		curVb->ny = ny;
		curVb->nz = nz;
		curVb->diffuse = 0xFF000000;
		normal = normal.X * vec + normal.Y * vecNormal + normal.Z * vecZ;
		normal.Normalize();
		TheTerrainRenderObject->doTheLight(&vb, lightRay, &normal, 0, 1, true);
		curVb->diffuse = vb.diffuse | 0xFF000000;
		curVb++;
	}
	return(numVertex);
}
