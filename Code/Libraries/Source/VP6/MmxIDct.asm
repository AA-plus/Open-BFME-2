.686
.mmx
.model flat

; Clean room: reverse/vp6_cleanroom/specs/001d35e0.md, 001d3f30.md, 001d4650.md,
; 001d4d50.md and 001d5160.md plus retail only. No decoder source was
; consulted.
;
; The MMX inverse DCT family. Each routine is hand-scheduled assembly: cdecl,
; it saves the caller-saved EDX and ECX along with EBX (no compiled C++
; prologue does that), reads its arguments off ESP, and leaves the MMX state
; in use (the separately installed clear-state routine is the caller's
; cleanup). The constant block they all address is the one
; fillidctconstants builds (FillIdctConstants.cpp): lane masks, the seven
; cosine multipliers and the rounding word. MMX_idct1 (retail 0x001D45F0,
; between MMX_idct10 and MMX_idct_DX) is C++ in AverageBlockMmx.cpp.

EXTERN ?Rva009B3A00Table@@3PAGA:WORD     ; retail 0x00E22980

_TEXT SEGMENT

; MMX_idct -- retail 0x001D35E0, 2374 bytes (spec 001d35e0): dequantise plus
; full 8x8 inverse DCT (input, quantiser, output; 16-bit words). Multiplies
; the 64 transmission-order coefficients by the quantiser, scatters them
; through the zig-zag order into the layout whose 4x4 quadrants are
; transposed, runs the 1-D transform over the rows and then over the columns
; (the second pass rounds by 8 and shifts right by 4) and writes the block in
; natural raster order.
public _MMX_idct
_MMX_idct PROC
    push edx
    push ecx
    push ebx

    ; eax = input, edx = output, ebx = quantiser, ecx = constant block
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 18h]

    ; touch the output block's cache lines (values discarded)
    mov ecx, dword ptr [edx]
    mov ebx, dword ptr [edx + 1Ch]
    mov ecx, dword ptr [edx + 38h]
    mov ebx, dword ptr [edx + 54h]
    mov ecx, dword ptr [edx + 70h]
    mov ebx, dword ptr [edx + 7Ch]
    mov ebx, dword ptr [esp + 14h]
    lea ecx, ?Rva009B3A00Table@@3PAGA

    ; dequantise in transmission order and scatter through the lane masks
    ; into the quadrant-transposed internal layout
    movq mm0, qword ptr [eax]
    pmullw mm0, qword ptr [ebx]
    movq mm1, qword ptr [eax + 10h]
    pmullw mm1, qword ptr [ebx + 10h]
    movq mm2, qword ptr [ecx]
    movq mm3, mm0
    movq mm4, qword ptr [eax + 8]
    psrlq mm0, 10h
    pmullw mm4, qword ptr [ebx + 8]
    pand mm3, mm2
    movq mm5, mm0
    movq mm6, mm1
    pand mm5, mm2
    psllq mm6, 20h
    movq mm7, qword ptr [ecx + 18h]
    pxor mm0, mm5
    pand mm7, mm6
    por mm0, mm3
    pxor mm6, mm7
    por mm0, mm7
    movq mm7, qword ptr [ecx + 18h]
    movq mm3, mm4
    movq qword ptr [edx], mm0
    pand mm3, mm2
    movq mm0, qword ptr [eax + 20h]
    psllq mm3, 10h
    pmullw mm0, qword ptr [ebx + 20h]
    pand mm7, mm1
    por mm5, mm3
    por mm7, mm6
    movq mm3, qword ptr [eax + 18h]
    por mm7, mm5
    pmullw mm3, qword ptr [ebx + 18h]
    psrlq mm4, 10h
    movq qword ptr [edx + 10h], mm7
    movq mm5, mm4
    movq mm7, mm0
    psrlq mm4, 10h
    psrlq mm7, 30h
    movq mm6, mm2
    pand mm5, mm2
    pand mm6, mm4
    movq qword ptr [edx + 50h], mm7
    pxor mm4, mm6
    psrlq mm1, 20h
    por mm4, mm5
    movq mm7, qword ptr [ecx + 18h]
    pand mm1, mm2
    movq mm5, qword ptr [eax + 30h]
    psllq mm0, 10h
    pmullw mm5, qword ptr [ebx + 30h]
    pand mm7, mm0
    movq qword ptr [edx + 40h], mm1
    por mm7, mm4
    movq mm4, mm3
    pand mm3, mm2
    movq mm1, qword ptr [ecx + 10h]
    psllq mm3, 20h
    por mm7, mm3
    movq mm3, mm5
    psllq mm3, 30h
    pand mm1, mm0
    movq qword ptr [edx + 20h], mm7
    por mm6, mm3
    movq mm7, qword ptr [ecx + 8]
    por mm6, mm1
    movq mm1, qword ptr [eax + 38h]
    pand mm7, mm4
    pmullw mm1, qword ptr [ebx + 38h]
    por mm7, mm6
    pand mm0, qword ptr [ecx + 8]
    psrlq mm4, 20h
    movq qword ptr [edx + 30h], mm7
    movq mm6, mm4
    movq mm7, qword ptr [ecx + 18h]
    pand mm4, mm2
    movq mm3, qword ptr [ecx + 8]
    pand mm7, mm1
    pand mm3, mm5
    por mm0, mm4
    psllq mm3, 10h
    por mm7, mm0
    movq mm4, qword ptr [ecx + 10h]
    por mm7, mm3
    movq mm0, qword ptr [eax + 50h]
    movq mm3, mm4
    pmullw mm0, qword ptr [ebx + 50h]
    pand mm4, mm5
    movq qword ptr [edx + 8], mm7
    por mm6, mm4
    movq mm4, mm3
    psrlq mm6, 10h
    movq mm7, mm0
    pand mm4, mm1
    psllq mm7, 30h
    por mm6, mm4
    movq mm4, qword ptr [eax + 58h]
    por mm7, mm6
    pmullw mm4, qword ptr [ebx + 58h]
    psrlq mm3, 10h
    movq qword ptr [edx + 18h], mm7
    pand mm3, mm1
    psrlq mm5, 30h
    pand mm1, mm2
    movq mm6, qword ptr [eax + 68h]
    por mm5, mm3
    pmullw mm6, qword ptr [ebx + 68h]
    psrlq mm0, 10h
    movq mm7, mm4
    movq mm3, mm2
    psllq mm7, 30h
    pand mm3, mm0
    pxor mm0, mm3
    psllq mm3, 20h
    por mm7, mm5
    movq mm5, mm6
    pand mm6, qword ptr [ecx + 8]
    por mm7, mm3
    psllq mm6, 20h
    por mm0, mm1
    movq qword ptr [edx + 28h], mm7
    por mm0, mm6
    movq mm7, qword ptr [eax + 78h]
    movq mm6, mm5
    pmullw mm7, qword ptr [ebx + 78h]
    psrlq mm5, 20h
    pand mm6, mm2
    movq mm1, mm5
    movq qword ptr [edx + 38h], mm0
    pand mm1, mm2
    movq mm0, qword ptr [eax + 70h]
    movq mm3, mm7
    pmullw mm0, qword ptr [ebx + 70h]
    psllq mm3, 10h
    pand mm7, qword ptr [ecx + 18h]
    pxor mm5, mm1
    por mm6, mm5
    movq mm5, mm3
    pand mm5, qword ptr [ecx + 18h]
    por mm7, mm1
    movq mm1, qword ptr [eax + 60h]
    pxor mm3, mm5
    pmullw mm1, qword ptr [ebx + 60h]
    por mm7, mm3
    por mm6, mm5
    movq mm5, mm0
    movq qword ptr [edx + 78h], mm7
    psrlq mm5, 10h
    pand mm5, qword ptr [ecx + 10h]
    movq mm7, mm0
    por mm6, mm5
    pand mm0, mm2
    pxor mm7, mm0
    psllq mm0, 20h
    movq qword ptr [edx + 68h], mm6
    psrlq mm4, 10h
    movq mm5, qword ptr [eax + 48h]
    psllq mm7, 10h
    pmullw mm5, qword ptr [ebx + 48h]
    movq mm6, mm7
    movq mm3, qword ptr [ecx + 10h]
    psllq mm6, 10h
    pand mm7, qword ptr [ecx + 18h]
    pand mm3, mm1
    por mm7, mm0
    movq mm0, mm1
    pand mm1, qword ptr [ecx + 18h]
    por mm6, mm3
    movq mm3, mm4
    psrlq mm1, 20h
    pand mm3, mm2
    por mm7, mm1
    por mm7, mm3
    movq mm3, mm4
    pand mm3, qword ptr [ecx + 8]
    movq mm1, mm5
    movq qword ptr [edx + 58h], mm7
    psrlq mm5, 30h
    movq mm7, qword ptr [eax + 40h]
    por mm6, mm3
    pmullw mm7, qword ptr [ebx + 40h]
    por mm6, mm5
    pand mm4, qword ptr [ecx + 10h]
    psllq mm0, 20h
    movq qword ptr [edx + 48h], mm6
    movq mm6, mm0
    pand mm0, qword ptr [ecx + 18h]
    psllq mm6, 10h
    movq mm5, qword ptr [eax + 28h]
    movq mm3, mm1
    pmullw mm5, qword ptr [ebx + 28h]
    psrlq mm1, 10h
    pand mm1, qword ptr [ecx + 8]
    por mm0, mm4
    pand mm2, mm7
    por mm0, mm1
    por mm0, mm2
    psllq mm3, 10h
    movq mm4, mm3
    movq mm2, mm5
    movq qword ptr [edx + 70h], mm0
    psrlq mm2, 30h
    pand mm4, qword ptr [ecx + 10h]
    por mm6, mm2
    movq mm2, qword ptr [ecx + 8]
    por mm6, mm4
    pand mm2, mm7
    psllq mm3, 20h
    por mm3, qword ptr [edx + 50h]
    por mm6, mm2
    movq mm2, qword ptr [ecx + 18h]
    psllq mm5, 10h
    movq qword ptr [edx + 60h], mm6
    pand mm2, mm5
    movq mm6, qword ptr [ecx + 10h]
    pxor mm5, mm2
    pand mm6, mm7
    psrlq mm2, 20h
    pand mm7, qword ptr [ecx + 18h]
    por mm3, mm2
    por mm7, qword ptr [edx + 40h]
    por mm6, mm3
    por mm7, mm5
    movq qword ptr [edx + 50h], mm6
    movq qword ptr [edx + 40h], mm7

    ; first pass: natural rows 0..3, then rows 4..7, each group transposed
    movq mm2, qword ptr [edx + 30h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 18h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 38h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 20h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 28h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 10h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 8]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    movq mm3, qword ptr [edx + 20h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 10h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 8], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 18h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 10h]
    movq mm0, mm4
    movq qword ptr [edx + 38h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 28h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 10h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 20h], mm2
    movq mm2, qword ptr [edx + 70h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 58h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 50h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 78h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 60h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 68h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 50h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 60h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 40h]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 48h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 50h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    movq mm3, qword ptr [edx + 60h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 50h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx + 40h], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 48h], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 58h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx + 40h]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 50h]
    movq mm0, mm4
    movq qword ptr [edx + 78h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 68h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx + 40h], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 50h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 70h], mm4
    movq qword ptr [edx + 60h], mm2

    ; second pass: natural columns 0..3, then 4..7, rounded (+8) and >> 4
    movq mm2, qword ptr [edx + 30h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 50h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 70h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 20h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 60h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 10h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 40h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 20h]
    paddsw mm7, mm7
    movq qword ptr [edx + 20h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 10h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 40h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 30h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 60h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 50h], mm5
    movq qword ptr [edx + 70h], mm7
    movq qword ptr [edx], mm0
    movq mm2, qword ptr [edx + 38h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 58h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 18h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 78h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 28h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 68h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 18h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 28h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 8]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 48h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 18h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 28h]
    paddsw mm7, mm7
    movq qword ptr [edx + 28h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 18h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 48h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 38h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 68h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 58h], mm5
    movq qword ptr [edx + 78h], mm7
    movq qword ptr [edx + 8], mm0
    pop ebx
    pop ecx
    pop edx
    ret
