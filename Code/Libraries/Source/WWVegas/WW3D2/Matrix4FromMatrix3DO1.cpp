// cl: /O1 /G7 /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
//
// Matrix4::Matrix4(const Matrix3D&) (0x0006A2CD): retail holds one size-optimised (/O1)
// out-of-line copy of the header body.
// The anchor below only makes this TU emit the inline body out of line; it is not retail code.
//
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix3d.h"
#include "aabox.h"
#include "always.h"
#include "shader.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "rinfo.h"
#include "wwdebug.h"
#include "d3d8.h"
#include "matrix4.h"
#include "texture.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"
#define DynamicIBAccessClass DonorDynamicIBAccessClass
#include "dx8indexbuffer.h"
#undef DynamicIBAccessClass
#define DX8_RECORD_MATRIX_CHANGE() matrix_changes++
#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++

// ?_bfmeMatrix4FromMatrix3DAnchor@@YA?AVMatrix4@@ABVMatrix3D@@@Z absent-from-retail
Matrix4 _bfmeMatrix4FromMatrix3DAnchor(const Matrix3D &m)
{
	return Matrix4(m);
}
