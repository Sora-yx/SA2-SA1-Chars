#include "pch.h"


const void* const loc_717028 = (const void*)0x717028;
__declspec(naked) void thingSonic() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_717028
	}
}


const void* const loc_71729f = (const void*)0x71729f;
__declspec(naked) void thingAmy() {
	__asm {

		sub esp, 4
		jmp loc_71729f
	}
}

void Disable_Jiggle()
{
	WriteJump((void*)0x716FDD, thingSonic);
	WriteJump((void*)0x717257, thingAmy);
}