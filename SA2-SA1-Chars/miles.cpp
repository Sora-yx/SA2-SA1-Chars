#include "pch.h"

static Trampoline* Tails_Callback_t = nullptr;

void Miles_SA1Voices_Init() {

    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_twe\\3.csb", "Resource\\gd_PC\\voices\\b03_twe\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_wk_btrl\\3.csb", "Resource\\gd_PC\\voices\\b03_wk_btrl\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\c_b03_twe\\3.csb", "Resource\\gd_PC\\voices\\c_b03_twe\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\event_adx_e.afs", "Resource\\gd_PC\\voices\\event_adx_e.afs");
    return;
}

void Miles_Init() {


    Miles_SA1Voices_Init();
}