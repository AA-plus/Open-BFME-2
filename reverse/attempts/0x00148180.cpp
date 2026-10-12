// ?Add_Mesh@DX8RigidFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z
// partial score=0.8 date=2026-10-12
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Semantic donor ZH dx8renderer.cpp Add_Mesh, BFME1 revision9cbfb551fe20.
// WB9D97D0 confirms target148180 identity and source1010..1024. Native
//148180..148517 RET4 proves extended96B FVF descriptor, vertex bufferE8,
//used verticesEC, FVF D8, sortingE4; all called providers already matched.
// 2026-10-12: providers now use the matched inline shapes (MeshMatDescClass
// Get_UV_Array_By_Index/Get_UV_Array/Get_Color_Array, real noinline
// MeshGeometryClass::Get_Vertex_Normal_Array(false) at 0x16AB90); UV loop now
// strength-reduces/counts down like retail. Residue: retail keeps
// split_table.mmc in ebp across new/VB ctors/AppendLock/normals (this in esi,
// zero CSE in edi, i homed at 0x3c below split_table); MSVC here reloads the
// field after every call (const member, visible ctor, /Oa /Ow tried: no).
#include <new>
class Vector2 {public:float X,Y;};
class Vector3 {public:float X,Y,Z;Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}};
template <class T> class ShareBufferClass {public:virtual void Delete_This();T *Get_Array(){return m_array;}protected:int m_refs;T *m_rawBuffer;T *m_array;int m_count;int m_alignment;};
class MeshMatDescClass {
public:
 Vector2 *Get_UV_Array(int pass,int stage){
  if(UVSource[pass][stage]==-1)return 0;
  if(UV[UVSource[pass][stage]]!=0)return UV[UVSource[pass][stage]]->Get_Array();
  return 0;
 }
 Vector2 *Get_UV_Array_By_Index(int index,bool create){
  if(create && !UV[index])UV[index]=0;
  if(!create && m_unknown0C!=0 && index<2)return Get_UV_Array(0,index);
  if(UV[index])return UV[index]->Get_Array();
  return 0;
 }
 unsigned *Get_Color_Array(int index,bool create){
  if(create && !ColorArray[index])ColorArray[index]=0;
  if(ColorArray[index])return ColorArray[index]->Get_Array();
  return 0;
 }
 int PassCount,VertexCount,PolyCount,m_unknown0C;
 ShareBufferClass<Vector2> *UV[8];
 int UVSource[4][2];
 ShareBufferClass<unsigned> *ColorArray[2];
};
class MeshGeometryClass {public:__declspec(noinline) const Vector3 *Get_Vertex_Normal_Array(bool);
 char pad[0x28];unsigned VertexCount;void *Poly;ShareBufferClass<Vector3> *Vertex;
 unsigned Get_Vertex_Count()const{return VertexCount;}
 const Vector3*Get_Vertex_Array()const{return Vertex->Get_Array();}
};
class MeshModelClass:public MeshGeometryClass {
public:
 char gap34[0x60];MeshMatDescClass *CurMatDesc;
 unsigned *Get_Color_Array(int index,bool create=true){return CurMatDesc->Get_Color_Array(index,create);}
 Vector2 *Get_UV_Array_By_Index(int index,bool create=false){return CurMatDesc->Get_UV_Array_By_Index(index,create);}
};
class Vertex_Split_Table {
public:
 MeshModelClass *model;bool npatch;unsigned count;void *polygons;bool allocated;
 Vertex_Split_Table(MeshModelClass*);
 ~Vertex_Split_Table(){if(allocated)delete[](unsigned short*)polygons;}
 unsigned Get_Vertex_Count()const{return model->Get_Vertex_Count();}
 const Vector3 *Get_Vertex_Array()const{return model->Get_Vertex_Array();}
 const Vector3 *Get_Vertex_Normal_Array()const{return model->Get_Vertex_Normal_Array(false);}
 const unsigned*Get_Color_Array(unsigned index)const{return model->Get_Color_Array(index,false);}
 const Vector2*Get_UV_Array(unsigned uv_array_index)const{return model->Get_UV_Array_By_Index(uv_array_index);}
};
struct S2FVFInfo {
 unsigned fvf;bool basis;unsigned count,stride,location,extension,normal,extensionEnd,blend,tex[8],diffuse,specular,basisOffset,basisSecond,basisEnd,extensionData,formatIndex;
 unsigned Get_FVF_Size()const{return stride;}unsigned Get_Location_Offset()const{return location;}unsigned Get_Normal_Offset()const{return normal;}
 unsigned Get_Diffuse_Offset()const{return diffuse;}unsigned Get_Specular_Offset()const{return specular;}unsigned Get_Tex_Offset(unsigned n)const{return tex[n];}
};
class BfmeDynamicVBBase {public:virtual ~BfmeDynamicVBBase();char pad[16];S2FVFInfo *format;char tail[4];const S2FVFInfo&FVF_Info()const{return *format;}};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {public:BfmeDynamicSortingVB(unsigned short);void *buffer;};
class BfmeDynamicNativeVB:public BfmeDynamicVBBase {public:BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);void *buffer;};
class VertexBufferClass {public:class AppendLockClass {public: void *owner,*vertices;char lock;AppendLockClass(VertexBufferClass*,unsigned,unsigned,int);~AppendLockClass();void *Get_Vertex_Array()const{return vertices;}};};
class DX8Caps {public:char pad[0x13b];bool npatches;bool Support_NPatches()const{return npatches;}};
class DX8Wrapper {public:static DX8Caps *Get_Current_Caps(){return CurrentCaps;}private:static DX8Caps *CurrentCaps;};
class WW3D {public:static unsigned Get_NPatches_Level(){return NPatchesLevel;}private:static unsigned NPatchesLevel;};
class DX8FVFCategoryContainer {
public:
 virtual ~DX8FVFCategoryContainer();char pad[0xD0-4];void *index;unsigned used_indices,FVF;char gapDC[8];bool sorting;
 void Generate_Texture_Categories(Vertex_Split_Table&,unsigned);
};
class DX8RigidFVFCategoryContainer:public DX8FVFCategoryContainer {
public:
 BfmeDynamicVBBase*vertex_buffer;unsigned used_vertices;
 virtual void Add_Mesh(MeshModelClass*);
};
typedef char FVFSize[(sizeof(S2FVFInfo)==96)?1:-1];
typedef char BaseSize[(sizeof(DX8FVFCategoryContainer)==0xe8)?1:-1];
typedef char VBSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
void DX8RigidFVFCategoryContainer::Add_Mesh(MeshModelClass* mmc_) {
 Vertex_Split_Table split_table(mmc_);
 int needed_vertices=split_table.Get_Vertex_Count();
 if(!vertex_buffer){
  int vb_size=4000;if(vb_size<needed_vertices)vb_size=needed_vertices;
  if(sorting)vertex_buffer=new BfmeDynamicSortingVB(vb_size);
  else vertex_buffer=new BfmeDynamicNativeVB(FVF,vb_size,(DX8Wrapper::Get_Current_Caps()->Support_NPatches() && WW3D::Get_NPatches_Level()>1)?4:0,0);
 }
 VertexBufferClass::AppendLockClass l((VertexBufferClass*)vertex_buffer,used_vertices,split_table.Get_Vertex_Count(),0);
 const S2FVFInfo fi=vertex_buffer->FVF_Info();
 unsigned char *vb=(unsigned char*)l.Get_Vertex_Array();
 unsigned int i;
 const Vector3 *locs=split_table.Get_Vertex_Array();
 const Vector3 *norms=split_table.Get_Vertex_Normal_Array();
 const unsigned *diffuse=split_table.Get_Color_Array(0);
 const unsigned *specular=split_table.Get_Color_Array(1);
 for(i=0;i<split_table.Get_Vertex_Count();++i){
  *(Vector3*)(vb+fi.Get_Location_Offset())=locs[i];
  if((FVF&0x10)==0x10 && norms)*(Vector3*)(vb+fi.Get_Normal_Offset())=norms[i];
  if((FVF&0x40)==0x40){if(diffuse)*(unsigned*)(vb+fi.Get_Diffuse_Offset())=diffuse[i];else *(unsigned*)(vb+fi.Get_Diffuse_Offset())=0xFFFFFFFF;}
  if((FVF&0x80)==0x80){if(specular)*(unsigned*)(vb+fi.Get_Specular_Offset())=specular[i];else *(unsigned*)(vb+fi.Get_Specular_Offset())=0xFFFFFFFF;}
  vb+=fi.Get_FVF_Size();
 }
 int uvcount=(FVF>>8)&15;
 for(int j=0;j<uvcount;++j){
  unsigned char *vb=(unsigned char*)l.Get_Vertex_Array();
  const Vector2 *uvs=split_table.Get_UV_Array(j);
  if(uvs)for(i=0;i<split_table.Get_Vertex_Count();++i){*(Vector2*)(vb+fi.Get_Tex_Offset(j))=uvs[i];vb+=fi.Get_FVF_Size();}
 }
 Generate_Texture_Categories(split_table,used_vertices);
 used_vertices+=needed_vertices;
}
