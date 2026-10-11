// cl: /MD
// The pool lock waits briefly on the event created during startup.
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *handle, unsigned long milliseconds);

// The event is WWLib thread.cpp test_event (HANDLE is void *), created by that
// unit's dynamic initializer; one definition, declared here.
extern void *test_event;

// MSVC folds a direct global argument into `push [memory]`; retail loads the
// event into eax first. The helper keeps that codegen choice localized.
__forceinline void *loadPoolYieldEvent()
{
    __asm mov eax, test_event
}

void BFMEPoolYield()
{
    WaitForSingleObject(loadPoolYieldEvent(), 1);
}
