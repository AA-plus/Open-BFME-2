// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroData identity and 0x140-byte layout are established by the
// independently matched copy constructor and named vtable at VA C38D88.
// RvaVecAscii declares the existing 12-byte string-vector cleanup ABI at
// RVA2CC70. The global STL vector<AsciiString> destructor pin is misidentified
// as string release36410 in an unrelated baseline caller; do not reuse it here.
// WriteNamedHero4074CF opens a wide path with mode w, writes map50 entries
// as "%s = %d\n", closes the file and returns success as a bool.
#include <memory>
#include <vector>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "unicode_string.h"
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
typedef _STL::map<int,int> IntegerMap;
struct TreeHintPayload001F8ACB { unsigned int value; };
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB> StringPayloadMap;
namespace _STL {
template <> TreeHintPayload001F8ACB &map<AsciiString,TreeHintPayload001F8ACB>::operator[](const AsciiString &);
}
typedef _STL::vector<bool> BitVector;
typedef _STL::map<int,_STL::vector<unsigned int> > IntegerVectorMap;
class RvaVecAscii { AsciiString *m_begin; AsciiString *m_end; AsciiString *m_capacity; public: ~RvaVecAscii(); };
struct BfmeHeroElement005C39DE { AsciiString text; unsigned int word4, word8; BfmeHeroElement005C39DE(); BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &); };
class CreateAHeroData;
extern void __cdecl UnregisterCreateAHeroAtRva0021A624(CreateAHeroData *);
class CreateAHeroData : public Snapshot {
    unsigned int word04; UnicodeString text08; unsigned int word0C, word10;
    IntegerMap map14, map20; unsigned int word2C, word30, word34, word38;
    RvaVecAscii strings3C; unsigned char flag48; AsciiString text4C;
    StringPayloadMap map50; BitVector bits5C; unsigned char flag70; bool flag71;
    unsigned short pad72; IntegerVectorMap map74; BfmeHeroElement005C39DE elements80[15];
    unsigned int word134, word138, word13C;
public:
    bool WriteNamedHeroAtRva004074CF();
    bool rva00408A55();
    bool rva004099CA(AsciiString *name, bool flag);
    virtual ~CreateAHeroData();
};
CreateAHeroData::~CreateAHeroData() { if (!text4C.isEmpty()) WriteNamedHeroAtRva004074CF(); UnregisterCreateAHeroAtRva0021A624(this); }

typedef char HeroLayoutSizeCheck[sizeof(CreateAHeroData)==0x140 ? 1 : -1];
typedef char HeroStringVectorSizeCheck[sizeof(RvaVecAscii)==12 ? 1 : -1];

// Whole-class instantiation of this tree. It reproduces operator= (retail 0x0040806A)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<AsciiString,_STL::pair<AsciiString const ,TreeHintPayload001F8ACB>,_STL::_Select1st<_STL::pair<AsciiString const ,TreeHintPayload001F8ACB> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const ,TreeHintPayload001F8ACB> > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?j_00015d7a@@YAXXZ=??1?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@XZ")

// ?rva0021B7B6@Rva0021B7B6@@QAEXPAVINI@@PAX@Z @0x0021B7B6 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and its twins. The worker is the rowed
// 0x0021AAFE single-token worker.
// The join-append is the shared Rva0049B6AE::append member (rowed, body
// ignores ecx); the string temporaries are the canonical AsciiString.
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

