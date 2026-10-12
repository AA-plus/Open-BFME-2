// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DTreeDraw@@UBE?AW4NameKeyType@@XZ, retail 0x000CEB7A (69 bytes), the
// W3DTreeDraw module table slot (0x007CCD08): Zero Hour's MAKE_STANDARD_MODULE_MACRO key,
// a function-local static NAMEKEY("W3DTreeDraw") (guard 0x00DEBBAC, key 0x00DEBBA8).
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class W3DTreeDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

NameKeyType W3DTreeDraw::getModuleNameKey() const
{
	static const NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DTreeDraw");
	return nk;
}