_MMX_idct ENDP

; MMX_idct10 -- retail 0x001D3F30, 1724 bytes (spec 001d3f30): the reduced
; transform for blocks whose only non-zero coefficients are the first ten in
; transmission order. Dequantises and scatters all 64 words exactly as
; MMX_idct does, then runs the four-input transform over natural rows 0..3
; and over all eight columns (rows 4..7 taken as zero).
public _MMX_idct10
_MMX_idct10 PROC
    push edx
    push ecx
    push ebx

    ; eax = input, edx = output, ebx = quantiser, ecx = constant block
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 18h]

    ; touch the output block's cache lines (values discarded)
    mov ecx, dword ptr [edx]
    mov ebx, dword ptr [edx + 1Ch]
    mov ecx, dword ptr [edx + 38h]
    mov ebx, dword ptr [edx + 54h]
    mov ecx, dword ptr [edx + 70h]
    mov ebx, dword ptr [edx + 7Ch]
    mov ebx, dword ptr [esp + 14h]
    lea ecx, ?Rva009B3A00Table@@3PAGA

    ; dequantise all 64 words and scatter them as MMX_idct does
    movq mm0, qword ptr [eax]
    pmullw mm0, qword ptr [ebx]
    movq mm1, qword ptr [eax + 10h]
    pmullw mm1, qword ptr [ebx + 10h]
    movq mm2, qword ptr [ecx]
    movq mm3, mm0
    movq mm4, qword ptr [eax + 8]
    psrlq mm0, 10h
    pmullw mm4, qword ptr [ebx + 8]
    pand mm3, mm2
    movq mm5, mm0
    movq mm6, mm1
    pand mm5, mm2
    psllq mm6, 20h
    movq mm7, qword ptr [ecx + 18h]
    pxor mm0, mm5
    pand mm7, mm6
    por mm0, mm3
    pxor mm6, mm7
    por mm0, mm7
    movq mm7, qword ptr [ecx + 18h]
    movq mm3, mm4
    movq qword ptr [edx], mm0
    pand mm3, mm2
    movq mm0, qword ptr [eax + 20h]
    psllq mm3, 10h
    pmullw mm0, qword ptr [ebx + 20h]
    pand mm7, mm1
    por mm5, mm3
    por mm7, mm6
    movq mm3, qword ptr [eax + 18h]
    por mm7, mm5
    pmullw mm3, qword ptr [ebx + 18h]
    psrlq mm4, 10h
    movq qword ptr [edx + 10h], mm7
    movq mm5, mm4
    movq mm7, mm0
    psrlq mm4, 10h
    psrlq mm7, 30h
    movq mm6, mm2
    pand mm5, mm2
    pand mm6, mm4
    movq qword ptr [edx + 50h], mm7
    pxor mm4, mm6
    psrlq mm1, 20h
    por mm4, mm5
    movq mm7, qword ptr [ecx + 18h]
    pand mm1, mm2
    movq mm5, qword ptr [eax + 30h]
    psllq mm0, 10h
    pmullw mm5, qword ptr [ebx + 30h]
    pand mm7, mm0
    movq qword ptr [edx + 40h], mm1
    por mm7, mm4
    movq mm4, mm3
    pand mm3, mm2
    movq mm1, qword ptr [ecx + 10h]
    psllq mm3, 20h
    por mm7, mm3
    movq mm3, mm5
    psllq mm3, 30h
    pand mm1, mm0
    movq qword ptr [edx + 20h], mm7
    por mm6, mm3
    movq mm7, qword ptr [ecx + 8]
    por mm6, mm1
    movq mm1, qword ptr [eax + 38h]
    pand mm7, mm4
    pmullw mm1, qword ptr [ebx + 38h]
    por mm7, mm6
    pand mm0, qword ptr [ecx + 8]
    psrlq mm4, 20h
    movq qword ptr [edx + 30h], mm7
    movq mm6, mm4
    movq mm7, qword ptr [ecx + 18h]
    pand mm4, mm2
    movq mm3, qword ptr [ecx + 8]
    pand mm7, mm1
    pand mm3, mm5
    por mm0, mm4
    psllq mm3, 10h
    por mm7, mm0
    movq mm4, qword ptr [ecx + 10h]
    por mm7, mm3
    movq mm0, qword ptr [eax + 50h]
    movq mm3, mm4
    pmullw mm0, qword ptr [ebx + 50h]
    pand mm4, mm5
    movq qword ptr [edx + 8], mm7
    por mm6, mm4
    movq mm4, mm3
    psrlq mm6, 10h
    movq mm7, mm0
    pand mm4, mm1
    psllq mm7, 30h
    por mm6, mm4
    movq mm4, qword ptr [eax + 58h]
    por mm7, mm6
    pmullw mm4, qword ptr [ebx + 58h]
    psrlq mm3, 10h
    movq qword ptr [edx + 18h], mm7
    pand mm3, mm1
    psrlq mm5, 30h
    pand mm1, mm2
    movq mm6, qword ptr [eax + 68h]
    por mm5, mm3
    pmullw mm6, qword ptr [ebx + 68h]
    psrlq mm0, 10h
    movq mm7, mm4
    movq mm3, mm2
    psllq mm7, 30h
    pand mm3, mm0
    pxor mm0, mm3
    psllq mm3, 20h
    por mm7, mm5
    movq mm5, mm6
    pand mm6, qword ptr [ecx + 8]
    por mm7, mm3
    psllq mm6, 20h
    por mm0, mm1
    movq qword ptr [edx + 28h], mm7
    por mm0, mm6
    movq mm7, qword ptr [eax + 78h]
    movq mm6, mm5
    pmullw mm7, qword ptr [ebx + 78h]
    psrlq mm5, 20h
    pand mm6, mm2
    movq mm1, mm5
    movq qword ptr [edx + 38h], mm0
    pand mm1, mm2
    movq mm0, qword ptr [eax + 70h]
    movq mm3, mm7
    pmullw mm0, qword ptr [ebx + 70h]
    psllq mm3, 10h
    pand mm7, qword ptr [ecx + 18h]
    pxor mm5, mm1
    por mm6, mm5
    movq mm5, mm3
    pand mm5, qword ptr [ecx + 18h]
    por mm7, mm1
    movq mm1, qword ptr [eax + 60h]
    pxor mm3, mm5
    pmullw mm1, qword ptr [ebx + 60h]
    por mm7, mm3
    por mm6, mm5
    movq mm5, mm0
    movq qword ptr [edx + 78h], mm7
    psrlq mm5, 10h
    pand mm5, qword ptr [ecx + 10h]
    movq mm7, mm0
    por mm6, mm5
    pand mm0, mm2
    pxor mm7, mm0
    psllq mm0, 20h
    movq qword ptr [edx + 68h], mm6
    psrlq mm4, 10h
    movq mm5, qword ptr [eax + 48h]
    psllq mm7, 10h
    pmullw mm5, qword ptr [ebx + 48h]
    movq mm6, mm7
    movq mm3, qword ptr [ecx + 10h]
    psllq mm6, 10h
    pand mm7, qword ptr [ecx + 18h]
    pand mm3, mm1
    por mm7, mm0
    movq mm0, mm1
    pand mm1, qword ptr [ecx + 18h]
    por mm6, mm3
    movq mm3, mm4
    psrlq mm1, 20h
    pand mm3, mm2
    por mm7, mm1
    por mm7, mm3
    movq mm3, mm4
    pand mm3, qword ptr [ecx + 8]
    movq mm1, mm5
    movq qword ptr [edx + 58h], mm7
    psrlq mm5, 30h
    movq mm7, qword ptr [eax + 40h]
    por mm6, mm3
    pmullw mm7, qword ptr [ebx + 40h]
    por mm6, mm5
    pand mm4, qword ptr [ecx + 10h]
    psllq mm0, 20h
    movq qword ptr [edx + 48h], mm6
    movq mm6, mm0
    pand mm0, qword ptr [ecx + 18h]
    psllq mm6, 10h
    movq mm5, qword ptr [eax + 28h]
    movq mm3, mm1
    pmullw mm5, qword ptr [ebx + 28h]
    psrlq mm1, 10h
    pand mm1, qword ptr [ecx + 8]
    por mm0, mm4
    pand mm2, mm7
    por mm0, mm1
    por mm0, mm2
    psllq mm3, 10h
    movq mm4, mm3
    movq mm2, mm5
    movq qword ptr [edx + 70h], mm0
    psrlq mm2, 30h
    pand mm4, qword ptr [ecx + 10h]
    por mm6, mm2
    movq mm2, qword ptr [ecx + 8]
    por mm6, mm4
    pand mm2, mm7
    psllq mm3, 20h
    por mm3, qword ptr [edx + 50h]
    por mm6, mm2
    movq mm2, qword ptr [ecx + 18h]
    psllq mm5, 10h
    movq qword ptr [edx + 60h], mm6
    pand mm2, mm5
    movq mm6, qword ptr [ecx + 10h]
    pxor mm5, mm2
    pand mm6, mm7
    psrlq mm2, 20h
    pand mm7, qword ptr [ecx + 18h]
    por mm3, mm2
    por mm7, qword ptr [edx + 40h]
    por mm6, mm3
    por mm7, mm5
    movq qword ptr [edx + 50h], mm6
    movq qword ptr [edx + 40h], mm7

    ; first pass: natural rows 0..3 (inputs in0..in3), then the transposes
    movq mm2, qword ptr [edx + 30h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 20h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 20h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 10h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    movq mm3, qword ptr [edx + 20h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 10h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 8], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 18h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 10h]
    movq mm0, mm4
    movq qword ptr [edx + 38h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 28h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 10h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 20h], mm2

    ; second pass: natural columns 0..3, rounded (+8) and >> 4
    movq mm2, qword ptr [edx + 30h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 20h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 20h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 10h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 20h]
    paddsw mm7, mm7
    movq qword ptr [edx + 20h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 10h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 40h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 30h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 60h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 50h], mm5
    movq qword ptr [edx + 70h], mm7
    movq qword ptr [edx], mm0

    ; second pass: natural columns 4..7
    movq mm2, qword ptr [edx + 38h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 18h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 28h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 28h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 18h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 28h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 8]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx + 8]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 18h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 28h]
    paddsw mm7, mm7
    movq qword ptr [edx + 28h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 18h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 48h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 38h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 68h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 58h], mm5
    movq qword ptr [edx + 78h], mm7
    movq qword ptr [edx + 8], mm0
    pop ebx
    pop ecx
    pop edx
    ret
