#include "pch.h"

static void __cdecl DrawMotion_Onion(NJS_MOTION* motion, NJS_OBJECT* obj, float frame)
{
	const auto frame_count = static_cast<float>(motion->nbFrame);

	const NJS_ARGB color_orig = GlobalSpriteColor;
	SaveConstantAttr();
	njControl3D_Backup();

	njControl3D_Add(nj_control_3d_flag_ & 0xFFFFFDDF | NJD_CONTROL_3D_CNK_BLEND_MODE | NJD_CONTROL_3D_CNK_CONSTANT_ATTR | NJD_CONTROL_3D_CONSTANT_MATERIAL);
	AddConstantAttrSADX(255, 2048); //2048 IS ALPHA IN SA2

	njColorBlendingMode(NJD_COLOR_BLENDING_SRCALPHA, NJD_SOURCE_COLOR);
	njColorBlendingMode(NJD_COLOR_BLENDING_ONE, NJD_DESTINATION_COLOR);

	float alpha = 0.75f;

	for (int i = 0; i < 2; ++i)
	{
		SetMaterial(alpha, 1.0, 1.0, 1.0);

		alpha -= 0.25f;
		frame -= 2.0f;

		if (frame < 0.0f)
		{
			frame = frame_count + frame;
		}

		DrawMotionAndObject(motion, obj, frame);
	}

	ResetMaterial();
	njControl3D_Restore();
	GlobalSpriteColor = color_orig;
	LoadConstantAttr();
}

void DrawSonicMotion(NJS_MOTION* Motion, NJS_OBJECT* obj, float frame)
{
	njCnkMotion(obj, Motion, frame); 

	if (SonicCO2PtrExtern && SonicCO2PtrExtern->base.AnimInfo.Current == 10)
		DrawMotion_Onion(Motion, obj, frame);
}

static void __declspec(naked) DrawSonicMotion_Asm()
{
	__asm
	{
		push[esp + 08h] // frame
		push[esp + 08h] // obj
		push ecx // mtn
		call DrawSonicMotion
		pop ecx // mtn
		add esp, 4 // obj
		add esp, 4 // frame
		retn
	}
}

void init_OnionBlur()
{
	WriteCall((void*)0x720687, DrawSonicMotion_Asm);
}