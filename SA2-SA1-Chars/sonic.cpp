#include "pch.h"

Trampoline* Sonic_Display_t;

enum SonicModel {
	SRoot = 0,
	SRightArm,
	SRightHandParent2 = 3,
	SRightHandParent = 5,
	SLeftArm = 8,
	SLeftHandParent2 = 10,
	SLeftHandParent = 12,
	SRightFootHeel = 18,
	SRightFootToe = 21,
	SLeftFootHeel = 32,
	SLeftFootToe,
	SHead = 35,
	SHead2 = 50,
};

static NJS_MATRIX S_RightHandMatrice;
static NJS_MATRIX S_LeftHandMatrice;
static NJS_MATRIX S_LeftFootMatrice;
static NJS_MATRIX S_RightFootMatrice;

void Sonic_SetMatrixPosition(NJS_OBJECT* mdl)
{
	if (mdl == CharacterModels[SRightHandParent2].Model)
	{
		njSetMatrix(S_RightHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SLeftHandParent2].Model)
	{
		njSetMatrix(S_LeftHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SRightFootHeel].Model)
	{
		njSetMatrix(S_RightFootMatrice, CURRENT_MATRIX);
	}
	else if (mdl == CharacterModels[SLeftFootHeel].Model)
	{
		njSetMatrix(S_LeftFootMatrice, CURRENT_MATRIX);
	}
}

void Sonic_Callback_r(NJS_OBJECT* mdl) {

	NJS_MATRIX_PTR m = _nj_current_matrix_ptr_;
	SonicCharObj2* wk = SonicCO2PtrExtern;

	char pNum = wk->base.PlayerNum;
	char char2 = wk->base.CharID2;

	if (char2 != Characters_Sonic)
	{
		return;
	}

	if (mdl == CharacterModels[SRoot].Model || mdl == CharacterModels[6].Model->child)
	{
		NJS_VECTOR pt{};
		njCalcPoint(m, &pt, &pt, FALSE);
		njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head2_pos, &pt, 0);
		pt = { 1.0f, 0.0f, 0.0f };
		njCalcVector(&pt, &pt, m);
		njCalcVector(&pt, &wk->head2_vec, MATRIX_1A51A00);
		Sonic_SetMatrixPosition(mdl);
		return;
	}
	if (mdl == CharacterModels[SRoot].Model)
	{
		if (MainCharObj1[wk->base.PlayerNum]->Action == 1)
		{
			njRotateX(m, wk->base.TiltAngle);
		}
	}
	else
	{
		if (mdl != CharacterModels[SRightArm].Model)
		{
			if (mdl == CharacterModels[SLeftArm].Model)
			{

				if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) != 0)
				{
					njRotateX(m, *((uint32_t*)wk->base.HeldObject->EntityData2 + 12));
				}
			}
			else if (mdl == CharacterModels[SHead].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head0_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->head0_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SHead2].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head1_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->head1_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SRightHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->righthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, 1.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->righthand_vec0, MATRIX_1A51A00);
				pt = { 0.0f, -1.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->righthand_vec1, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SLeftHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->lefthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, -1.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->lefthand_vec0, MATRIX_1A51A00);
				pt = { 0.0f, -1.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->lefthand_vec1, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SRightFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->rightfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->rightfoot_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SLeftFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A51A00, (NJS_VECTOR*)&wk->leftfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->leftfoot_vec, MATRIX_1A51A00);
			}
			Sonic_SetMatrixPosition(mdl);
			return;
		}
		if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) == 0)
		{
			Sonic_SetMatrixPosition(mdl);
			return;
		}
	}
}

