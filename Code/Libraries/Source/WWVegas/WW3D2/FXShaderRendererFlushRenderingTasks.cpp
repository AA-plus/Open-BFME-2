// cl: /O1 /G7 /MD /EHsc
// Native comparator0017368A..001736A7 follows a RET4 at00173687.
// Both range flushers001748B3 and00174A57 pass this address to the owned
// STLport sort over32-byte rendering tasks. Only the mesh pointer at task0
// and its unsigned ordering word at meshC4 are read here. The names below
// describe an address-derived ABI view; the original record and method
// spelling are unknown. Native EAX is the complete zero/one result.
struct Rva0017368AMesh { char unknown[0xc4]; unsigned key; };
struct Rva0017368ATask { Rva0017368AMesh *mesh; char unknown[28]; };

unsigned Rva0017368ACompare(const Rva0017368ATask &a, const Rva0017368ATask &b)
{
    return a.mesh->key < b.mesh->key;
}
