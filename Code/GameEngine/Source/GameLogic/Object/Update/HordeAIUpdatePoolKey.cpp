// cl: /DNDEBUG /MD /EHsc
// ?rva00049A67C@HordeAIUpdate@@SA?AW4NameKeyType@@XZ @0x49a67c
// (69B): cached pool-name key for HordeAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HordeAIUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object { public: void *rva0028C197() const; };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
class AIUpdateInterface
{
protected:
 virtual void bfmePrivateCommand42(Object *, CommandSourceType);
};

class HordeAIUpdate : public AIUpdateInterface
{
public:
	static NameKeyType rva00049A67C();
private:
 char m_gap04[4];
 Object *m_owner; // native module owner at +8
 Object *getObject() const { return m_owner; }
protected:
 virtual void bfmePrivateCommand42(Object *, CommandSourceType);
};

// ?rva00049A67C@HordeAIUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HordeAIUpdate::rva00049A67C()
{
	static NameKeyType TheHordeAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HordeAIUpdate");
	return TheHordeAIUpdatePoolKey;
}


// Native 0049AC5F..0049AC94, 53B, RET8; HordeAIUpdate slot23 is named
// by its vtable and the existing worker override at0049B1CB. The owner
// getter reads+8; both calls resolve to their independently matched bodies.
// Native FuncInfo D3D650 points to unwind map D3D648: one inactive state
// with a null action. The guard-clearing funclet B8D64E belongs to the next
// record, not this one. The contradictory pure-getter condition lets VC7.1
// retain that EH record after eliminating its initialization branch. This
// is compiler-shape reconstruction; no original dead source is asserted.
void HordeAIUpdate::bfmePrivateCommand42(Object *obj, CommandSourceType source)
{
 if (getObject() && !getObject()) {
  static void *cache = getObject()->rva0028C197();
  (void)cache;
 }
 if (getObject()->rva0028C197())
  AIUpdateInterface::bfmePrivateCommand42(obj, source);
}
