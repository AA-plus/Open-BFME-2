// cl: /Ireference/shims/bfme2_ascii -O1 -arch:SSE -G7 -MD /GX
// Identity: WB parseToken in AISpecialPowerInstanceType.cpp (assert line43).
// Target58A5C7 proves the scalar return ABI,41-entry table, and the calls
// to AsciiString construction, comparison and buffer release. Retail has
// no EH frame. Original enum tags and table name remain unresolved.
// The table is defined once in INIAsciiIndexParse.cpp; retain its current
// name rather than create a second datum. WB uses39 entries; retail uses41.
#include "ascii_string.h"
// The comparison only observes the existing buffer; the native parser has no EH frame.
template <> int StringBase<char>::compare(const char *text) const throw();
extern const char *g_00DD3068[];
int __cdecl parseToken(const char *key)
{
 int found=-1;
 if(key!=0) {
  for(int i=0;i<41;++i) {
   bool eq=(reinterpret_cast<const StringBase<char> &>(AsciiString(g_00DD3068[i])).compare(key)==0);
   if(eq) { found=i;break; }
  }
 }
 return found;
}
