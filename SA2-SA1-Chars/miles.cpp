#include "pch.h"

static Trampoline* Tails_Callback_t = nullptr;

const int MilesCurlMDL = 255;

void Miles_SA1Voices_Init() {

	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_twe\\3.csb", "Resource\\gd_PC\\voices\\b03_twe\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_wk_btrl\\3.csb", "Resource\\gd_PC\\voices\\b03_wk_btrl\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\c_b03_twe\\3.csb", "Resource\\gd_PC\\voices\\c_b03_twe\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\event_adx_e.afs", "Resource\\gd_PC\\voices\\event_adx_e.afs");
	return;
}

extern "C" {

	__declspec(dllexport) void MilesAdjustAnim()
	{
		TailsAnimList[0].AnimationSpeed = 0.50f;
		TailsAnimList[0].TransitionSpeed = 0.0625f;
		TailsAnimList[65].ModelNum = MilesCurlMDL;
		TailsAnimList[66].ModelNum = MilesCurlMDL;
		TailsAnimList[67].ModelNum = MilesCurlMDL;
		TailsAnimList[68].AnimNum = 15;
		TailsAnimList[95].AnimationSpeed = TailsAnimList[0].AnimationSpeed;
		TailsAnimList[95].TransitionSpeed = TailsAnimList[0].TransitionSpeed;
		TailsAnimList[18].AnimationSpeed = 1.0f;
		TailsAnimList[18].TransitionSpeed = 0.25f;
	}
}

void Miles_Init() {

	MilesAdjustAnim();
	Miles_SA1Voices_Init();
}