_MMX_idct10 ENDP

; MMX_idct_DX -- retail 0x001D4650, 1777 bytes (spec 001d4650): the decoder's
; full transform. The input and quantiser are already in the MMX storage
; order (table 0x00DB7D28), which is the quadrant-transposed internal layout,
; so the products are stored without a scatter; the two passes are those of
; MMX_idct.
public _MMX_idct_DX
_MMX_idct_DX PROC
    push edx
    push ecx
    push ebx

    ; eax = input, edx = output, ebx = quantiser, ecx = constant block
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 18h]

    ; touch the output block's cache lines (values discarded)
    mov ecx, dword ptr [edx]
    mov ebx, dword ptr [edx + 1Ch]
    mov ecx, dword ptr [edx + 38h]
    mov ebx, dword ptr [edx + 54h]
    mov ecx, dword ptr [edx + 70h]
    mov ebx, dword ptr [edx + 7Ch]
    mov ebx, dword ptr [esp + 14h]
    lea ecx, ?Rva009B3A00Table@@3PAGA

    ; dequantise straight into the internal layout
    movq mm0, qword ptr [eax]
    pmullw mm0, qword ptr [ebx]
    movq mm1, qword ptr [eax + 8]
    pmullw mm1, qword ptr [ebx + 8]
    movq mm2, qword ptr [eax + 10h]
    pmullw mm2, qword ptr [ebx + 10h]
    movq mm3, qword ptr [eax + 18h]
    pmullw mm3, qword ptr [ebx + 18h]
    movq mm4, qword ptr [eax + 20h]
    pmullw mm4, qword ptr [ebx + 20h]
    movq mm5, qword ptr [eax + 28h]
    pmullw mm5, qword ptr [ebx + 28h]
    movq mm6, qword ptr [eax + 30h]
    pmullw mm6, qword ptr [ebx + 30h]
    movq mm7, qword ptr [eax + 38h]
    pmullw mm7, qword ptr [ebx + 38h]
    movq qword ptr [edx], mm0
    movq qword ptr [edx + 8], mm1
    movq qword ptr [edx + 10h], mm2
    movq qword ptr [edx + 18h], mm3
    movq qword ptr [edx + 20h], mm4
    movq qword ptr [edx + 28h], mm5
    movq qword ptr [edx + 30h], mm6
    movq qword ptr [edx + 38h], mm7
    movq mm0, qword ptr [eax + 40h]
    pmullw mm0, qword ptr [ebx + 40h]
    movq mm1, qword ptr [eax + 48h]
    pmullw mm1, qword ptr [ebx + 48h]
    movq mm2, qword ptr [eax + 50h]
    pmullw mm2, qword ptr [ebx + 50h]
    movq mm3, qword ptr [eax + 58h]
    pmullw mm3, qword ptr [ebx + 58h]
    movq mm4, qword ptr [eax + 60h]
    pmullw mm4, qword ptr [ebx + 60h]
    movq mm5, qword ptr [eax + 68h]
    pmullw mm5, qword ptr [ebx + 68h]
    movq mm6, qword ptr [eax + 70h]
    pmullw mm6, qword ptr [ebx + 70h]
    movq mm7, qword ptr [eax + 78h]
    pmullw mm7, qword ptr [ebx + 78h]
    movq qword ptr [edx + 40h], mm0
    movq qword ptr [edx + 48h], mm1
    movq qword ptr [edx + 50h], mm2
    movq qword ptr [edx + 58h], mm3
    movq qword ptr [edx + 60h], mm4
    movq qword ptr [edx + 68h], mm5
    movq qword ptr [edx + 70h], mm6
    movq qword ptr [edx + 78h], mm7

    ; first pass: natural rows 0..3, then rows 4..7, each group transposed
    movq mm2, qword ptr [edx + 30h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 18h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 38h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 20h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 28h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 10h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 8]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    movq mm3, qword ptr [edx + 20h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 10h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 8], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 18h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 10h]
    movq mm0, mm4
    movq qword ptr [edx + 38h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 28h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 10h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 20h], mm2
    movq mm2, qword ptr [edx + 70h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 58h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 50h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 78h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 60h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 68h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 50h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 60h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 40h]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 48h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 50h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    movq mm3, qword ptr [edx + 60h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 50h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx + 40h], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 48h], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 58h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx + 40h]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 50h]
    movq mm0, mm4
    movq qword ptr [edx + 78h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 68h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx + 40h], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 50h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 70h], mm4
    movq qword ptr [edx + 60h], mm2

    ; second pass: natural columns 0..3, then 4..7, rounded (+8) and >> 4
    movq mm2, qword ptr [edx + 30h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 50h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 70h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 20h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 60h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 10h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 40h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 20h]
    paddsw mm7, mm7
    movq qword ptr [edx + 20h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 10h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 40h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 30h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 60h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 50h], mm5
    movq qword ptr [edx + 70h], mm7
    movq qword ptr [edx], mm0
    movq mm2, qword ptr [edx + 38h]
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm7, qword ptr [edx + 58h]
    pmulhw mm4, mm6
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm6, mm7
    movq mm5, mm1
    pmulhw mm1, mm2
    movq mm3, qword ptr [edx + 18h]
    pmulhw mm5, mm7
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    paddw mm6, mm7
    paddw mm2, mm1
    movq mm1, qword ptr [edx + 78h]
    paddw mm7, mm5
    movq mm5, mm0
    pmulhw mm0, mm3
    paddsw mm4, mm7
    pmulhw mm5, mm1
    movq mm7, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    paddw mm0, mm3
    pmulhw mm3, mm7
    movq mm2, qword ptr [edx + 28h]
    pmulhw mm7, mm1
    paddw mm5, mm1
    movq mm1, mm2
    pmulhw mm2, qword ptr [ecx + 28h]
    psubsw mm3, mm5
    movq mm5, qword ptr [edx + 68h]
    paddsw mm0, mm7
    movq mm7, mm5
    psubsw mm0, mm4
    pmulhw mm5, qword ptr [ecx + 28h]
    paddw mm2, mm1
    pmulhw mm1, qword ptr [ecx + 48h]
    paddsw mm4, mm4
    paddsw mm4, mm0
    psubsw mm3, mm6
    paddw mm5, mm7
    paddsw mm6, mm6
    pmulhw mm7, qword ptr [ecx + 48h]
    paddsw mm6, mm3
    movq qword ptr [edx + 18h], mm4
    psubsw mm1, mm5
    movq mm4, qword ptr [ecx + 38h]
    movq mm5, mm3
    pmulhw mm3, mm4
    paddsw mm7, mm2
    movq qword ptr [edx + 28h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 8]
    pmulhw mm0, mm4
    paddw mm5, mm3
    movq mm3, qword ptr [edx + 48h]
    psubsw mm5, mm1
    paddw mm2, mm0
    psubsw mm6, mm3
    movq mm0, mm6
    pmulhw mm6, mm4
    paddsw mm3, mm3
    paddsw mm1, mm1
    paddsw mm3, mm0
    paddsw mm1, mm5
    pmulhw mm4, mm3
    paddsw mm6, mm0
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 18h]
    paddsw mm2, mm6
    paddw mm4, mm3
    psubsw mm2, mm1
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 28h]
    paddsw mm7, mm7
    movq qword ptr [edx + 28h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 18h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 48h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 38h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 68h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 58h], mm5
    movq qword ptr [edx + 78h], mm7
    movq qword ptr [edx + 8], mm0
    pop ebx
    pop ecx
    pop edx
    ret
