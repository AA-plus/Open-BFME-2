// cl: /MD /EHsc
// ?rva005189CF@Rva005189CF@@QAEXXZ @0x005189CF 282B
// Master-option APT text: formats APT:MasterOption_%s from m_310 table when
// 0..5, builds Unicode via TheGameText fetch slots 0x38/0x3C plus concats,
// then bfmeSetText with CannotChangeGraphics. Evidence: caller 0x0051AE54;
// rowed AsciiString format 0x00038150 set 0x0000565D concat 0x00006A2A
// 0x00005692 releaseBuffer 0x00036E70 0x00036410 ctor 0x00037BA0;
// pin bfmeSetText 0x00225301; globals TheGameText 0x009FF0BC
// TheRva00222A8BTarget 0x009FE4CC; literals APT:MasterOption_%s
// APT:CannotChangeGraphics; table 0x00DB95F4.
typedef bool Bool;
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend class Rva005189CF;
	StringBase(const T *text);
	void releaseBuffer();
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void set(const T *s);
	void concat(const T *s);
	void concat(const StringBase<T> &other);
private:
	BfmeStringData<T> *m_data;
};

// Retail narrow cleanup calls the releaseBuffer worker directly.
// Keep the forwarding destructor inline without emitting a competing copy.
template <> __declspec(dllimport) __forceinline
StringBase<char>::~StringBase() { releaseBuffer(); }

class AsciiString : private StringBase<char>
{
	friend class Rva005189CF;
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	void __cdecl format(const char *fmt, ...);
};
class UnicodeString : private StringBase<unsigned short>
{
	friend class Rva005189CF;
public:
	UnicodeString() {}
	~UnicodeString() {}
};
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	// MSVC 7.1 lays overloaded virtuals in reverse declaration order, so
	// declare char first to place Ascii fetch at 0x38 and char fetch at 0x3C.
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &a, const UnicodeString &u, bool b);
};
class Rva00222A8BTarget
{
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char *rva00202B6CNames[];
class Rva005189CF
{
	char m_pad[0x310];
	int m_310;
public:
	void rva005189CF();
};
void Rva005189CF::rva005189CF()
{
	AsciiString key;
	if (m_310 >= 0 && m_310 <= 5)
		key.format("APT:MasterOption_%s", rva00202B6CNames[m_310]);
	UnicodeString u;
	if (((StringBase<char> &)key).m_data != 0 && ((StringBase<char> &)key).m_data->length != 0)
	{
		((StringBase<unsigned short> &)u).set(L"(");
		((StringBase<unsigned short> &)u).concat(TheGameText->fetch(key, 0));
		((StringBase<unsigned short> &)u).concat(L") - ");
	}
	((StringBase<unsigned short> &)u).concat(TheGameText->fetch("APT:CannotChangeGraphics", 0));
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(AsciiString("APT:CannotChangeGraphics"), u, false);
}