void DisplaySonic_Upgrade(EntityData1* data1, SonicCharObj2* sonicCO2) {

	if (!sonicCO2 || AltCostume[sonicCO2->base.PlayerNum] != 0)
		return;


	int curAnim = sonicCO2->base.AnimInfo.Current;

	if (data1->Status & Status_Ball || curAnim == 30 || curAnim == 11 || curAnim == 12 || curAnim == 100)
		return;

	njSetTexture(sonicCO2->TextureList);
	njPushMatrixEx();

	NJS_OBJECT* CrystalRing = CharacterModels[25].Model;

	int upgrade = sonicCO2->base.Upgrades;

	if ((upgrade & (Upgrades_SonicFlameRing)) != 0)
	{
		if (CrystalRing)
		{
			NJS_VECTOR FRPos = { CrystalRing->child->pos[0], CrystalRing->child->pos[1], CrystalRing->child->pos[2] };
			memcpy(CURRENT_MATRIX, &S_LeftHandMatrice, 0x30u);
			DrawChunkModel(CrystalRing->getchunkmodel());// Display FlameRing Model on Sonic
			signed int v30 = dword_25F02D8;
			signed int v31 = *(DWORD*)&sonicCO2->field_36A[6];
			dword_1DEB6A4 = dword_25F02D8;
			SetMaterial(1, njCos(v31) * -1.0, 0, 0);
			njTranslateEx(&FRPos);
	
			DrawChunkModel(CrystalRing->child->getchunkmodel());// Display FlameRing animation on Sonic
			ResetMaterial();
			dword_25F02D8 = dword_1DEB6A4;
			sub_426420(8, 0);
			*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) = *(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) & 0xF7FFFFFF | 0x14000000;
		}
	}
	if ((upgrade & Upgrades_SonicBounceBracelet) != 0)
	{
		NJS_OBJECT* BounceMDL = CharacterModels[26].Model;

		if (BounceMDL)
		{
			memcpy(CURRENT_MATRIX, &S_RightHandMatrice, 0x30u);
			DrawChunkModel(BounceMDL->getchunkmodel());
			signed int v36 = *(DWORD*)&sonicCO2->field_36A[10];
			SetMaterial(1, njCos(v36) * -1.0, 0, 0);
			NJS_OBJECT* BounceChild = CharacterModels[26].Model->child;
			njTranslateEx((NJS_VECTOR*)BounceChild->pos);

			if (BounceChild->ang[2])
			{
				njRotateZ((float*)_nj_current_matrix_ptr_, BounceChild->ang[2]);
			}
			if (BounceChild->ang[1])
			{
				njRotateY(CURRENT_MATRIX, BounceChild->ang[1]);
			}
			if (BounceChild->ang[0])
			{
				njRotateX(CURRENT_MATRIX, BounceChild->ang[0]);
			}
			DrawChunkModel(BounceChild->getchunkmodel());
			ResetMaterial();
		}
	}
	if ((upgrade & Upgrades_SonicMagicGloves) != 0 && CharacterModels[27].Model)
	{
		NJS_OBJECT* GloveMDL = CharacterModels[27].Model;
		if (GloveMDL) {
			memcpy(CURRENT_MATRIX, &S_RightHandMatrice, 0x30u);
			DrawObjWithCallBack(GloveMDL);
		}
	}
	if ((upgrade & Upgrades_SonicLightShoes) != 0 && CharacterModels[14].Model)
	{
		NJS_OBJECT* ShoesMDL = CharacterModels[14].Model;
		if (ShoesMDL) {
			memcpy(CURRENT_MATRIX, &S_LeftFootMatrice, 0x30u);
			DrawObjWithCallBack(ShoesMDL);
			memcpy(CURRENT_MATRIX, &S_RightFootMatrice, 0x30u);
			DrawObjWithCallBack(CharacterModels[13].Model);
		}
	}

	njPopMatrixEx();
}

void __cdecl Sonic_Display_r(ObjectMaster* obj)
{

	ObjectFunc(origin, Sonic_Display_t->Target());
	origin(obj);

	DisplaySonic_Upgrade(obj->Data1.Entity, (SonicCharObj2*)obj->Data2.Undefined);

}

void Sonic_Init() {
	WriteJump((void*)0x71EAA0, Sonic_Callback_r);
	//Sonic_Display_t = new Trampoline((int)Sonic_Display, (int)Sonic_Display + 0x6, Sonic_Display_r);
}