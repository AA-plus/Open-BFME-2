// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva00085553Get@@YAXHH@Z 0x00085553 44B: free function sets five globals from second arg; caller 0x00085EE6
extern int BfmeScreenTransitionCurFadeFrame;
extern int BfmeScreenTransitionFadeFrames;
extern int BfmeScreenTransitionFadeDirection;
extern int BfmeScreenTransitionSwapCounter;
extern unsigned char BfmeScreenTransitionTimeOfDaySwapped;

void Rva00085553Get(int a, int b)
{
	BfmeScreenTransitionCurFadeFrame = 0;
	BfmeScreenTransitionFadeFrames = 0xC;
	BfmeScreenTransitionFadeDirection = b;
	BfmeScreenTransitionSwapCounter = 1;
	BfmeScreenTransitionTimeOfDaySwapped = 0;
}