__forceinline const char *GetStr0021B7B6(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva0021AAFE
{
public:
	bool rva0021AAFE(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0021B7B6 : public Rva0021AAFE
{
public:
	void rva0021B7B6(INI *ini, void *extra);
};

void Rva0021B7B6::rva0021B7B6(INI *ini, void *extra)
{
	AsciiString *accum = (AsciiString *)extra;
	if (accum != 0)
		accum->clear();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			AsciiString tmp(token);
			AsciiString part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr0021B7B6(part);
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!rva0021AAFE(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva0021AAFE(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}

class GameState;
extern GameState *TheGameState;
class Rva002DC74A {
public: UnicodeString rva002DC74A(const UnicodeString &) const;
};
class CreateAHeroManager {
public: unsigned char pad[0x1D8]; bool statsChanged;
};
extern CreateAHeroManager *TheCreateAHeroManager;
struct _iobuf;
extern "C" {
__declspec(dllimport) _iobuf *__cdecl _wfopen(const unsigned short *,const unsigned short *);
__declspec(dllimport) int __cdecl fprintf(_iobuf *, const char *,...);
__declspec(dllimport) int __cdecl fclose(_iobuf *);
// The real fgets import slot; a pointer call preserves retail's two loop tests.
extern char *(__cdecl *_imp__fgets)(char *, int, _iobuf *);
}
// Native 4074CF..4075A3 and the already-owned destructor caller 409285:
// build a wide save path, set manager +1D8, write map50 key/value pairs,
// and close the stream. Keep the established address-derived member identity;
// WorldBuilder's same-string SaveStats lead does not reconcile the class name.
bool CreateAHeroData::WriteNamedHeroAtRva004074CF() {
 UnicodeString path=((const Rva002DC74A *)TheGameState)->rva002DC74A(UnicodeString(text4C));
 TheCreateAHeroManager->statsChanged=true;
 _iobuf *file=_wfopen(path.str(),(const unsigned short *)L"w");
 if(file) {
 for(StringPayloadMap::iterator it=map50.begin();it!=map50.end();++it) {
  fprintf(file,"%s = %d\n",it->first.str(),it->second.value);
 }
 fclose(file);
 return true;
 }
 return false;
}

// ?rva004099CA@CreateAHeroData@@QAE_NPAVAsciiString@@_N@Z @0x004099CA 172B: the
// counterpart of WriteNamedHero4074CF. Native: an empty name fails; the rowed
// opener 0x004098A9 (name, flag) yields the stream, failing when null; a
// reader Xfer (0x0060C5FA) opens it (0x0060C3C3) and a version above 1 fails;
// otherwise the hero's wrapper 0x00406EBF transfers it, flag48 takes the flag,
// and the byte at +0x71 is the result. Open's version output lands on the
// parameter slot the name occupied (a dead name's stack slot).
class Xfer { public: virtual ~Xfer(); };
struct Rva0060C3C3Stream;
class Rva0060C5FA : public Xfer { public: Rva0060C5FA(void *a1, void *a2, void *a3); private: char m_pad04[0x20 - 4]; };
class XferLoad { public: bool Open(Rva0060C3C3Stream *stream, int *version); };
class Rva0060C45E { public: void clear(); };
class Rva00406EBF { public: void rva00406EBF(Xfer *x); };
class HeroFile { public: virtual ~HeroFile(); virtual bool open(const char *name, int access); virtual void close(); };
class File;
File *Rva004098A9(const AsciiString &name, bool systemFile);

bool CreateAHeroData::rva004099CA(AsciiString *name, bool flag)
{
    if (((StringBase<char> *)name)->isEmpty())
        return false;
    HeroFile *file = (HeroFile *)Rva004098A9(*name, flag);
    if (file == 0)
        return false;
    Rva0060C5FA xfer(0, 0, 0);
    bool ok;
    if (!((XferLoad *)&xfer)->Open((Rva0060C3C3Stream *)file, (int *)&name))
    {
        file->close();
        ok = false;
    }
    else if ((unsigned)*(int *)&name > 1)
    {
        file->close();
        ok = false;
    }
    else
    {
        ((Rva00406EBF *)this)->rva00406EBF(&xfer);
        flag48 = flag;
        ((Rva0060C45E *)&xfer)->clear();
        file->close();
        ok = flag71;
    }
    return ok;
}

// The reader calls the MD CRT import. A scoped C-linkage declaration retains
// the real atoi symbol without changing the STL bodies' static-free settings.
namespace HeroStatsCRT {
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
}

// Native408A55..408C11: bool-returning stats reader, with wide path from
// the same GameState provider as the verified writer. Native line buffer is
// 1024 bytes; map50 receives trimmed key/value pairs before award refresh.
// The real IAT symbol is used directly; no alternate name or address pin.
class Rva0021937DTarget { public: void rva00407E94(); };
bool CreateAHeroData::rva00408A55()
{
    if (reinterpret_cast<const StringBase<char> *>(&text4C)->isEmpty())
        return false;
    UnicodeString path = reinterpret_cast<const Rva002DC74A *>(TheGameState)->rva002DC74A(UnicodeString(text4C));
    _iobuf *file = _wfopen(path.str(), reinterpret_cast<const unsigned short *>(L"r"));
    char buffer[1024];
    if (file != 0) {
      if (_imp__fgets(buffer, sizeof(buffer), file)) {
        do {
        AsciiString line(buffer);
        line.trim();
        AsciiString key;
        AsciiString value;
        line.nextToken(&key, "=");
        value.set(line.str() + 1);
        key.trim();
        value.trim();
        if (!key.isEmpty()) {
            if (value.isEmpty())
                map50[key].value = 0;
            else
                map50[key].value = HeroStatsCRT::atoi(value.str());
        }
        } while (_imp__fgets(buffer, sizeof(buffer), file));
      }
      fclose(file);
      reinterpret_cast<Rva0021937DTarget *>(this)->rva00407E94();
      return true;
    }
    return false;
}
