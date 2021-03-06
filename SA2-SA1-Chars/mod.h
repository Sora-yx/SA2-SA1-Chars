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
void DLL_SA2ModDataInit();
void PatchAnimations();


extern HelperFunctions HelperFunctionsGlobal;

#define CURRENT_MATRIX _nj_current_matrix_ptr_

const int MilesjmpBallID = 230;
const int MilesCurlMDL = 255;
const int MilesFlightMDL = 269;
const int knuxCurlMDL = 236;


