// ?copyCurrentRecordingToFile@RecorderClass@@QAE_NPAVUnicodeString@@0@Z
// partial score=0.984 date=2026-10-11
// ?copyCurrentRecordingToFile@RecorderClass@@QAE_NPAVUnicodeString@@0@Z
// best 2026-10-11 seat14: 643B/643B, frame 0x10034 exact, every instruction and
// relocation agrees; 10 one-byte ebp displacements differ (retail: the branch
// string temporaries at -0x10, bytesRead/bytesWritten spill at -0x18 sharing the
// triple's Pair8.b; here bytesRead gets -0x10 and the temporaries pack with
// Pair8 at -0x18). Byte-equal ratio 633/643.
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// RecorderClass::copyCurrentRecordingToFile, retail [0x0037D6E8,0x0037D96B),
// 643 bytes including the out-of-line success tail at 0x0037D930.
#include "unicode_string.h"

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *, const unsigned short *);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *, long, int);
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *);
extern "C" __declspec(dllimport) int __cdecl fwprintf(FILE *, const unsigned short *, ...);
extern "C" __declspec(dllimport) unsigned short __cdecl fputwc(unsigned short, FILE *);

UnicodeString Rva0037B9D4Get();
UnicodeString Rva0037BA48Get();
UnicodeString Rva0037D55EGet();
class Rva0037BBED
{
public:
	UnicodeString rva0037BCA8();
};

struct Pair8 { int a, b; };
struct Triple12 { Triple12() {} int a, b, c; };
inline Triple12 Rva0037BA97Init(const Pair8 *src, int c)
{
	Triple12 tmp;
	tmp.a = src->a;
	tmp.b = src->b;
	tmp.c = c;
	return tmp;
}

struct BFME2WideConcatPair
{
	const UnicodeString *a, *b;
	operator UnicodeString();
};
struct BFME2WideConcatTriple
{
	const UnicodeString *a, *b, *c;
	operator UnicodeString();
};

static __forceinline BFME2WideConcatPair operator+(const UnicodeString &x, const UnicodeString &y)
{
	BFME2WideConcatPair p = { &x, &y };
	return p;
}
static __forceinline void assignConcat(UnicodeString &dst, const UnicodeString &x, const UnicodeString &y, const UnicodeString &z)
{
	Pair8 xy = { (int)&x, (int)&y };
	dst = (BFME2WideConcatTriple &)Rva0037BA97Init(&xy, (int)&z);
}

class RecorderClass
{
public:
	bool copyCurrentRecordingToFile(UnicodeString *name, UnicodeString *title);
	void logGameEnd() throw();
private:
	char pad00[0x10];
	FILE *m_file;
};

bool RecorderClass::copyCurrentRecordingToFile(UnicodeString *name, UnicodeString *title)
{
	if (m_file == 0)
		return false;
	unsigned int fileSize = ftell(m_file);
	if (fileSize < 0x25)
		return false;
	UnicodeString path;
	if (!name->isEmpty())
		path = Rva0037B9D4Get() + *name;
	else
		assignConcat(path, Rva0037B9D4Get(), Rva0037D55EGet(), Rva0037BA48Get());
	FILE *out = _wfopen(path.str(), (const unsigned short *)L"wb");
	if (!out)
		return false;
	int seekRes = fseek(m_file, 0, 0);
	char buffer[0x10000];
	unsigned int bytesRead = fread(buffer, 1, 0x25, m_file);
	unsigned int bytesWritten = fwrite(buffer, 1, 0x25, out);
	if (seekRes != 0 || bytesRead < 0x25 || bytesWritten < 0x25)
		return false;
	UnicodeString oldTitle = ((Rva0037BBED *)this)->rva0037BCA8();
	fwprintf(out, (const unsigned short *)L"%ws", title->str());
	fputwc(0, out);
	do {
		bytesRead = fread(buffer, 1, 0x10000, m_file);
		bytesWritten = fwrite(buffer, 1, bytesRead, out);
	} while (bytesRead == 0x10000 && bytesWritten == bytesRead);
	if (bytesRead != bytesWritten)
		return false;
	FILE *saved = m_file;
	m_file = out;
	logGameEnd();
	m_file = saved;
	fclose(out);
	fseek(m_file, fileSize, 0);
	return true;
}
