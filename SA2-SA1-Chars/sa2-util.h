#pragma once

#define MATRIX_1A51A00 ((NJS_MATRIX_PTR)0x1A51A00) //matrix used for Sonic CallBack
#define MATRIX_1A521BC ((NJS_MATRIX_PTR)0x1A521BC) //matrix used for Miles CallBack

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


DataPointer(NJS_ARGB, GlobalSpriteColor, 0x25EFFD0);



static const void* const sub_42F770Ptr = (void*)0x42F770;
static inline void sub_42F770(float* a1)
{
	__asm
	{
		mov eax, [a1]
		call sub_42F770Ptr
	}
}

static const void* const doJigglePtr = (void*)0x4479E0;
static inline void DoJiggleThing(JiggleInfo* a1)
{
	__asm
	{
		mov eax, [a1]
		call doJigglePtr
	}
}


//int __usercall BAMS_SubWrap@<eax>(int result@<eax>, int ang0@<edx>, __int16 ang1@<cx>)

static const void* const BAMS_SubWrapPtr = (void*)0x446960;
static inline signed int BAMS_SubWrap(int a, int ang0, __int16 ang1)
{
	signed int result;
	__asm
	{
		mov cx, [ang1]
		mov edx, [ang0]
		mov eax, [a]
		call BAMS_SubWrapPtr
		mov result, eax
	}
	return result;
}