_MMX_idct_DX ENDP

; MMX_idct10_DX -- retail 0x001D4D50, 1034 bytes (spec 001d4d50): the
; decoder's reduced transform (2..10 coefficients). Dequantises the four
; storage spans that hold natural rows 0..3, columns 0..3, zeroes rows 4..7
; and runs the four-input transform of MMX_idct10.
public _MMX_idct10_DX
_MMX_idct10_DX PROC
    push edx
    push ecx
    push ebx

    ; eax = input, edx = output, ebx = quantiser, ecx = constant block
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 18h]

    ; touch the output block's cache lines (values discarded)
    mov ecx, dword ptr [edx]
    mov ebx, dword ptr [edx + 1Ch]
    mov ecx, dword ptr [edx + 38h]
    mov ebx, dword ptr [edx + 54h]
    mov ecx, dword ptr [edx + 70h]
    mov ebx, dword ptr [edx + 7Ch]
    mov ebx, dword ptr [esp + 14h]
    lea ecx, ?Rva009B3A00Table@@3PAGA
    movq mm0, qword ptr [eax]
    pmullw mm0, qword ptr [ebx]
    movq mm1, qword ptr [eax + 10h]
    pmullw mm1, qword ptr [ebx + 10h]
    movq mm2, qword ptr [eax + 20h]
    pmullw mm2, qword ptr [ebx + 20h]
    movq mm3, qword ptr [eax + 30h]
    pmullw mm3, qword ptr [ebx + 30h]
    movq qword ptr [edx], mm0
    pxor mm5, mm5
    movq qword ptr [edx + 8], mm5
    movq qword ptr [edx + 10h], mm1
    movq qword ptr [edx + 18h], mm5
    movq qword ptr [edx + 20h], mm2
    movq qword ptr [edx + 28h], mm5
    movq qword ptr [edx + 30h], mm3
    movq qword ptr [edx + 38h], mm5
    movq qword ptr [edx + 40h], mm5
    movq qword ptr [edx + 48h], mm5
    movq qword ptr [edx + 50h], mm5
    movq qword ptr [edx + 58h], mm5
    movq qword ptr [edx + 60h], mm5
    movq qword ptr [edx + 68h], mm5
    movq qword ptr [edx + 70h], mm5
    movq qword ptr [edx + 78h], mm5

    ; first pass: natural rows 0..3, with the transposes
    movq mm2, qword ptr [edx + 30h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 20h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 20h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 10h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    movq mm3, qword ptr [edx + 20h]
    psubsw mm4, mm7
    paddsw mm1, mm1
    paddsw mm7, mm7
    paddsw mm1, mm2
    paddsw mm7, mm4
    psubsw mm4, mm3
    paddsw mm3, mm3
    psubsw mm6, mm5
    paddsw mm5, mm5
    paddsw mm3, mm4
    paddsw mm5, mm6
    psubsw mm7, mm0
    paddsw mm0, mm0
    movq qword ptr [edx + 10h], mm1
    paddsw mm0, mm7
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 8], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 18h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 10h]
    movq mm0, mm4
    movq qword ptr [edx + 38h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 28h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 10h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 20h], mm2

    ; second pass: all eight natural columns, rounded (+8) and >> 4
    movq mm2, qword ptr [edx + 30h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 10h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 20h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 20h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 10h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 20h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 10h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 20h]
    paddsw mm7, mm7
    movq qword ptr [edx + 20h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 10h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 40h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 30h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 60h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 50h], mm5
    movq qword ptr [edx + 70h], mm7
    movq qword ptr [edx], mm0
    movq mm2, qword ptr [edx + 38h]
    nop
    movq mm6, qword ptr [ecx + 30h]
    movq mm4, mm2
    movq mm1, qword ptr [ecx + 40h]
    pmulhw mm4, mm6
    movq mm3, qword ptr [edx + 18h]
    pmulhw mm1, mm2
    movq mm0, qword ptr [ecx + 20h]
    paddw mm4, mm2
    pxor mm6, mm6
    paddw mm2, mm1
    movq mm5, qword ptr [edx + 28h]
    pmulhw mm0, mm3
    movq mm1, mm5
    paddw mm0, mm3
    pmulhw mm3, qword ptr [ecx + 50h]
    psubsw mm6, mm2
    pmulhw mm5, qword ptr [ecx + 28h]
    psubsw mm0, mm4
    movq mm7, qword ptr [edx + 28h]
    paddsw mm4, mm4
    paddw mm7, mm5
    paddsw mm4, mm0
    pmulhw mm1, qword ptr [ecx + 48h]
    psubsw mm3, mm6
    movq qword ptr [edx + 18h], mm4
    paddsw mm6, mm6
    movq mm4, qword ptr [ecx + 38h]
    paddsw mm6, mm3
    movq mm5, mm3
    pmulhw mm3, mm4
    movq qword ptr [edx + 28h], mm6
    movq mm2, mm0
    movq mm6, qword ptr [edx + 8]
    pmulhw mm0, mm4
    paddw mm5, mm3
    paddw mm2, mm0
    psubsw mm5, mm1
    pmulhw mm6, mm4
    paddw mm6, qword ptr [edx + 8]
    paddsw mm1, mm1
    movq mm4, mm6
    paddsw mm1, mm5
    psubsw mm6, mm2
    paddsw mm2, mm2
    movq mm0, qword ptr [edx + 18h]
    paddsw mm2, mm6
    psubsw mm2, mm1
    nop
    paddsw mm2, qword ptr [ecx + 58h]
    paddsw mm1, mm1
    paddsw mm1, mm2
    psraw mm2, 4
    psubsw mm4, mm7
    psraw mm1, 4
    movq mm3, qword ptr [edx + 28h]
    paddsw mm7, mm7
    movq qword ptr [edx + 28h], mm2
    paddsw mm7, mm4
    movq qword ptr [edx + 18h], mm1
    psubsw mm4, mm3
    paddsw mm4, qword ptr [ecx + 58h]
    paddsw mm3, mm3
    paddsw mm3, mm4
    psraw mm4, 4
    psubsw mm6, mm5
    psraw mm3, 4
    paddsw mm6, qword ptr [ecx + 58h]
    paddsw mm5, mm5
    paddsw mm5, mm6
    psraw mm6, 4
    movq qword ptr [edx + 48h], mm4
    psraw mm5, 4
    movq qword ptr [edx + 38h], mm3
    psubsw mm7, mm0
    paddsw mm7, qword ptr [ecx + 58h]
    paddsw mm0, mm0
    paddsw mm0, mm7
    psraw mm7, 4
    movq qword ptr [edx + 68h], mm6
    psraw mm0, 4
    movq qword ptr [edx + 58h], mm5
    movq qword ptr [edx + 78h], mm7
    movq qword ptr [edx + 8], mm0
    pop ebx
    pop ecx
    pop edx
    ret
