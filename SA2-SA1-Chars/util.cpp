#include "pch.h"

bool isNewTrick() {
	HMODULE amyNT = GetModuleHandle(L"SA2-Amy-New-Tricks");

	if (amyNT)
		return true;

	return false;
}

typedef void(__cdecl* func)(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);

void SetCharacterAnim(uint16_t Index, uint16_t Count, NJS_MOTION* Animation)
{
	HMODULE SA2Anim = GetModuleHandle(L"SA2-Anim-Break");

	if (!SA2Anim) 
		return;

	func Obj = reinterpret_cast<func>(::GetProcAddress(SA2Anim, "SetCharacterAnim")); 

	if (Obj)
	{
		(*Obj)(Index, Count, Animation);
		PrintDebug("Added new anim to charAnimR");
	}

	return;
}

typedef AnimationIndex* (CALLBACK* anim) (void);

AnimationIndex* getCharAnim_r()
{
	HMODULE SA2Anim = GetModuleHandle(L"SA2-Anim-Break");

	if (!SA2Anim)
		return nullptr;

	anim Obj = (anim)GetProcAddress(SA2Anim, "GetCharacterAnim_r");

	if (Obj)
	{
		AnimationIndex* Result = Obj();
		return Result;
	}

	return nullptr;
}