#pragma once

#define MATRIX_1A51A00 ((NJS_MATRIX_PTR)0x1A51A00) //matrix used for Sonic CallBack


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