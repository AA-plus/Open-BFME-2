// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00218E96Parse@@YAXPAVINI@@HPAU?$vector@UFileInfoStruct@MixFileCreator@@V?$allocator@UFileInfoStruct@MixFileCreator@@@_STL@@@_STL@@@_STL@@@Z @0x00218E96 300B
// INI-driven fill of a MixFileCreator::FileInfoStruct vector. Two leading
// integers (CRC, Offset) come from getNextToken/scanInt; following string
// tokens are style markers ("+bold" -> 1, "-bold" -> 2, "normal" -> 0) or the
// entry filename. The record is pushed only when the filename is non-empty.
// Callees all rowed: INI getNextToken/scanInt/getNextAsciiString, StringBase
// compareNoCase/set/releaseBuffer, vector push_back 0x00218DD2 (chain).
// Layout from MixFileCreatorFileInfoStructAssign (CRC Offset Size Filename).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

typedef MixFileCreator::FileInfoStruct FileInfoStruct;

class INI
{
public:
	const char *getNextToken(const char *delimiters);
	int scanInt(const char *token);
	AsciiString getNextAsciiString();
	AsciiString getNextQuotedAsciiString();
	void initFromINI(void *instance, const struct FieldParse *fields);
};

struct Rva00218FC2Record
{
	Rva00218FC2Record();
	Rva00218FC2Record(const Rva00218FC2Record &);
	~Rva00218FC2Record();
	Rva00218FC2Record &operator=(const Rva00218FC2Record &);
	char bytes[16];
	bool Less(const Rva00218FC2Record &) const;
};

struct Rva00218FC2RecordCompare
{
	bool operator()(const Rva00218FC2Record &a, const Rva00218FC2Record &b) const { return a.Less(b); }
};

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class FontLibrary
{
public:
	_STL::vector<Rva00218FC2Record> *rva00218C2B(const AsciiString &name);
};

extern FontLibrary *TheFontLibrary;

namespace _STL
{
template <class I, class C> void sort(I first, I last, C comp);
}
void Rva00218E96Parse(INI *ini, int unused, _STL::vector<FileInfoStruct> *out)
{
	int crc = ini->scanInt(ini->getNextToken(0));
	int offset = ini->scanInt(ini->getNextToken(0));
	FileInfoStruct info;
	info.CRC = (unsigned long)crc;
	info.Offset = (unsigned long)offset;
	info.Size = 0;
	AsciiString cur = ini->getNextAsciiString();
	for (;;)
	{
		if (cur.getLength() == 0)
			break;
		if (((const StringBase<char> &)(cur)).compareNoCase("+bold") == 0)
			info.Size = 1;
		else if (((const StringBase<char> &)(cur)).compareNoCase("-bold") == 0)
			info.Size = 2;
		else if (((const StringBase<char> &)(cur)).compareNoCase("normal") == 0)
			info.Size = 0;
		else
			info.Filename.set(cur);
		cur.set(ini->getNextAsciiString());
	}
	if (info.Filename.getLength() > 0)
		out->push_back(info);
}

void rva00219005(INI *ini)
{
	(void)&ini;
	AsciiString name = ini->getNextQuotedAsciiString();
	_STL::vector<Rva00218FC2Record> *table = TheFontLibrary->rva00218C2B(name);
	FieldParse fields[2] = {{"Size", (INIFieldParseProc)Rva00218E96Parse, 0, 0}, {0, 0, 0, 0}};
	ini->initFromINI(table, fields);
	Rva00218FC2RecordCompare compare = {};
	_STL::sort(table->begin(), table->end(), compare);
}
