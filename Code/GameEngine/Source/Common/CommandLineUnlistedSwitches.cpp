// cl: /DNDEBUG /MD
// Command-line switch parsers that BFME 2's -command table (0x0081FB58..
// 0x0081FBD0, sixteen entries, all rowed) no longer lists but whose bodies
// survive between the listed ones (0x003B9505..0x003B9FD3). Each has the
// BFME 1 / Zero Hour CommandLine.cpp parser shape: int (char *args[], int
// num), a TheWritableGlobalData guard, one GlobalData store, and the number
// of arguments consumed. Their command names are not recovered, so they keep
// address-derived names; the GlobalData offsets are the stores retail makes.
#include <stdlib.h>
template<class T> class StringBase {
    T *data;
public: void set(const T*);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct CommandLineSwitchPair
{
    int m_00;
    int m_04;
    int m_08;
    int m_0C;
};

struct CommandLineSwitchView
{
    char pad0000[0x27 - 0x0];
    bool m_bfme27;
    char pad0028[0x2d - 0x28];
    bool m_bfme2D;
    char pad002E[0x8c - 0x2e];
    StringBase<char> m_bfme8C;
    char pad0090[0x9bf - 0x90];
    bool m_bfme9BF;
    bool m_bfme9C0;
    char pad09C1[0xaec - 0x9c1];
    StringBase<char> m_bfmeAEC;
    char pad0AF0[0xb04 - 0xaf0];
    int m_bfmeB04;
    CommandLineSwitchPair m_bfmeB08;
    char pad0B18[0xb38 - 0xb18];
    int m_bfmeB38;
    char pad0B3C[0xbd4 - 0xb3c];
    bool m_bfmeBD4;
    char pad0BD5[0xd46 - 0xbd5];
    bool m_bfmeD46;
    char pad0D47[0xd48 - 0xd47];
    int m_bfmeD48;
    char pad0D4C[0xea4 - 0xd4c];
    bool m_bfmeEA4;
    bool m_bfmeEA5;
    char pad0EA6[0x1111 - 0xea6];
    bool m_bfme1111;
    char pad1112[0x11c8 - 0x1112];
    bool m_bfme11C8;
    char pad11C9[0x11ca - 0x11c9];
    bool m_bfme11CA;
    bool m_bfme11CB;
};

#define TheSwitches ((CommandLineSwitchView *)TheWritableGlobalData)

// Native 3B9505..3B9516: sets +2D true.
int Rva003B9505Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme2D=true;
    return 1;
}

// Native 3B9521..3B9535: sets +11CA false.
int Rva003B9521Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme11CA=false;
    return 1;
}

// Native 3B9535..3B9549: sets +11CA true.
int Rva003B9535Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme11CA=true;
    return 1;
}

// Native 3B9549..3B955D: sets +11CB true.
int Rva003B9549Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme11CB=true;
    return 1;
}

// Native 3B96F5..3B9709: sets +EA5 false.
int Rva003B96F5Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeEA5=false;
    return 1;
}

// Native 3B9737..3B974B: sets +EA4 false.
int Rva003B9737Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeEA4=false;
    return 1;
}

// Native 3B99AB..3B99BF: sets +1111 true.
int Rva003B99ABParse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme1111=true;
    return 1;
}

// Native 3B99BF..3B99D0: sets +27 true.
int Rva003B99BFParse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme27=true;
    return 1;
}

// Native 3B9A0C..3B9A20: sets +BD4 true.
int Rva003B9A0CParse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeBD4=true;
    return 1;
}

// Native 3B9A29..3B9A3D: sets +D46 true.
int Rva003B9A29Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeD46=true;
    return 1;
}

// Native 3B9AA5..3B9AB9: sets +9BF false.
int Rva003B9AA5Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme9BF=false;
    return 1;
}

// Native 3B9AB9..3B9ACD: sets +9C0 true.
int Rva003B9AB9Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme9C0=true;
    return 1;
}

// Native 3B9D5F..3B9D6F: sets +11C8 without the guard.
int Rva003B9D5FParse(char *args[],int num) {
    TheSwitches->m_bfme11C8=true;
    return 1;
}

// Native 3B9F30..3B9F56: copies the argument into the +AEC string.
int Rva003B9F30Parse(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheSwitches->m_bfmeAEC.set(args[1]);
    return 2;
}

// Native 3B9FB7..3B9FD3: copies the argument into the +8C string, unguarded.
int Rva003B9FB7Parse(char *args[],int num) {
    TheSwitches->m_bfme8C.set(args[1]);
    return 2;
}

// Native 3B9A3D..3B9A62: atoi of the argument into +D48 (no guard on
// TheWritableGlobalData, only on the argument count).
int Rva003B9A3DParse(char *args[],int num) {
    if(num>1)
        TheSwitches->m_bfmeD48=atoi(args[1]);
    return 2;
}

// Native 3B9A62..3B9A9C: clears the +B10/+B14 pair and stores the
// 0xBAADEC4C marker at +B38 and +B04.
int Rva003B9A62Parse(char *args[],int num) {
    if(TheWritableGlobalData) {
        CommandLineSwitchPair *pair=&TheSwitches->m_bfmeB08;
        pair->m_08=0;
        pair->m_0C=0;
        TheSwitches->m_bfmeB38=0xBAADEC4C;
        TheSwitches->m_bfmeB04=0xBAADEC4C;
    }
    return 1;
}
