// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Two retail wrappers (23B + 21B) over the shared callee at 0x004097AF.
// 0x00409892: push [esp+8], push 0x4A, push [esp+0x10], push [esp+0x10],
//   call, add esp, 0x10, ret -> callee(a, b, 0x4A, b).
// 0x004098A9: push 0, push 0x41, push [esp+0x10], push [esp+0x10],
//   call, add esp, 0x10, ret -> callee(a, b, 0x41, 0).
// /O1 keeps the pushes on the stack slots. Callee/tag identities unproven;
// names are address-derived. One ledger row per wrapper.
// The parameters take the worker's ABI (Rva004097AFOpenFile.cpp): a name by
// reference and a one-byte system flag, which every caller passes unwidened
// (0x0021F54B pushes the spilled flag's whole dword; 0x004099EB forwards it).

class AsciiString;
class File;

extern "C" File *__cdecl Rva004097AFWorker(const AsciiString &name, bool systemFile, int access,
	bool checkOut);

File *Rva00409892(const AsciiString &name, bool systemFile)
{
	return Rva004097AFWorker(name, systemFile, 0x4A, systemFile);
}

File *Rva004098A9(const AsciiString &name, bool systemFile)
{
	return Rva004097AFWorker(name, systemFile, 0x41, false);
}
