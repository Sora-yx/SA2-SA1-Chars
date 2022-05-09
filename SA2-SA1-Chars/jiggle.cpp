#include "pch.h"

ModelInfo* MilesJiggleMDL[14];

ModelInfo** GetMilesJiggle()
{
	return MilesJiggleMDL;
}

void LoadMilesJiggleMDL()
{
	std::string chara = "miles";

	MilesJiggleMDL[9] = LoadJiggleMDL("9", chara);
	MilesJiggleMDL[10] = LoadJiggleMDL("10", chara);
	MilesJiggleMDL[11] = LoadJiggleMDL("11", chara);
	MilesJiggleMDL[12] = LoadJiggleMDL("12", chara);
	MilesJiggleMDL[13] = LoadJiggleMDL("13", chara);
}

const void* const loc_728399 = (const void*)0x728399;
__declspec(naked) void thingKnux() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_728399
	}
}



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
	WriteJump((void*)0x728346, thingKnux);

	LoadMilesJiggleMDL();
}