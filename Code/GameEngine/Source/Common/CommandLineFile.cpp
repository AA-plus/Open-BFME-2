// cl: /DNDEBUG /MD
// EA BFME1 CommandLine.cpp parseFile; BFME2's live -file table entry
// identifies RVA3BA233 and the complete 63-byte body.
// Initial file is +ABC. The adjacent +AB8 name below is descriptive:
// retail's extended map normalizer writes a timestamped label there.
// Helper identity is based on the full 453-byte body at 3BA06E:
// source-derived slash/token/.map normalization plus BFME2's second output.
template<class T> class StringBase {
    T *data;
public: void set(const T*);
};
class GlobalData {
public:
    char prefix[0xab8];
    StringBase<char> m_bfmeFileLabel;
    StringBase<char> m_initialFile;
    char unknownAC0[4];
    bool m_bfmeResumeRequested; // descriptive name; live -resumeGame writes +AC4
    bool m_bfmeAC5; // written by the unlisted 0x003BA2BE parser below
};
extern GlobalData *TheWritableGlobalData;
void ConvertShortMapPathToLongMapPath(StringBase<char>&,StringBase<char>&);
int parseFile(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}

// Retail command table at81FBC8 maps -resumeGame to3BA272 (76 bytes).
// Reuses parseFile's source-backed flow with the independently observed flag.
int parseResumeGame(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_bfmeResumeRequested=true;
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}

// Native 3BA2BE..3BA30A (76 bytes), directly after parseResumeGame and not
// in the -command table at 81FBC8: the same file flow, raising the +AC5 flag.
// Its command name is not recovered; address-derived name.
int Rva003BA2BEParse(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_bfmeAC5=true;
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}
