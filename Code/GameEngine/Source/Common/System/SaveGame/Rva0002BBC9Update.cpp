// cl: /MD
// ?Rva0002BBC9Update@@YAXXZ @0x0002BBC9 21B
// Refreshes global SaveDate BfmeINIReadTimestamp via rowed 0x0002BB1C then copies
// BfmeINIMacroGeneration to BfmeINISavedMacroGeneration. Caller at 0x001B511B ignores the return.
typedef unsigned short WORD;

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
public:
	void rva0002BB1C();
};

// BfmeINIReadTimestamp: matched references place it at VA 0xddf5b8 (zero-filled; a plain-data view).
SaveDate BfmeINIReadTimestamp;
extern int BfmeINIMacroGeneration;
// BfmeINIMacroGeneration: matched references place it at VA 0xddf5ac (zero-filled .bss).
int BfmeINIMacroGeneration;
extern int BfmeINISavedMacroGeneration;
// BfmeINISavedMacroGeneration: matched references place it at VA 0xddf5b0 (zero-filled .bss).
int BfmeINISavedMacroGeneration;

void Rva0002BBC9Update()
{
	BfmeINIReadTimestamp.rva0002BB1C();
	BfmeINISavedMacroGeneration = BfmeINIMacroGeneration;
}
