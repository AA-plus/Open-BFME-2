// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /EHsc
// Retail 0x00420B61..0x00420C8E (301 bytes), RET 8. Calls from the
// grant body 0x00420C8E and named system's update queue establish the receiver.
// The method name remains address-derived. The target LevelUpFx parser and
// constructor prove level+0x3C is a vector of eight-byte FX/bone records and
// level+0x48 is the creation list. Target instructions establish each branch,
// matrix store and call; BFME1 a10e4cb's ExperienceLevelConstructor.cpp and
// WWMath Matrix3D::Make_Identity corroborate record and matrix semantics.
// Drawable's existing address-derived provider takes two opaque 32-bit slots;
// this call passes the bone text and output matrix pointers through those slots.
// It neither changes nor claims a new identity for that provider. All calls
// resolve to existing whole-byte providers, without additional pins.
#include "ascii_string.h"

#include "Lib/Coord3D.h"
class Matrix3D {
public:
    float m[12];
    __declspec(dllimport) __forceinline Matrix3D(bool identity) {
        if (identity) {
            m[0]=1.0f; m[1]=0.0f; m[2]=0.0f; m[3]=0.0f;
            m[4]=0.0f; m[5]=1.0f; m[6]=0.0f; m[7]=0.0f;
            m[8]=0.0f; m[9]=0.0f; m[10]=1.0f; m[11]=0.0f;
        }
    }
};
class Object;
class Drawable { public: bool rva00272835(int,int); };
class Thing { public: Drawable *getDrawable() const; };
class FXList { public:
 static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);
 static void doFXObj(const FXList*,const Object*,const Object*);
};
class ObjectCreationList { public: void create(void*,void*,void*); };
struct LevelUpFXInfo { const FXList *fx; AsciiString bone; };
template<class T> struct GrantVectorView {
 T *first,*last,*limit;
 unsigned size() const { return last-first; }
 T &operator[](unsigned i) const { return first[i]; }
};
struct GrantLevelFXView { char unknown[0x3c]; GrantVectorView<LevelUpFXInfo> fx; ObjectCreationList *creation; };
class Overridable;
class DelayedExperienceLevelGrantSystem { public: void rva00420B61(const Overridable*,Object*); };
void DelayedExperienceLevelGrantSystem::rva00420B61(const Overridable *level,Object *object) {
 const GrantLevelFXView *data=(const GrantLevelFXView*)level;
 for(unsigned i=0;i<data->fx.size();++i) {
  const LevelUpFXInfo &entry=data->fx[i];
  if(!((const StringBase<char>*)&entry.bone)->isEmpty() && ((Thing*)object)->getDrawable()) {
   Matrix3D matrix(true);
   ((Thing*)object)->getDrawable()->rva00272835((int)entry.bone.str(),(int)&matrix);
   Coord3D position={matrix.m[3],matrix.m[7],matrix.m[11]};
   FXList::doFXPos(entry.fx,&position,&matrix,0.0f,0);
  } else FXList::doFXObj(entry.fx,object,0);
 }
 if(data->creation) data->creation->create(object,0,0);
}
