// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// ZH GameState's save-file terminator token. Retail .data 0x009BD038 holds the pointer;
// GameState::xfer (0x002DE311 family) and addSnapshotBlock (0x002DCDBF) read it, and the
// initial DIR32 targets the "SG_EOF" text at 0x00803F6C.
extern const char BfmeSaveFileEofText[7] = "SG_EOF";
const char *SAVE_FILE_EOF = BfmeSaveFileEofText;
