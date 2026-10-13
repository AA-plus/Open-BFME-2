// cl: /MD /EHsc
//
// Zero Hour profile_cmd.cpp as built into BFME2 (retail 0x006C67F0-
// 0x006C6E7F). Zero Hour's static Debug::Command is a call through
// theDebug's vtable (slot 0x8C) here. Execute is the 1391-byte body at
// 0x006C68C0 (ZH Execute plus BFME2's "external" command, the count and
// 'spike' arguments of "add", and a longer "help" text); the 503-byte
// body at 0x006C65F0 is the unrelated ProfileBlock constructor.

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "internal.h"

// .bss 0x00E0C634 / 0x00E0C630
unsigned ProfileCmdInterface::numResIf;
ProfileCmdInterface::Factory *ProfileCmdInterface::resIf;

// ?AddResultFunction@ProfileCmdInterface@@SAXP6APAVProfileResultInterface@@HPBQBD@ZPBD2@Z
void ProfileCmdInterface::AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
	const char *name, const char *arg)
{
	if (!func)
		return;
	if (!name)
		return;
	for (unsigned k = 0; k < numResIf; k++)
		if (!strcmp(resIf[k].name, name))
			return;
	++numResIf;
	resIf = (Factory *)ProfileReAllocMemory(resIf, numResIf * sizeof(Factory));
	resIf[numResIf - 1].func = func;
	resIf[numResIf - 1].name = name;
	resIf[numResIf - 1].arg = arg;
}

// ?RunResultFunctions@ProfileCmdInterface@@QAEXXZ
void ProfileCmdInterface::RunResultFunctions(void)
{
	if (!numResFunc)
		theDebug->Command("profile.result file_csv");

	for (unsigned k = 0; k < numResFunc; k++)
	{
		resFunc[k]->WriteResults();
		resFunc[k]->Delete();
	}
}

// Debug's operator<<(int) is vtable slot 0x34, which debug.h leaves unnamed.
class DebugIntShift
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30();
	virtual Debug &shiftInt(int value);
};
static inline DebugIntShift &asIntShift(Debug &dbg)
{
	return (DebugIntShift &)dbg;
}

// BFME2's pattern entry is 0x18 bytes: the "add" command stores the optional
// 'spike' flag (argn >= 4) as an __int64 at +0x10.
struct PatternEntryWithSpike
{
	PatternEntryWithSpike *next;
	bool isActive;
	char *pattern;
	int framesLeft;
	__int64 spike;
};

// ?rva006C83B0@@YAXAAVDebug@@IPBQBD@Z (ProfilePerfCommand.cpp)
void rva006C83B0(Debug &dbg, unsigned argc, const char *const *argv);

