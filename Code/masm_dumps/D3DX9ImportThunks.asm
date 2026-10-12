.386
.model flat

; d3dx9_27.dll import thunks -- retail 0x0062AF26..0x0062AFC8, six bytes each:
; `jmp dword ptr [__imp__<name>@<n>]` through the IAT slot the PE import
; directory names for that export. Import thunks are linker machinery (the
; d3dx9 import library supplies them). No C++ spelling both defines the
; stdcall name _<name>@<n> and reaches its own __imp__ slot: a dllimport
; declaration of the same extern "C" function cannot be defined (C2491), and
; a forwarding body under another name cannot carry the real name. That is
; the codegen blocker that keeps these real-ABI stubs in MASM, as
; CxxThrowExceptionImportThunk.asm does for msvcr71. The stdcall argument
; byte counts are the d3dx9 SDK declarations' and agree with the decorated
; names the matched callers reference. D3DXMatrixInverse (0x0062AF38) keeps
; its C++ forwarding row; D3DXVec4Transform, D3DXPlaneFromPointNormal and
; D3DXVec3Transform (0x0062AF4A..0x0062AF56) keep their address-named rows.

EXTERN __imp__D3DXMatrixMultiply@12:DWORD
EXTERN __imp__D3DXMatrixScaling@16:DWORD
EXTERN __imp__D3DXMatrixTranslation@16:DWORD
EXTERN __imp__D3DXAssembleShader@28:DWORD
EXTERN __imp__D3DXMatrixTranspose@8:DWORD
EXTERN __imp__D3DXMatrixRotationZ@8:DWORD
EXTERN __imp__D3DXFilterTexture@16:DWORD
EXTERN __imp__D3DXLoadSurfaceFromMemory@40:DWORD
EXTERN __imp__D3DXVec3TransformCoordArray@24:DWORD
EXTERN __imp__D3DXCreateTexture@32:DWORD
EXTERN __imp__D3DXCreateTextureFromFileInMemoryEx@60:DWORD
EXTERN __imp__D3DXLoadSurfaceFromFileInMemory@36:DWORD
EXTERN __imp__D3DXCheckTextureRequirements@28:DWORD
EXTERN __imp__D3DXLoadVolumeFromFileInMemory@36:DWORD
EXTERN __imp__D3DXCreateVolumeTexture@36:DWORD
EXTERN __imp__D3DXCreateVolumeTextureFromFileInMemoryEx@64:DWORD
EXTERN __imp__D3DXCreateCubeTextureFromFileInMemoryEx@56:DWORD
EXTERN __imp__D3DXGetImageInfoFromFileInMemory@12:DWORD
EXTERN __imp__D3DXCreateEffectFromFileA@32:DWORD
EXTERN __imp__D3DXCreateEffect@36:DWORD
EXTERN __imp__D3DXLoadSurfaceFromSurface@32:DWORD
EXTERN __imp__D3DXGetFVFVertexSize@4:DWORD
EXTERN __imp__D3DXGetShaderInputSemantics@12:DWORD

_TEXT SEGMENT

; retail 0x0062AF26
public _D3DXMatrixMultiply@12
_D3DXMatrixMultiply@12 PROC
    jmp  DWORD PTR __imp__D3DXMatrixMultiply@12
_D3DXMatrixMultiply@12 ENDP

; retail 0x0062AF2C
public _D3DXMatrixScaling@16
_D3DXMatrixScaling@16 PROC
    jmp  DWORD PTR __imp__D3DXMatrixScaling@16
_D3DXMatrixScaling@16 ENDP

; retail 0x0062AF32
public _D3DXMatrixTranslation@16
_D3DXMatrixTranslation@16 PROC
    jmp  DWORD PTR __imp__D3DXMatrixTranslation@16
_D3DXMatrixTranslation@16 ENDP

; retail 0x0062AF3E
public _D3DXAssembleShader@28
_D3DXAssembleShader@28 PROC
    jmp  DWORD PTR __imp__D3DXAssembleShader@28
_D3DXAssembleShader@28 ENDP

; retail 0x0062AF44
public _D3DXMatrixTranspose@8
_D3DXMatrixTranspose@8 PROC
    jmp  DWORD PTR __imp__D3DXMatrixTranspose@8
_D3DXMatrixTranspose@8 ENDP

; retail 0x0062AF5C
public _D3DXMatrixRotationZ@8
_D3DXMatrixRotationZ@8 PROC
    jmp  DWORD PTR __imp__D3DXMatrixRotationZ@8
_D3DXMatrixRotationZ@8 ENDP

; retail 0x0062AF62
public _D3DXFilterTexture@16
_D3DXFilterTexture@16 PROC
    jmp  DWORD PTR __imp__D3DXFilterTexture@16
_D3DXFilterTexture@16 ENDP

