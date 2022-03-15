#include "pch.h"

static Trampoline* Tails_Callback_t = nullptr;
static NJS_MATRIX TailsBellyMatrix;
static NJS_MATRIX TailsShoeLeftMatrix;
static NJS_MATRIX TailsShoeRightMatrix;


//ToDO: add the shoes upgrade
void Tails_Callback_r(NJS_OBJECT* model) {

    if (model == CharacterModels[208].Model->child->child->child->sibling->child->child) {
        memcpy(&TailsBellyMatrix, _nj_current_matrix_ptr_, 0x30u);
    }

    /*if (model == CharacterModels[208].Model->child->child->child->child->child->child->sibling->child->child->child->child->child->child->child) {
        memcpy(&TailsShoeLeftMatrix, _nj_current_matrix_ptr_, sizeof(NJS_MATRIX));
    }

    if (model == CharacterModels[208].Model->child->child->child->child->child->child->child->child->child->child->child->child->child) {
        memcpy(&TailsShoeRightMatrix, _nj_current_matrix_ptr_, sizeof(NJS_MATRIX));
    }*/

    FunctionPointer(void, original, (NJS_OBJECT * model), Tails_Callback_t->Target());
    original(model);
}

void __cdecl njScale_r(float a1, float a2, float a3) {

    NJS_OBJECT* badge = CharacterModels[240].Model;


    if (badge && (MainCharObj1[MilesCO2Extern->base.PlayerNum]->Status & Status_Ball) == 0) {

        njPushMatrixEx();
        memcpy(_nj_current_matrix_ptr_, &TailsBellyMatrix, 0x30u);
        njTranslate(nullptr, -0.5f, 0.1f, 0.0f);
        DrawObject(badge);
        njPopMatrixEx();
    }

    njScale_(a1, a2, a3);

}

void Miles_SA1Voices_Init() {

    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_twe\\3.csb", "Resource\\gd_PC\\voices\\b03_twe\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_wk_btrl\\3.csb", "Resource\\gd_PC\\voices\\b03_wk_btrl\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\c_b03_twe\\3.csb", "Resource\\gd_PC\\voices\\c_b03_twe\\3.csb");
    HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\event_adx_e.afs", "Resource\\gd_PC\\voices\\event_adx_e.afs");
    return;
}

void Miles_Init() {

    Tails_Callback_t = new Trampoline((int)0x750320, (int)0x750329, Tails_Callback_r);
    WriteCall((void*)0x7509CF, njScale_r);
    Miles_SA1Voices_Init();
}