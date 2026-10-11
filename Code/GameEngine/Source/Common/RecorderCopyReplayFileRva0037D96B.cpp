// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Rva0037D96B, retail [0x0037D96B,0x0037DC36), 715 bytes, cdecl bool over
// three UnicodeString references. BFME1 RecorderCopyReplayFile (9cbfb551) is
// the semantic guide, WB F5C460 places it in Recorder.cpp: build the source
// path (the replay directory unless the name already holds a backslash) and
// the destination path (replay directory + name, or replay directory + the
// default replay name + extension when the name is empty), copy the 0x25-byte
// replay header, replace the stored title with `title`, then copy the rest in
// 64K chunks. Retail concatenates through the wide pair/triple materializers
// (0x0021C3F7, 0x0037D3C9) and the Pair8/Triple12 builder at 0x0037BA97.
#include "unicode_string.h"

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *, const unsigned short *);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, FILE *);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *, long, int);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *);
extern "C" __declspec(dllimport) int __cdecl fwprintf(FILE *, const unsigned short *, ...);
extern "C" __declspec(dllimport) unsigned short __cdecl fputwc(unsigned short, FILE *);

UnicodeString Rva0037B9D4Get();
UnicodeString Rva0037BA48Get();
UnicodeString Rva0037D55EGet();
UnicodeString readUnicodeString(FILE *);

struct Pair8 { int a, b; };
struct Triple12 { Triple12() {} int a, b, c; };
// The rowed 43-byte builder (Rva0037BA97Finish.cpp), kept visible: declared
// only, cl gives the triple's Pair8 a slot of its own (frame 0x10044 against
// retail's 0x1003C); with the body in view it shares the pair branch's slot as
// retail does. It is still called, never expanded.
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

bool Rva0037D96B(const UnicodeString &src, const UnicodeString &dst, const UnicodeString &title)
{
	UnicodeString srcPath;
	if (src.find(0x5C))
		srcPath = src;
	else {
		srcPath = Rva0037B9D4Get();
		srcPath += src;
	}
	UnicodeString dstPath;
	if (!dst.isEmpty())
		dstPath = Rva0037B9D4Get() + dst;
	else
		assignConcat(dstPath, Rva0037B9D4Get(), Rva0037D55EGet(), Rva0037BA48Get());
	FILE *in = _wfopen(srcPath.str(), (const unsigned short *)L"rb");
	if (!in)
		return false;
	FILE *out = _wfopen(dstPath.str(), (const unsigned short *)L"wb");
	if (!out)
		return false;
	int seekRes = fseek(in, 0, 0);
	char buffer[0x10000];
	unsigned int bytesRead = fread(buffer, 1, 0x25, in);
	unsigned int bytesWritten = fwrite(buffer, 1, 0x25, out);
	if (seekRes != 0 || bytesRead < 0x25 || bytesWritten < 0x25)
		return false;
	UnicodeString oldTitle = readUnicodeString(in);
	fwprintf(out, (const unsigned short *)L"%ws", title.str());
	fputwc(0, out);
	do {
		bytesRead = fread(buffer, 1, 0x10000, in);
		bytesWritten = fwrite(buffer, 1, bytesRead, out);
	} while (bytesRead == 0x10000 && bytesWritten == bytesRead);
	if (bytesRead != bytesWritten)
		return false;
	fclose(in);
	fclose(out);
	return true;
}
