#pragma once

extern HMODULE SA2Anim;
extern bool sonic;
extern bool miles;
extern bool knux;
extern bool amy;
extern bool SonicUpgrade;
extern bool milesUpgrade;
extern bool knuxUpgrade;
extern bool amyUpgrade;

void ReadConfig(const char* path);
void Disable_Jiggle();
void Sonic_Init();
void Miles_Init();
void Amy_Init();
void PatchAnimations();
void DLL_SA2ModDataInit();

extern HelperFunctions HelperFunctionsGlobal;

#define CURRENT_MATRIX _nj_current_matrix_ptr_