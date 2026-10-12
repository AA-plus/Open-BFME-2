// cl: /O1 /MD
// Rva005AE6F8 slot scan (retail 0x005AE6F8, 107 bytes, cdecl): searches
// 8-byte slots from first to last for one whose pointee's first dword
// equals value, returning the slot or last. Four-at-a-time unrolled loop
// ((last-first)>>5 groups) plus a fallthrough switch for the 3/2/1
// remainder; the stride travels in a register (push-8/pop-esi). The fourth
// argument is dead in retail (the 0x005AE78A wrapper forwards a local's
// address that the body never reads). Slot layout and owner identity are
// unproven; the name is address-derived.
struct Rva005AE6F8Slot
{
	void *ptr;
	int pad;
};

void *rva005AE6F8(Rva005AE6F8Slot *first, Rva005AE6F8Slot *last, int value, void *ignored)
{
	(void)ignored;
	int groups = ((char *)last - (char *)first) >> 5;
	int step = 8;
	while (groups > 0) {
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
		--groups;
	}
	int rest = ((char *)last - (char *)first) >> 3;
	switch (rest) {
	case 3:
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
	case 2:
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
	case 1:
		if (*(int *)first->ptr == value)
			return first;
		first = (Rva005AE6F8Slot *)((char *)first + step);
		break;
	default:
		break;
	}
	return last;
}
