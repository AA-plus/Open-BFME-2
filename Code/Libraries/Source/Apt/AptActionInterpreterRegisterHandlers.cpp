// cl: /O2 /MD /EHsc
// Native opcode-table entries7049B0/86 and706070/453 retain their PDB
// private static signatures and whole extents. Body provenance is the existing
// ConstantHandlers TU; only register stores use the verified canonical
// AptScriptFunctionBase::SetRegisterValue709F70 instead of its retired name.
// Canonical spFrameStack replaces the old frame-global linker alias.
// Native fields stack0/4/8, currentFunction30, thrownValue60 and28-byte
// LocalContext are the existing target evidence. Untouched storage stays opaque.
// This is a caller identity repair, with no new coverage, pin or donor identity.
#include "AptObject/AptScriptFunction.h"
#include <stddef.h>
struct AptCharacterInst;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class EAStringC {
public:
    EAStringC(const char *);
    ~EAStringC();
private:
    void *data;
};
class AptBasePtrStack {
public:
    __forceinline AptValue *At(int nPos) const {
        if (!(count-nPos>0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10A);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return items[count-nPos-1];
    }
    __forceinline int GetSize() const { return count; }
    void rva006E3AA0(int);
    int count, capacity;
    AptValue **items;
};
// Keep the already rowed neutral150B frame-publisher provider spelling.
// Its canonical class reconciliation is separate from this register repair.
class Rva8D0D80Result { public: void rva006FBED0(); };
struct AptActionInterpreter {
    struct LocalContextT {
        const unsigned char *pInstruction;
        AptCIH *pCurrentContext;
        AptValue *pCurWith;
        const unsigned char *pRemoveWithAt;
        AptValue *pSuper;
        bool bEncounteredReturn;
        AptCharacterInst *pParentCharacter;
    };
    AptBasePtrStack stack;
    unsigned char unused0Cto30[0x24];
    AptScriptFunctionBase *mpCurrentFunction;
    unsigned char unused34to60[0x2C];
    AptValue *mpThrownValue;
    int mnStackFrameBase;
    bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int=1, int=1, int=0);
    const unsigned char *runStream(const unsigned char *, AptCIH *, int, AptCharacterInst *);
private:
    static void _FunctionAptActionStoreRegister(AptActionInterpreter *const, LocalContextT *const);
    static void _FunctionAptActionTry(AptActionInterpreter *const, LocalContextT *const);
};
typedef char RegisterStackSize[sizeof(AptBasePtrStack)==12 ? 1 : -1];
typedef char RegisterContextSize[sizeof(AptActionInterpreter::LocalContextT)==28 ? 1 : -1];
typedef char RegisterFunctionOffset[offsetof(AptActionInterpreter,mpCurrentFunction)==0x30 ? 1 : -1];
typedef char RegisterThrownOffset[offsetof(AptActionInterpreter,mpThrownValue)==0x60 ? 1 : -1];

void AptActionInterpreter::_FunctionAptActionStoreRegister(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    AptScriptFunctionBase::SetRegisterValue(*data,p->stack.At(0));
}

// Target 706070..706234; donor supplies semantics; native proves +30 function,
// +8 frame hash and this 20-byte action header. runStream 7002C0 has a verified provider below.
struct RuntimeTryBlock { unsigned int trySize,catchSize,finallySize; unsigned char flags; unsigned char unused[2]; unsigned char caughtReg; const char *caughtName; };
void AptActionInterpreter::_FunctionAptActionTry(AptActionInterpreter *const p,LocalContextT *const c)
{
    unsigned int nPreStackSize=p->stack.GetSize();
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const RuntimeTryBlock *data=(const RuntimeTryBlock *)c->pInstruction;
    c->pInstruction+=sizeof(RuntimeTryBlock);
    c->pInstruction+=data->trySize;c->pInstruction+=data->catchSize;c->pInstruction+=data->finallySize;
    p->runStream((const unsigned char *)(data+1),c->pCurrentContext,data->trySize,c->pParentCharacter);
    if (p->mpThrownValue && (data->flags&1)) {
        AptValue *thrown=p->mpThrownValue;
        if (data->flags&4) AptScriptFunctionBase::SetRegisterValue(data->caughtReg,thrown);
        else {
            EAStringC param(data->caughtName);
            if(p->mpCurrentFunction) {
                if(!AptScriptFunctionBase::spFrameStack) ((Rva8D0D80Result *)p->mpCurrentFunction)->rva006FBED0();
                ((AptNativeHash *)((unsigned char *)AptScriptFunctionBase::spFrameStack+8))->Set(&param,thrown);
            } else p->setVariable((AptValue *)c->pCurrentContext,0,&param,thrown);
        }
        p->mpThrownValue->Release();p->mpThrownValue=0;
        p->runStream((const unsigned char *)(data+1)+data->trySize,c->pCurrentContext,data->catchSize,c->pParentCharacter);
    }
    if(data->flags&2) {
        AptValue *thrown=p->mpThrownValue;
        if(thrown) { thrown->AddRef();p->mpThrownValue->Release();p->mpThrownValue=0; }
        p->runStream((const unsigned char *)(data+1)+data->trySize+data->catchSize,c->pCurrentContext,data->finallySize,c->pParentCharacter);
        if(thrown && !p->mpThrownValue) { thrown->AddRef();p->mpThrownValue=thrown;thrown->Release(); }
    }
    unsigned int nPostStackSize=p->stack.GetSize();
    if (nPostStackSize>nPreStackSize) p->stack.rva006E3AA0(nPostStackSize-nPreStackSize);
    if((unsigned int)p->stack.GetSize()!=nPreStackSize) {
        g_bfmeAptAssertAtE17734("(uint32_t)pInterpreter->stack.GetSize() == nPreStackSize","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x2599);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
}
