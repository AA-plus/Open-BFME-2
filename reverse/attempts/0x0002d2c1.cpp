// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z
// partial score=0.9 date=2026-10-12
// cl: /O1 /arch:SSE /G7 /Ireference/shims/iniexception /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z @0x0002D2C1, 936B.
//
// Bank repair 2026-10-12: use the matched INI region's /O1 /arch:SSE /G7
// explicitly because bank/scratch paths do not receive Code/ region defaults.
// The old default-/O2 scratch result was 1182B; the corrected bank emits 933B
// against the native 936B body and first differs at the early throw-tail JMP
// (+0x47). This remains a partial, not a matched ledger body.
//
// Target corrections: helper call at 0x2D39E pushes the just-opened File*, not
// the INI receiver; startsWith false at 0x2D3F6 exits the record loop; update
// 0x2D578..0x2D57C stores saved macroCount+1 without updating that saved local.
// The insertion wrapper's output starts at EBP-0x40 and its inserted flag is
// at EBP-0x38: the old eight-byte view was undersized. The rowed insertion
// provider also writes {node, table, byte flag}; that corroborates a 12B view.
// Exception storage is the canonical 8B {message pointer, argument count};
// retail ThrowInfo/CatchableType and the matched constructor/copy/destructor
// independently support it. The inline insertion helper preserves native
// copy-pair-before-insert and pair/factory destruction order; it is a local
// reconstruction, not an established original helper identity.
//
// Remaining mismatch: duplicate/common exception tail placement, two late
// error-block ordering differences and their branch displacements. Whole-byte,
// callee/data identity, literal and EH gates have NOT passed for this bank.
// Donor name and layout uncertainties documented below are preserved.

// Name/signature are carried from the clean BFME1 INI.cpp prepFile donor;
// this target body is substantially different. Target evidence: all three
// matched INI load entries pass (&filename, loadType) and branch on AL; the
// body opens/records the file, runs the +0x838 helper, closes the file,
// scans the helper's 12-byte records, and handles #define rows through the
// global macro table. The table's constructor at 0x2DC3C initializes a
// hash_map at +0 and set at +0x14; target calls 0x2CD2F with ECX=0xDDF58C and
// 0x2CB98 with that same base. Its target class name remains structural.
// The helper record/name views follow 0x6018B6, 0x5D5847 and the independent
// readLine consumer; the macro value is the pair's second StringBase at node
// +8, confirmed by target compare/assignment calls 0x69D6/0x366F0.
// GeneralsMD Common/INI/INI.cpp prepFile supplies only the open/save-file
// semantic lead. Target-specific timestamp gating, macro parsing, error
// messages, and duplicate replacement follow retail bytes and strings.

#include "ascii_string.h"

// Keep the vector member declaration out of the implementation header. The
// target calls its separately emitted size body at 0x5D5847.
namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	unsigned int size() const;
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <class First, class Second> struct pair
{
	First first;
	Second second;
	pair(const pair &that);
	~pair();
};
}

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE,
	INI_LOAD_UNK4,
	INI_LOAD_UNK5
};

class File
{
public:
	virtual ~File();
	virtual bool open(const char *name, int flags);
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unknown);
};

extern FileSystem *TheFileSystem;
extern AsciiString g_00DDF5B4;
extern int g_00DDF5AC;
extern int g_00DDF5B0;
extern unsigned g_Va00DDF58C;

typedef unsigned short WORD;
struct SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};

struct SaveDate
{
	WORD year;
	WORD month;
	WORD day;
	WORD dayOfWeek;
	WORD hour;
	WORD minute;
	WORD second;
	WORD milliseconds;
};
extern SaveDate g_00DDF5B8;

bool Rva0002C025IsNewer(const AsciiString &filename, const SYSTEMTIME *date);

class Rva0002CB98
{
	unsigned char m_pad[0x14];
public:
	bool rva0002CB98(const AsciiString &filename) const;
};

struct Out0002CA72
{
	void *first;
	void *iteratorOwner;
	unsigned char second;
	unsigned char pad[3];
};
struct Pair0002CA72;
class Rva0002CD2F
{
	char m_pad[16];
	unsigned int m_count;
public:
	Out0002CA72 *rva0002CD2F(Out0002CA72 *out, const Pair0002CA72 *value);
};

struct BfmeE12
{
	float x;
	float y;
	float z;
};

struct INIFileRecord
{
	unsigned int fileId;
	int line;
	int nameIndex;
};
struct INIFileRecordTable
{
	INIFileRecord *begin;
	INIFileRecord *end;
	unsigned int reserved;
	AsciiString *names;
};
class INIFileTable
{
public:
	int getFileId(int index) const;
private:
	unsigned int reserved;
	INIFileRecordTable records;
};