_MMX_idct10_DX ENDP

; MMX_idct3 -- retail 0x001D5160, 777 bytes (spec 001d5160; nothing in retail
; references it): three-coefficient transform without dequantisation (input,
; output). Places input words 0, 1, 2 at natural (0,0), (0,1) and (1,0),
; zeroes the rest and transforms rows 0..1 and then every column, all in
; wrapping arithmetic.
public _MMX_idct3
_MMX_idct3 PROC
    push edx
    push ecx
    push ebx

    ; eax = input, edx = output, ecx = constant block
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 14h]

    ; touch the output block's cache lines (values discarded)
    mov ecx, dword ptr [edx]
    mov ebx, dword ptr [edx + 1Ch]
    mov ecx, dword ptr [edx + 38h]
    mov ebx, dword ptr [edx + 54h]
    mov ecx, dword ptr [edx + 70h]
    mov ebx, dword ptr [edx + 7Ch]
    lea ecx, ?Rva009B3A00Table@@3PAGA
    movq mm0, qword ptr [eax]
    pxor mm1, mm1
    movq mm2, qword ptr [ecx]
    movq mm3, mm0
    pxor mm4, mm4
    psrlq mm0, 10h
    pand mm3, mm2

    ; place words 0..2 through the lane masks
    movq mm5, mm0
    movq mm6, mm1
    pand mm5, mm2
    movq mm7, qword ptr [ecx + 18h]
    pxor mm0, mm5
    pand mm7, mm6
    por mm0, mm3
    pxor mm6, mm7
    por mm0, mm7
    movq mm7, qword ptr [ecx + 18h]
    movq mm3, mm4
    movq qword ptr [edx], mm0
    pand mm3, mm2
    psllq mm3, 10h
    pand mm7, mm1
    por mm5, mm3
    por mm7, mm6
    por mm7, mm5
    psrlq mm4, 10h

    ; zero the remaining rows
    movq qword ptr [edx + 10h], mm7
    movq qword ptr [edx + 20h], mm4
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 8], mm4
    movq qword ptr [edx + 18h], mm4
    movq qword ptr [edx + 28h], mm4
    movq qword ptr [edx + 38h], mm4
    movq qword ptr [edx + 78h], mm4
    movq qword ptr [edx + 68h], mm4
    movq qword ptr [edx + 58h], mm4
    movq qword ptr [edx + 48h], mm4
    movq qword ptr [edx + 70h], mm4
    movq qword ptr [edx + 60h], mm4
    movq qword ptr [edx + 50h], mm4
    movq qword ptr [edx + 40h], mm4

    ; first pass: natural rows 0 and 1 (inputs in0, in1), then the transposes
    movq mm7, qword ptr [edx + 10h]
    movq mm0, qword ptr [ecx + 20h]
    movq mm3, qword ptr [ecx + 50h]
    pmulhw mm0, mm7
    pmulhw mm3, mm7
    movq mm6, qword ptr [edx]
    movq mm4, qword ptr [ecx + 38h]
    paddw mm0, mm7
    movq mm1, mm6
    pmulhw mm6, mm4
    movq mm2, mm0
    movq mm5, mm3
    pmulhw mm2, mm4
    pmulhw mm5, mm4
    paddw mm6, mm1
    movq mm4, mm6
    paddw mm2, mm0
    paddw mm5, mm3
    movq mm7, mm6
    movq mm1, mm5
    psubw mm6, mm2
    psubw mm4, mm3
    psubw mm7, mm0
    paddw mm2, mm2
    paddw mm3, mm3
    paddw mm0, mm0
    paddw mm2, mm6
    paddw mm3, mm4
    psubw mm2, mm1
    psubw mm6, mm5
    paddw mm1, mm1
    paddw mm5, mm5
    paddw mm0, mm7
    paddw mm1, mm2
    movq qword ptr [edx + 10h], mm1
    paddw mm5, mm6
    movq mm1, mm4
    punpcklwd mm4, mm5
    movq qword ptr [edx], mm0
    punpckhwd mm1, mm5
    movq mm0, mm6
    punpcklwd mm6, mm7
    movq mm5, mm4
    punpckldq mm4, mm6
    punpckhdq mm5, mm6
    movq mm6, mm1
    movq qword ptr [edx + 8], mm4
    punpckhwd mm0, mm7
    movq qword ptr [edx + 18h], mm5
    punpckhdq mm6, mm0
    movq mm4, qword ptr [edx]
    punpckldq mm1, mm0
    movq mm5, qword ptr [edx + 10h]
    movq mm0, mm4
    movq qword ptr [edx + 38h], mm6
    punpcklwd mm0, mm5
    movq qword ptr [edx + 28h], mm1
    punpckhwd mm4, mm5
    movq mm5, mm2
    punpcklwd mm2, mm3
    movq mm1, mm0
    punpckldq mm0, mm2
    punpckhdq mm1, mm2
    movq mm2, mm4
    movq qword ptr [edx], mm0
    punpckhwd mm5, mm3
    movq qword ptr [edx + 10h], mm1
    punpckhdq mm4, mm5
    punpckldq mm2, mm5
    movq qword ptr [edx + 30h], mm4
    movq qword ptr [edx + 20h], mm2
    movq mm7, qword ptr [edx + 10h]
    movq mm0, qword ptr [ecx + 20h]
    movq mm3, qword ptr [ecx + 50h]
    pmulhw mm0, mm7
    pmulhw mm3, mm7
    movq mm6, qword ptr [edx]
    movq mm4, qword ptr [ecx + 38h]
    paddw mm0, mm7
    movq mm1, mm6
    pmulhw mm6, mm4
    movq mm2, mm0
    movq mm5, mm3
    pmulhw mm2, mm4
    pmulhw mm5, mm4
    paddw mm6, mm1
    movq mm4, mm6
    paddw mm6, qword ptr [ecx + 58h]
    paddw mm4, qword ptr [ecx + 58h]
    paddw mm2, mm0
    paddw mm5, mm3
    movq mm7, mm6
    movq mm1, mm5
    psubw mm6, mm2
    psubw mm4, mm3
    psubw mm7, mm0
    paddw mm2, mm2
    paddw mm3, mm3
    paddw mm0, mm0
    paddw mm2, mm6
    paddw mm3, mm4
    psraw mm4, 4
    movq qword ptr [edx + 40h], mm4
    psraw mm3, 4
    movq qword ptr [edx + 30h], mm3
    psubw mm2, mm1
    psubw mm6, mm5
    paddw mm1, mm1
    paddw mm5, mm5
    paddw mm0, mm7
    paddw mm1, mm2
    psraw mm7, 4
    psraw mm2, 4
    psraw mm0, 4
    psraw mm1, 4
    movq qword ptr [edx + 70h], mm7
    movq qword ptr [edx], mm0
    movq qword ptr [edx + 10h], mm1
    movq qword ptr [edx + 20h], mm2
    movq qword ptr [edx + 10h], mm1
    paddw mm5, mm6
    psraw mm5, 4
    movq qword ptr [edx + 50h], mm5
    psraw mm6, 4
    movq qword ptr [edx + 60h], mm6
    movq mm7, qword ptr [edx + 18h]
    movq mm0, qword ptr [ecx + 20h]
    movq mm3, qword ptr [ecx + 50h]
    pmulhw mm0, mm7
    pmulhw mm3, mm7
    movq mm6, qword ptr [edx + 8]
    movq mm4, qword ptr [ecx + 38h]
    paddw mm0, mm7
    movq mm1, mm6
    pmulhw mm6, mm4
    movq mm2, mm0
    movq mm5, mm3
    pmulhw mm2, mm4
    pmulhw mm5, mm4
    paddw mm6, mm1
    movq mm4, mm6
    paddw mm6, qword ptr [ecx + 58h]
    paddw mm4, qword ptr [ecx + 58h]
    paddw mm2, mm0
    paddw mm5, mm3
    movq mm7, mm6
    movq mm1, mm5
    psubw mm6, mm2
    psubw mm4, mm3
    psubw mm7, mm0
    paddw mm2, mm2
    paddw mm3, mm3
    paddw mm0, mm0
    paddw mm2, mm6
    paddw mm3, mm4
    psraw mm4, 4
    movq qword ptr [edx + 48h], mm4
    psraw mm3, 4
    movq qword ptr [edx + 38h], mm3
    psubw mm2, mm1
    psubw mm6, mm5
    paddw mm1, mm1
    paddw mm5, mm5
    paddw mm0, mm7
    paddw mm1, mm2
    psraw mm7, 4
    psraw mm2, 4
    psraw mm0, 4
    psraw mm1, 4
    movq qword ptr [edx + 78h], mm7
    movq qword ptr [edx + 8], mm0
    movq qword ptr [edx + 18h], mm1
    movq qword ptr [edx + 28h], mm2
    movq qword ptr [edx + 18h], mm1
    paddw mm5, mm6
    psraw mm5, 4
    movq qword ptr [edx + 58h], mm5
    psraw mm6, 4
    movq qword ptr [edx + 68h], mm6
    pop ebx
    pop ecx
    pop edx
    ret
_MMX_idct3 ENDP

_TEXT ENDS
END