// ?Execute@ProfileCmdInterface@@UAE_NAAVDebug@@PBDW4CommandMode@DebugCmdInterface@@IPBQBD@Z
bool ProfileCmdInterface::Execute(Debug &dbg, const char *cmd, CommandMode cmdmode,
	unsigned argn, const char *const *argv)
{
	bool normalMode = cmdmode == Normal;

	if (!strcmp(cmd, "help"))
	{
		if (!normalMode)
			return true;

		if (!argn)
		{
			dbg << "profile group help:\n"
				"  result, caller, clear, add, view, external\n";
			return true;
		}
		else if (!strcmp(argv[0], "result"))
		{
			dbg << "result\n\n"
				"Shows the list of available result functions and their\n"
				"optional parameters.\n"
				"\n"
				"result <res_func_name> [ <arg1> .. <argN> ]\n\n"
				"Adds the given result function to be executed on program\n"
				"exit.\n";
			return true;
		}
		else if (!strcmp(argv[0], "caller"))
		{
			dbg << "caller [ (+|-) ]\n\n"
				"Enables/disables recording of caller information while\n"
				"performing function level profiling. Turned off by default\n"
				"since CPU hit is non-zero.\n";
		}
		else if (!strcmp(argv[0], "clear"))
		{
			dbg << "clear\n\n"
				"Clears the profile inclusion/exclusion list.\n";
			return true;
		}
		else if (!strcmp(argv[0], "add"))
		{
			dbg << "add (+|-) <pattern> [ <count> [ 'spike' ] ]\n"
				"\n"
				"Adds a pattern to the profile list. By default all\n"
				"profile ranges are disabled. Each new range is then checked\n"
				"against all pattern in this list. If a match is found the\n"
				"active/inactive state is modified accordingly (+ for active,\n"
				"- for inactive). The final state is always the last match.\n"
				"If an optional count is specified the pattern is automatically\n"
				"removed from the list once the given number of matches have\n"
				"occured. This is typically used in interactive mode in order to\n"
				"profile a certain number of frames.\n"
				"If 'spike' is specified a frame is only stored if the global\n"
				"total time for that frame is higher than the frame before thus\n"
				"effectively only storing spiking frames.\n";
			return true;
		}
		else if (!strcmp(argv[0], "view"))
		{
			dbg << "view\n\n"
				"Shows the active pattern list.\n";
			return true;
		}
		else if (!strcmp(argv[0], "external"))
		{
			dbg << "external (+|-) [ <if in + mode: output filename> ] [ <optional arguments> ]\n\n"
				"Starts/stops an external profiler, by executing a batch file.\n"
				"The batch file called 'profile.cmd' in the current directory will be executed\n"
				"with the parameter '/start' or '/stop'. If '/start' it is followed by the\n"
				"output filename and process identifier, eg:\n"
				"   profile.cmd /start run0 6453\n"
				"After those parameters the optional arguments will be passed through unchanged.\n";
			return true;
		}
		return false;
	}

	if (!strcmp(cmd, "result"))
	{
		if (!argn)
		{
			for (unsigned k = 0; k < numResIf; k++)
			{
				dbg << resIf[k].name;
				if ((resIf[k].arg && *resIf[k].arg) || !normalMode)
					dbg << "\n  " << resIf[k].arg;
				dbg << "\n";
			}
		}
		else
		{
			unsigned k;
			for (k = 0; k < numResIf; k++)
				if (!strcmp(argv[0], resIf[k].name))
					break;
			if (k == numResIf)
			{
				dbg << "Unknown result function\n";
				return true;
			}

			ProfileResultInterface *newIf = resIf[k].func(argn - 1, argv + 1);
			if (!newIf)
			{
				dbg << "Could not add result function\n";
				return true;
			}

			++numResFunc;
			resFunc = (ProfileResultInterface **)ProfileReAllocMemory(resFunc, numResFunc * sizeof(ProfileResultInterface *));
			resFunc[numResFunc - 1] = newIf;
			if (normalMode)
				dbg << "Result function " << argv[0] << " added\n";
		}

		return true;
	}

	if (!strcmp(cmd, "caller"))
		return true;

	if (!strcmp(cmd, "clear"))
	{
		const char *pattern = argn < 1 ? "*" : argv[0];
		for (Profile::PatternListEntry **entryPtr = &Profile::firstPatternEntry; *entryPtr;)
		{
			if (Debug::SimpleMatch((*entryPtr)->pattern, pattern))
			{
				Profile::PatternListEntry *cur = *entryPtr;
				*entryPtr = cur->next;
				ProfileFreeMemory(cur->pattern);
				ProfileFreeMemory(cur);
			}
			else
				entryPtr = &((*entryPtr)->next);
		}

		if (Profile::firstPatternEntry)
		{
			Profile::PatternListEntry *cur;
			for (cur = Profile::firstPatternEntry; cur->next; cur = cur->next);
			Profile::lastPatternEntry = cur;
		}
		else
			Profile::lastPatternEntry = 0;
		return true;
	}

	if (!strcmp(cmd, "add"))
	{
		if (argn < 2)
			dbg << "Please specify mode and pattern";
		else
		{
			PatternEntryWithSpike *cur = (PatternEntryWithSpike *)ProfileAllocMemory(sizeof(PatternEntryWithSpike));

			cur->next = 0;
			cur->isActive = *argv[0] == '+';
			cur->pattern = (char *)ProfileAllocMemory(strlen(argv[1]) + 1);
			cur->framesLeft = argn < 3 ? -1 : atoi(argv[2]);
			cur->spike = (int)(argn >= 4);
			strcpy(cur->pattern, argv[1]);
			_strlwr(cur->pattern);

			if (Profile::lastPatternEntry)
				Profile::lastPatternEntry->next = (Profile::PatternListEntry *)cur;
			else
				Profile::firstPatternEntry = (Profile::PatternListEntry *)cur;
			Profile::lastPatternEntry = (Profile::PatternListEntry *)cur;
		}
		return true;
	}

	if (!strcmp(cmd, "view"))
	{
		for (Profile::PatternListEntry *cur = Profile::firstPatternEntry; cur; cur = cur->next)
		{
			dbg << (cur->isActive ? "+ " : "- ") << cur->pattern;
			if (cur->framesLeft > 0)
				asIntShift(dbg << " (auto ").shiftInt(cur->framesLeft) << ")";
			dbg << "\n";
		}
		return true;
	}

	if (!strcmp(cmd, "external"))
	{
		rva006C83B0(dbg, argn, argv);
		return true;
	}

	return false;
}
