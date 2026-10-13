// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005CE804..005CE874,112B: six-argument constructor called by
// unrowed005759A5. Address-derived identity retained from prior attempt;
// WB015C2480 is unnamed and confirms the base call, two vptrs, argument2
// unused, members C/10/14/18 and owned holder1C. No donor name inferred.
// Structural sibling: StrategicInGameUIPlanningPhaseBuildingSelectionCtor.cpp,
// current master with BFME1 revision575ba2b04743f190f069805fbdc59936123c45da.
// Target builds base5E67FE at0 and observer at8 (BED658), then installs
// C75184/C7517C. A nontrivial owned member1C accounts for EH state2 before
// rowed5E683E forward(region->1C,region); teardown uses rowed5CE21C clear.
// The +8 observer's own vftable BED658 is not LivingWorldBuildingObserver's
// C77F44 (the four-slot building listener the LivingWorldLogic ctor/dtor and
// the sibling ctor 5CE5B3 install), so it keeps a TU-scoped address name.
class Rva005E67FE { public: Rva005E67FE(void *); virtual ~Rva005E67FE(); void *held; };
class Rva005E683EMid { public: void fwd(int,int); };
class Rva005CE804Observer { public: virtual ~Rva005CE804Observer() {} virtual void onBuildingChanged(); };
// Use the complete owning destructor provided by ThrowingNewHelpers.cpp.
// Its 26-byte retail body at5CE21C supersedes this view's thin clear wrapper.
class Rva005E893E;
class Rva005CE236 {public:Rva005CE236():m_p(0){}__declspec(noinline) ~Rva005CE236();void reset(Rva005E893E*);Rva005E893E*m_p;};
typedef char Rva005CE236SizeCheck[(sizeof(Rva005CE236)==4)?1:-1];
struct FwdArg { char pad[0x1c]; int id; };
class Rva005CE804 : public Rva005E67FE, public Rva005CE804Observer {
 public: Rva005CE804(void*,int,int,int,int,FwdArg*); virtual ~Rva005CE804(); virtual void onBuildingChanged();
 private: int a; int b; int c; FwdArg *region; Rva005CE236 owned;
};
Rva005CE804::Rva005CE804(void *owner,int context,int unused,int ui,int extra,FwdArg *r):Rva005E67FE(owner),a(context),b(ui),c(extra),region(r) {
 ((Rva005E683EMid*)this)->fwd(region->id,(int)region);
}
