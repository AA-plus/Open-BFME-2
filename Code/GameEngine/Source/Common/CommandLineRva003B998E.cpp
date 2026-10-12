// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD

class GlobalData
{
public:
	char m_padToFlag26[0x26];
	char m_flag26;
	char m_padToValue28[1];
	int m_value28;
	char m_padTo9B4[0x9b4 - 0x2c];
	int m_value9B4;
};

extern GlobalData *TheWritableGlobalData;

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

// ?Rva003B998EParse@@YAHPAPADH@Z @0x003B998E 29B
// Target evidence: called with command-line arguments by the adjacent parser;
// writes GlobalData fields at +0x26 and +0x28. Field meanings are inferred.
int Rva003B998EParse(char **, int)
{
	if (TheWritableGlobalData != 0)
	{
		TheWritableGlobalData->m_flag26 = 0;
		TheWritableGlobalData->m_value28 = 30000;
	}
	return 1;
}

// ?Rva003B99D0Parse@@YAHQAPADH@Z @0x003B99D0 60B
// The adjacent parser that calls the one above (retail keeps ECX across the
// call because the callee's body is visible here), then stores atoi of the
// argument at +0x9B4. Not in the 81FB58 -command table; name unrecovered.
int Rva003B99D0Parse(char *args[], int num)
{
	if (TheWritableGlobalData != 0 && num > 1)
	{
		Rva003B998EParse(args, num);
		TheWritableGlobalData->m_value9B4 = atoi(args[1]);
		return 2;
	}
	return 1;
}
