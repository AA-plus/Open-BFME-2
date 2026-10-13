// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Address-derived recovery of 0x006EC670 (116B), an Apt argument handler.
// Retail fetches interpreter-stack values At(0), At(1) and, when the int
// argument is >= 3, At(2); converts At(1) through the rowed
// BfmeAptValue::toInteger (0x006DD360) and adds 0x4000; then calls the
// interpreter method 0x007092F0 with (checkedCast, 0, checkedCast, At(0),
// size, At(2)) and returns the undefined singleton at 0x00E18078. The check
// cast 0x006DCF60 and At 0x006FE580 are rowed; 0x007092F0 is unrowed and
// address-derived. Identity of the handler is not proven.
class BfmeAptValue006DCD20;

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int nPos);
	BfmeAptValue006DCD20 *rva007092F0(BfmeAptValue006DCD20 *a1, int a2, BfmeAptValue006DCD20 *a3,
		BfmeAptValue006DCD20 *a4, int a5, BfmeAptValue006DCD20 *a6);
};

struct AptActionInterpreter
{
	AptBasePtrStack stack;
};

// g_aptDateInterpreter: interpreter global at VA 0x00E182E0; the stack
// sub-object is at offset 0 (matched references already place it there).
extern AptActionInterpreter g_aptDateInterpreter;
// g_aptUndefinedAtE18078: the undefined-value singleton at VA 0x00E18078.
class AptValue; extern AptValue *gpUndefinedValue;

class BfmeAptValue006DCD20
{
public:
	int toInteger() const;
	BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK);
};

BfmeAptValue006DCD20 *rva006ec670(BfmeAptValue006DCD20 *pValue, int nParams)
{
	BfmeAptValue006DCD20 *p0 = g_aptDateInterpreter.stack.At(0);
	BfmeAptValue006DCD20 *p1 = g_aptDateInterpreter.stack.At(1);
	BfmeAptValue006DCD20 *p2 = (nParams >= 3) ? g_aptDateInterpreter.stack.At(2) : 0;
	int size = p1->toInteger() + 0x4000;
	g_aptDateInterpreter.stack.rva007092F0(
		pValue->rva006DCF60(false), 0, pValue->rva006DCF60(false), p0, size, p2);
	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}
