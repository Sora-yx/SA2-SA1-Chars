#include "pch.h"

bool isNewTrick() {
	HMODULE amyNT = GetModuleHandle(L"SA2-Amy-New-Tricks");

	if (amyNT)
		return true;

	return false;
}

bool isBMiles() {
	HMODULE Miles = GetModuleHandle(L"SA2-Better-Miles");

	if (Miles)
		return true;

	return false;
}


typedef void(__cdecl* func)(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);

void SetCharacterAnim(uint16_t Index, uint16_t Count, NJS_MOTION* Animation)
{
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


void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = (ObjectFuncPtr)0x42E660;
	DrawObjMotion(obj);
}


void __cdecl AddConstantAttrSADX(NJD_FLAG _and, NJD_FLAG _or)
{
	nj_constant_attr_and_ |= _and;
	nj_constant_attr_or_ |= _or | NJD_FLAG_DOUBLE_SIDE;
}


const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

//Load Object File
ModelInfo* LoadMDL(const char* name, ModelFormat format) {
	std::string fullPath;

	fullPath = "resource\\gd_PC\\Models\\";


	fullPath += name;

	switch (format) {
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}

	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format) {
		PrintDebug("[SA2 Super Sonic] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[SA2 Super Sonic] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

ModelInfo* LoadJiggleMDL(const char* name, std::string characterName) {
	std::string fullPath;

	fullPath = "resource\\gd_PC\\jiggle\\" + characterName + "\\";
	fullPath += name;
	fullPath += ".sa2mdl";


	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == ModelFormat_Chunk) {
		PrintDebug("[SA1 Char] Loaded %s Jiggle model: %s.", ModelFormatStrings[(int)ModelFormat_Chunk - 1], name);
	}
	else {
		PrintDebug("[SA1 Char] Failed loading %s jiggle model: %s.", ModelFormatStrings[(int)ModelFormat_Chunk - 1], name);
	}

	return temp;
}

void FreeMDL(ModelInfo* pointer)
{
	if (pointer)
		delete(pointer);
}