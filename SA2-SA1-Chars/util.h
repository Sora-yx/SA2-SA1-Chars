#pragma once

typedef Uint32 NJD_FLAG;

bool isNewTrick();

void SetCharacterAnim(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);
AnimationIndex* getCharAnim_r();
void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void __cdecl AddConstantAttrSADX(NJD_FLAG _and, NJD_FLAG _or);