class Rva00601BBCHelper
{
public:
	virtual ~Rva00601BBCHelper();
	bool rva00602072(void *outer);
private:
	char m_04[0x18];
	_STL::vector<int> m_1C;
	_STL::vector<int> m_28;
};

class INI
{
	protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);

	private:
	File *m_file;
	AsciiString m_filename;
	INILoadType m_loadType;
	int m_0C;
	int m_10;
	char m_pad14[0x838 - 0x14];
	Rva00601BBCHelper m_helper;
};

#include "Common/INIException.h"

typedef _STL::pair<const AsciiString, AsciiString> MacroPair;
typedef char InsertResultSizeCheck[sizeof(Out0002CA72) == 12 ? 1 : -1];
typedef char ExceptionSizeCheck[sizeof(INIException) == 8 ? 1 : -1];
typedef char MacroPairSizeCheck[sizeof(MacroPair) == 8 ? 1 : -1];

// The lifted return record is two StringBase-sized words. Its mangling is
// retained as BfmePairEL; the pair base supplies the target-proven copy/dtor
// behavior at 0x2C574/0x2C0C0 without assigning that donor spelling to data.
class BfmeWordEL
{
	void *m_stringStorage;
};
struct BfmePairEL : MacroPair
{
	__forceinline ~BfmePairEL() {}
};
BfmePairEL __cdecl bfmeMakePairEL(const BfmeWordEL &first, const BfmeWordEL &second);

static __forceinline void insertMacroPair(Out0002CA72 *inserted, const BfmePairEL &factoryPair)
{
	MacroPair pair((const MacroPair &)factoryPair);
	((Rva0002CD2F *)&g_Va00DDF58C)->rva0002CD2F(inserted, (const Pair0002CA72 *)&pair);
}

// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z
bool INI::prepFile(const AsciiString &filename, INILoadType loadType)
{
	if (m_file != 0)
	{
		throw INIException(6,
			"INI::load, cannot open file '%s', file already open\n", filename.str());
	}

	if (loadType == INI_LOAD_UNK5)
	{
		if (g_00DDF5B0 == g_00DDF5AC)
		{
			if (!Rva0002C025IsNewer(filename, (const SYSTEMTIME *)&g_00DDF5B8))
				return false;
		}
		else if (((Rva0002CB98 *)&g_Va00DDF58C)->rva0002CB98(filename) == false)
		{
			return false;
		}
	}

	m_file = TheFileSystem->openFile(filename.str(), 1, 0);
	g_00DDF5B4 = filename;
	if (m_file == 0)
	{
		throw INIException(7, "INI::load, cannot open file '%s'\n", filename.str());
	}

	m_helper.rva00602072(m_file);
	m_file->close();
	m_file = 0;

	int macroCount = g_00DDF5AC;
	_STL::vector<BfmeE12> *records = (_STL::vector<BfmeE12> *)((char *)&m_helper + 4);
	INIFileTable *fileTable = (INIFileTable *)&m_helper;
	for (int index = 0; index < (int)records->size(); ++index)
	{
		char *rawLine = (char *)fileTable->getFileId(index);
		AsciiString line(rawLine);
		if (line.startsWith("#define"))
		{
			*rawLine = 0;
			AsciiString value;
			line.nextToken(&value, 0);
			AsciiString name;
			line.nextToken(&name, 0);

			if (filename.endsWith("map.ini"))
			{
				throw INIException(8,
					"%s:\nMACROs not allowed in map.ini.\n%s.", filename.str(), name.str());
			}

			for (const char *p = name.str(); ; ++p)
			{
				char ch = *p;
				if (ch == 0) break;
				if (ch > 'a' && ch < 'z')
				{
					throw INIException(8,
						"%s:\nMACRO names must use UPPERCASE letters.\n%s.", filename.str(), name.str());
				}
			}

			line.nextToken(&value, 0);
			AsciiString part;
			while (line.nextToken(&part, 0))
			{
				value += " ";
				value += part;
			}
			if (value.isEmpty())
			{
				throw INIException(8,
					"%s:\nError parsing MACRO.\n%s has no value", filename.str(), name.str());
			}

			Out0002CA72 inserted;
			insertMacroPair(&inserted, bfmeMakePairEL(
				(const BfmeWordEL &)name, (const BfmeWordEL &)value));


			bool duplicate = inserted.second == 0;
			if (loadType != INI_LOAD_UNK5)
			{
				if (duplicate)
				{
				throw INIException(8,
					"%s:\nDuplicate MACRO names.\n%s.", filename.str(), name.str());
			}
				}
			else if (duplicate)
			{
				AsciiString *existingValue = (AsciiString *)((char *)inserted.first + 8);
				if (existingValue->compare(value) != 0)
				{
					*existingValue = value;
					g_00DDF5AC = macroCount + 1;
				}
			}
		}
		else
			break;
	}

	m_filename = filename;
	m_loadType = loadType;
	return true;
}