; retail 0x0062AF68
public _D3DXLoadSurfaceFromMemory@40
_D3DXLoadSurfaceFromMemory@40 PROC
    jmp  DWORD PTR __imp__D3DXLoadSurfaceFromMemory@40
_D3DXLoadSurfaceFromMemory@40 ENDP

; retail 0x0062AF6E
public _D3DXVec3TransformCoordArray@24
_D3DXVec3TransformCoordArray@24 PROC
    jmp  DWORD PTR __imp__D3DXVec3TransformCoordArray@24
_D3DXVec3TransformCoordArray@24 ENDP

; retail 0x0062AF74
public _D3DXCreateTexture@32
_D3DXCreateTexture@32 PROC
    jmp  DWORD PTR __imp__D3DXCreateTexture@32
_D3DXCreateTexture@32 ENDP

; retail 0x0062AF7A
public _D3DXCreateTextureFromFileInMemoryEx@60
_D3DXCreateTextureFromFileInMemoryEx@60 PROC
    jmp  DWORD PTR __imp__D3DXCreateTextureFromFileInMemoryEx@60
_D3DXCreateTextureFromFileInMemoryEx@60 ENDP

; retail 0x0062AF80
public _D3DXLoadSurfaceFromFileInMemory@36
_D3DXLoadSurfaceFromFileInMemory@36 PROC
    jmp  DWORD PTR __imp__D3DXLoadSurfaceFromFileInMemory@36
_D3DXLoadSurfaceFromFileInMemory@36 ENDP

; retail 0x0062AF86
public _D3DXCheckTextureRequirements@28
_D3DXCheckTextureRequirements@28 PROC
    jmp  DWORD PTR __imp__D3DXCheckTextureRequirements@28
_D3DXCheckTextureRequirements@28 ENDP

; retail 0x0062AF8C
public _D3DXLoadVolumeFromFileInMemory@36
_D3DXLoadVolumeFromFileInMemory@36 PROC
    jmp  DWORD PTR __imp__D3DXLoadVolumeFromFileInMemory@36
_D3DXLoadVolumeFromFileInMemory@36 ENDP

; retail 0x0062AF92
public _D3DXCreateVolumeTexture@36
_D3DXCreateVolumeTexture@36 PROC
    jmp  DWORD PTR __imp__D3DXCreateVolumeTexture@36
_D3DXCreateVolumeTexture@36 ENDP

; retail 0x0062AF98
public _D3DXCreateVolumeTextureFromFileInMemoryEx@64
_D3DXCreateVolumeTextureFromFileInMemoryEx@64 PROC
    jmp  DWORD PTR __imp__D3DXCreateVolumeTextureFromFileInMemoryEx@64
_D3DXCreateVolumeTextureFromFileInMemoryEx@64 ENDP

; retail 0x0062AF9E
public _D3DXCreateCubeTextureFromFileInMemoryEx@56
_D3DXCreateCubeTextureFromFileInMemoryEx@56 PROC
    jmp  DWORD PTR __imp__D3DXCreateCubeTextureFromFileInMemoryEx@56
_D3DXCreateCubeTextureFromFileInMemoryEx@56 ENDP

; retail 0x0062AFA4
public _D3DXGetImageInfoFromFileInMemory@12
_D3DXGetImageInfoFromFileInMemory@12 PROC
    jmp  DWORD PTR __imp__D3DXGetImageInfoFromFileInMemory@12
_D3DXGetImageInfoFromFileInMemory@12 ENDP

; retail 0x0062AFAA
public _D3DXCreateEffectFromFileA@32
_D3DXCreateEffectFromFileA@32 PROC
    jmp  DWORD PTR __imp__D3DXCreateEffectFromFileA@32
_D3DXCreateEffectFromFileA@32 ENDP

; retail 0x0062AFB0
public _D3DXCreateEffect@36
_D3DXCreateEffect@36 PROC
    jmp  DWORD PTR __imp__D3DXCreateEffect@36
_D3DXCreateEffect@36 ENDP

; retail 0x0062AFB6
public _D3DXLoadSurfaceFromSurface@32
_D3DXLoadSurfaceFromSurface@32 PROC
    jmp  DWORD PTR __imp__D3DXLoadSurfaceFromSurface@32
_D3DXLoadSurfaceFromSurface@32 ENDP

; retail 0x0062AFBC
public _D3DXGetFVFVertexSize@4
_D3DXGetFVFVertexSize@4 PROC
    jmp  DWORD PTR __imp__D3DXGetFVFVertexSize@4
_D3DXGetFVFVertexSize@4 ENDP

; retail 0x0062AFC2
public _D3DXGetShaderInputSemantics@12
_D3DXGetShaderInputSemantics@12 PROC
    jmp  DWORD PTR __imp__D3DXGetShaderInputSemantics@12
_D3DXGetShaderInputSemantics@12 ENDP

_TEXT ENDS
END
