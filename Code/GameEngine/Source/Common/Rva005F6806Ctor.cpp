// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005F6806..005F686A; owner shares C796D0 with destructor5F64F5.
// Named ArmyDetailsMovieClip80 establishes level/name/layout/back ABI.
class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {
public:
 ArmyDetailsMovieClip(int,const AsciiString &,int,bool);
 virtual ~ArmyDetailsMovieClip();
 virtual void notifyBackButtonClicked();
 virtual void notifyIconListBackgroundClicked();
private: class Impl *m_impl;
};
}
class Rva005F6806Heap {
public:
 Rva005F6806Heap(void *,void *,void *);
 virtual ~Rva005F6806Heap();
private: char storage[0x38-4];
};
class Rva005F64F5 : public StrategicHUD::ArmyDetailsMovieClip {
public:
 Rva005F64F5(int,const AsciiString &,bool);
 virtual ~Rva005F64F5();
private: Rva005F6806Heap *owned8;
};
Rva005F64F5::Rva005F64F5(int level,const AsciiString &name,bool back)
 : StrategicHUD::ArmyDetailsMovieClip(level,name,1,back),
 owned8(new Rva005F6806Heap(this,(void *)level,(void *)&name)) {}
