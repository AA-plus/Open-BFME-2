// cl: /MD
// ?Rva000A8F64Set@@YAX_N@Z @0x000A8F64 52B leaf.
// Pause-style timer flag: byte flag at 0x009B4CE0, time base at 0x009E6180,
// accumulated at 0x009E617C via winmm timeGetTime. Same-value early return,
// then set flag and record or accumulate.
// Evidence: mov al [esp+4] cmp [0xDB4CE0] al je test al mov [0xDB4CE0] al
// je IAT timeGetTime mov [0xDE6180] eax ret call sub add; caller 0x00062A2D.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern unsigned char g_aptHostStateStorage[32];
// Existing consumers also use +8 and +10..+1C. Provide the complete observed
// DB4CE0..DB4D00 storage, with the exact retail .data initial bytes. Original
// grouping is unknown; this preserves the single existing owner and its views.
__declspec(align(4)) unsigned char g_aptHostStateStorage[32] = {
 1,0,0,0, 3,0,0,0, 1,0,0,0, 0x33,0x33,0x33,0x3f,
 0,0,0x80,0x3f, 0,0,0x80,0x3f, 0,0,0x80,0x3f, 0,0,0x80,0x3f
};
extern unsigned long g_00DE6180;
// g_00DE6180: matched references place it at VA 0xde6180 (zero-filled .bss).
unsigned long g_00DE6180;
extern unsigned long g_00DE617C;
// g_00DE617C: matched references place it at VA 0xde617c (zero-filled .bss).
unsigned long g_00DE617C;

void __cdecl Rva000A8F64Set(bool enabled)
{
    if (g_aptHostStateStorage[0] == enabled)
        return;
    g_aptHostStateStorage[0] = enabled;
    if (enabled)
        g_00DE6180 = timeGetTime();
    else
    {
        unsigned long now = timeGetTime();
        g_00DE617C += now - g_00DE6180;
    }
}
