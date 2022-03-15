#include "pch.h"

static Trampoline* Amy_Callback_t = nullptr;
static NJS_MATRIX AmyHeadMatrix;

void Amy_Callback_r(NJS_OBJECT* model) {

	if (model == CharacterModels[395].Model->child->child->child->sibling->child->child->child->child->sibling->child->child->sibling->sibling->child) {
		memcpy(&AmyHeadMatrix, _nj_current_matrix_ptr_, 0x30u);
	}

	FunctionPointer(void, original, (NJS_OBJECT * model), Amy_Callback_t->Target());
	original(model);
}

void DisplayAmyUpgrade() {

	njPushMatrixEx();

	if (SonicCO2PtrExtern->base.CharID2 == Characters_Amy) {

		NJS_OBJECT* warrior = CharacterModels[500].Model;

		if (warrior) {
			njPushMatrixEx();
			memcpy(_nj_current_matrix_ptr_, &AmyHeadMatrix, 0x30u);
			njTranslate(nullptr, -0.5f, 0.1f, 0.0f);
			DrawObject(warrior);
			njPopMatrixEx();
		}
	}
}

void Amy_Init() {

	if (isNewTrick()) //new trick will call the upgrade itself
		return;

	Amy_Callback_t = new Trampoline((int)0x71F040, (int)0x71F049, Amy_Callback_r);
	WriteCall((void*)0x720698, DisplayAmyUpgrade);
}