#pragma once

#define MATRIX_1A51A00 ((NJS_MATRIX_PTR)0x1A51A00) //matrix used for Sonic CallBack
typedef Uint32 NJD_SPRITE;
typedef Uint32 NJD_FLAG;
typedef Uint32 NJD_CONTROL_3D;
typedef DWORD _DWORD;
typedef Uint32 NJD_COLOR_TARGET;
typedef Uint32 NJD_COLOR_BLENDING;


DataPointer(int, dword_25F02D8, 0x25F02D8);
DataPointer(int, dword_1DEB6A4, 0x1DEB6A4);

FunctionPointer(void, DrawObjWithCallBack, (NJS_OBJECT* obj), 0x42E730);

//void __usercall sub_426420(int a1@<eax>, int a2)
static const void* const sub426420_ptr = (void*)0x426420;
static inline void sub_426420(int a1, int a2)
{
	__asm
	{
		push[a2]
		mov eax, a1
		call sub426420_ptr
		add esp, 4
	}
}

DataPointer(RenderInfo, Has_texlist_batadvPlayerChara_in_it, 0x2670544);
DataPointer(int, nj_control_3d_flag_, 0x025F02D8);

//void __usercall njColorBlendingMode(int a1@<eax>, int a2)
static const void* const njColorBlendingMode_ptr = (void*)0x426420;
static inline void njColorBlendingMode(NJD_COLOR_BLENDING mode, NJD_COLOR_TARGET target)
{
	__asm
	{
		push[target]
		mov eax, mode
		call njColorBlendingMode_ptr
		add esp, 4
	}
}

DataPointer(NJS_ARGB, GlobalSpriteColor, 0x25EFFD0);

DataPointer(int, nj_constant_attr_or_, 0x025F02D4);
DataPointer(int, nj_constant_attr_and_, 0x25F0268);
