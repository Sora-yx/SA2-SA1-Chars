#include "pch.h"
#include "animation.h"

static Trampoline* Tails_Callback_t = nullptr;
static Trampoline* Tails_Main_t = nullptr;
Trampoline* Tails_JumpStart_t = nullptr;

void Miles_SA1Voices_Init() {

	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_twe\\3.csb", "Resource\\gd_PC\\voices\\b03_twe\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\b03_wk_btrl\\3.csb", "Resource\\gd_PC\\voices\\b03_wk_btrl\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MPB\\c_b03_twe\\3.csb", "Resource\\gd_PC\\voices\\c_b03_twe\\3.csb");
	HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\event_adx_e.afs", "Resource\\gd_PC\\voices\\event_adx_e.afs");
	return;
}

enum MilesModel {
	MRoot = 208,
	MRoot2,
	MRoot3,
	MHead,
	MHead2 = 215,
	MRightFootToe,
	MLeftFootToe,
	MRightHandParent,
	MLeftHandParent,
	MRightArm,
	MLeftArm,
	mTailNode,
	MRightTailRoot, //sadx counterpart MILES_OBJECT 14 and 15
	MLeftTailRoot,
	MRightHandParent2 = 226,
	MLeftHandParent2,
	mLeftTail, //sadx counterpart MILES_OBJECT 12 and 13
	mRightTail

};

enum MilesTailsModels {
	leftTail = 5,
	rightTail,
	flyingLeftTail,
	flyingRightTail,
	leftTailMorph,
	rightTailMorph,
	leftTailMorph2,
	rightTailMorph2,
	tailMorphRef,
};

enum MilesFlightModels {
	FlightrightTailRoot = 270, //SADX counterpart: MIELS OBJECT 16 / 17
	FlightleftTailRoot
};

static NJS_MATRIX Miles_RightHandMatrice;
static NJS_MATRIX Miles_LeftHandMatrice;
static NJS_MATRIX Miles_LeftFootMatrice;
static NJS_MATRIX Miles_RightFootMatrice;

void Miles_SetMatrixPosition(NJS_OBJECT* mdl)
{
	if (mdl == CharacterModels[MRightHandParent2].Model)
	{
		njSetMatrix(Miles_RightHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[MLeftHandParent2].Model)
	{
		njSetMatrix(Miles_LeftHandMatrice, CURRENT_MATRIX);
	}
}


DataArray(float, flt_1A5215C, 0x1A5215C, 12);
DataPointer(DWORD, dword_1AF0188, 0x1AF0188);
DataPointer(DWORD, dword_1AF0184, 0x1AF0184);

FunctionPointer(void, Miles_ManageTails, (EntityData1* data1, CharObj2Base* a2, TailsCharObj2* a3), 0x751090);

void MilesRotateTailsLikeAPropeller(TailsCharObj2* milesCO2, EntityData1* data)
{
	NJS_OBJECT* firstTail = CharacterModels[FlightrightTailRoot].Model;
	NJS_OBJECT* secondTail = CharacterModels[FlightleftTailRoot].Model;

	int v3;
	int v4;
	double v6;
	double v7;
	double v8;
	double v9;
	NJS_OBJECT* v10;

	v3 = FrameIncrement != 2 ? 2048 : 4096;

	v4 = (WORD)v3 + (unsigned __int16)firstTail->ang[0] & 0xFC00;
	firstTail->ang[1] = 0;
	secondTail->ang[1] = 0;
	firstTail->ang[2] = 0;
	secondTail->ang[2] = 0;

	firstTail->ang[0] = v4;
	secondTail->ang[0] = v4 & 0xF800;

	v6 = firstTail->scl[0];
	if (data->Timer == 0xFF)
	{
		firstTail->scl[0] = v6 + 0.02;
		v7 = firstTail->scl[1] - 0.02;
	}
	else
	{
		firstTail->scl[0] = v6 - 0.02;
		v7 = firstTail->scl[1] + 0.02;
	}
	firstTail->scl[1] = v7;
	if (firstTail->scl[0] < 1.0)
	{
		firstTail->scl[0] = 1.0;
		firstTail->scl[1] = 1.0;
	}
	if (firstTail->scl[0] > 1.3)
	{
		firstTail->scl[0] = 1.3;
		firstTail->scl[1] = 0.69999999;
	}
	v8 = firstTail->scl[0];
	v9 = firstTail->scl[1];
	firstTail->scl[2] = firstTail->scl[0];

	secondTail->scl[0] = v8;
	secondTail->scl[1] = v9;
	secondTail->scl[2] = v8;
}

void Miles_Callback_r(NJS_OBJECT* mdl) {

	NJS_MATRIX_PTR m = _nj_current_matrix_ptr_;
	TailsCharObj2* wk = (TailsCharObj2*)MilesCO2Extern;

	char pNum = wk->base.PlayerNum;

	if (mdl == CharacterModels[MRoot2].Model || mdl == CharacterModels[MilesCurlMDL].Model->child)
	{
		NJS_VECTOR pt{};
		njCalcPoint(m, &pt, &pt, FALSE);
		njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->head2_pos, &pt, 0);
		pt = { 1.0f, 0.0f, 0.0f };
		njCalcVector(&pt, &pt, m);
		njCalcVector(&pt, &wk->head2_vec, MATRIX_1A521BC);
		Miles_SetMatrixPosition(mdl);
		return;
	}
	if (mdl == CharacterModels[MRoot3].Model)
	{
		if (MainCharObj1[wk->base.PlayerNum]->Action == 1)
		{
			njRotateX(m, wk->base.TiltAngle);
		}
	}
	else
	{
		if (mdl != CharacterModels[MRightArm].Model)
		{
			if (mdl == CharacterModels[MLeftArm].Model)
			{
				if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) != 0)
				{
					njRotateZ(CURRENT_MATRIX, -(wk->base.HeldObject->EntityData2->field_30));
				}
			}
			else if (mdl == CharacterModels[MHead].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->head0_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->head0_vec, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MHead2].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->head1_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->head1_vec, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MRightHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->righthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, 1.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->righthand_vec0, MATRIX_1A521BC);
				pt = { 1.0f, -1.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->righthand_vec1, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MLeftHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->lefthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, -1.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->lefthand_vec0, MATRIX_1A521BC);
				pt = { 1.0f, -1.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->lefthand_vec1, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MRightFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->rightfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->rightfoot_vec, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MLeftFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->leftfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->leftfoot_vec, MATRIX_1A521BC);
			}
			else if (mdl == CharacterModels[MLeftTailRoot].Model)// Tail
			{
				NJS_VECTOR pt{};
				njCalcPoint(m, &pt, &pt, FALSE);
				njCalcPoint(MATRIX_1A521BC, (NJS_VECTOR*)&wk->tailnode_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector(&pt, &pt, m);
				njCalcVector(&pt, &wk->tailnode_vec, MATRIX_1A521BC);
				sub_42F770(flt_1A5215C);
			}
			Miles_SetMatrixPosition(mdl);
			return;
		}


		if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) == 0)
		{
			Miles_SetMatrixPosition(mdl);
			return;
		}
	}

}

int TailsMorphCounterThing;
float f;

//Basic model vs chunk
//vlist +2 = points?
//r nbpoints?

void __cdecl MilesReformTailDependOnX()
{
	/**NJS_CNK_MODEL* v0; // eax
	int v1; // esi
	NJS_CNK_MODEL* v2; // edi
	int v3; // ecx
	NJS_POINT3* v4; // eax
	NJS_POINT3* v5; // ebx
	int v6; // edx
	NJS_MODEL_SADX* v7; // esi

	v0 = MILES_MODELS[tailMorphRef];
	(v1) = TailsMorphCounterThing;
	v2 = MILES_MODELS[9];
	v3 = v0->r;
	v4 = (NJS_POINT3*)v0->vlist + 2;
	v5 = (NJS_POINT3*)v2->vlist + 2;
	v6 = TailsMorphCounterThing & 0x30000;
	if ((TailsMorphCounterThing & 0x30000u) > 0x20000)
	{
		if (v6 == 196608)
		{
			v1 = TailsMorphCounterThing + 1536;
			goto LABEL_10;
		}
	}
	else
	{
		if ((TailsMorphCounterThing & 0x30000) == 0x20000)
		{
			v1 = TailsMorphCounterThing + 2048;
			goto LABEL_10;
		}
		if (!v6)
		{
			v1 = TailsMorphCounterThing + 1792;
			goto LABEL_10;
		}
		if (v6 == 0x10000)
		{
			v1 = TailsMorphCounterThing + 1280;
		LABEL_10:
			TailsMorphCounterThing = v1;
			f = 0.40000001;
			goto LABEL_11;
		}
	}
LABEL_11:
	MilesReformPointDependOnXY(v4, v3, v5, v1 & 0xFF00, f);
	CalculatePlaneNormals(v2);
	CalculateVertexNormals(v2);
	v7 = MILES_MODELS[10];
	MilesReformPointDependOnXY(
		MILES_MODELS[13]->points,
		MILES_MODELS[13]->nbPoint,
		v7->points,
		((WORD)TailsMorphCounterThing + 20480) & 0xFF00,
		f);
	CalculatePlaneNormals(v7);
	CalculateVertexNormals(v7);
	CharacterModels[rightTailMorph2].Model = CharacterModels[leftTailMorph].Model;
	CharacterModels[tailMorphRef].Model = CharacterModels[rightTailMorph].Model;

	MILES_OBJECTS[13]->model = MILES_MODELS[10];*/
}

float SomeFrameNumberThing = 0.0f;
char SADXTimer = 0;
float TailsFlightTime = 0.0f;
int spinTimer = 0;
static bool tails_hack = false;


void DrawMiles_Motion(TailsCharObj2* mCO2, NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) {

	char pID = mCO2->base.PlayerNum;
	EntityData1* data1 = MainCharObj1[pID];
	AnimationIndex* sa2anim = getCharAnim_r();

	int curAnim = mCO2->base.AnimInfo.Current;

	if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0 && mCO2->base.AnimInfo.mtnmode != 2)
	{
		mdl = CharacterModels[MilesjmpBallID].Model;
		curAnim = 30;
		motion = sa2anim[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
	}


	return DrawMotionAndObject(motion, mdl, frame);
}

void DrawTail_Motion(NJS_MOTION* motion, NJS_OBJECT* obj, float frame)
{

	const NJS_ARGB color_orig = GlobalSpriteColor;
	SaveConstantAttr();

	OnControl3D(nj_control_3d_flag_ & 0xFFFFFDDF | NJD_CONTROL_3D_CNK_BLEND_MODE | NJD_CONTROL_3D_CNK_CONSTANT_ATTR | NJD_CONTROL_3D_CONSTANT_MATERIAL);
	AddConstantAttrSADX(0, 2048); //2048 IS ALPHA IN SA2

	njColorBlendingMode(NJD_COLOR_BLENDING_SRCALPHA, NJD_SOURCE_COLOR);
	njColorBlendingMode(NJD_COLOR_BLENDING_ONE, NJD_DESTINATION_COLOR);

	float alpha = 0.75f;

	SetMaterial(alpha, 1.0, 1.0, 1.0);
	DrawMotionAndObject(motion, obj, frame);

	ResetMaterial();
	GlobalSpriteColor = color_orig;
	LoadConstantAttr();
}

void DoSpinDashModelStretch(NJS_VECTOR a2)
{
	a2.x = 0.0;
	a2.y = -1.0;
	a2.z = 0.0;
	njTranslateV(0, &a2);
	njRotateZ(0, 0x2000);
	a2.x = 0.69999999;
	a2.y = 1.1;
	a2.z = 0.80000001;
	njScaleV_(&a2);
}

void __cdecl MoveTail(__int16 curAnim)
{
	float tailRotationDirection = 0.0f;
	NJS_OBJECT* tail = CharacterModels[MRightTailRoot].Model;

	if (curAnim >= 8 && curAnim <= 10)
	{
		tailRotationDirection = SomeFrameNumberThing + 0.0099999998;
	}
	else
	{
		tailRotationDirection = SomeFrameNumberThing - 0.0099999998;
	}
	SomeFrameNumberThing = tailRotationDirection;

	if (SomeFrameNumberThing > 0.0)
	{
		if (SomeFrameNumberThing < 1.0)
		{
			//MorphPoints(MILES_MODELS[9], MILES_MODELS[7], MILES_MODELS[11], co2->SomeFrameNumberThing);
			//MorphPoints(MILES_MODELS[10], MILES_MODELS[8], MILES_MODELS[12], co2->SomeFrameNumberThing);
			//S[12]->model = MILES_MODELS[11];
			//MILES_OBJECTS[13]->model = MILES_MODELS[12];
		}
		else
		{
			SomeFrameNumberThing = 1.0;
			//MILES_OBJECTS[12]->model = MILES_MODELS[7];
			//MILES_OBJECTS[13]->model = MILES_MODELS[8];
		}
	}
	else
	{
		SomeFrameNumberThing = 0.0;

		if ((unsigned __int16)tail->ang[0] >= 0x1000u)
		{
			tail->ang[0] += 819;
			CharacterModels[MLeftTailRoot].Model->ang[0] += 819;
		}
		else
		{
			tail->ang[0] = 0;
			CharacterModels[MLeftTailRoot].Model->ang[0] = 0;
		}
	}

	CharacterModels[MRightTailRoot].Model->ang[0] += (unsigned __int64)((SomeFrameNumberThing * 0.80000001 + 0.2)
		* 4096.0);
	CharacterModels[MLeftTailRoot].Model->ang[0] = CharacterModels[MRightTailRoot].Model->ang[0] - (unsigned __int64)(SomeFrameNumberThing * -32768.0);
}

void __cdecl Miles_Display_r(ObjectMaster* a1)
{

	double frame_temp; // st7
	__int16 anim; // cx
	NJS_OBJECT* leftTailRoot; // ebp
	NJS_OBJECT* rightTailRoot; // edi
	double v14; // st7
	Angle ang0; // ebx
	BOOL v16; // zf
	char v18; // cl
	int count; // [esp+Ch
	int v23; // [esp+10h]
	Angle ang0_; // [esp+
	Angle nbFramea; // [eh]
	Angle v28; // [esp+20
	NJS_VECTOR a2;
	NJS_VECTOR vs;
	int frame;
	int calcAngle;

	EntityData1* data1 = a1->Data1.Entity;
	TailsCharObj2* mCO2 = (TailsCharObj2*)a1->Data2.Undefined;
	CharObj2Base* co2 = a1->Data2.Character;

	__int16 curAnim2 = (unsigned __int16)co2->AnimInfo.Current;
	__int16 curAnim = co2->AnimInfo.Current;
	leftTailRoot = CharacterModels[MLeftTailRoot].Model; //MILES_OBJECTS[15];
	rightTailRoot = CharacterModels[MRightTailRoot].Model;//MILES_OBJECTS[14];

	if ((SADXTimer & 4) != 0)
	{
		TailsFlightTime = 0.0;
		SomeFrameNumberThing = 1.0;
	}

	if (co2->AnimInfo.mtnmode == 2)
	{
		curAnim2 = (unsigned __int16)co2->AnimInfo.Animation3; //last Index
	}

	if ((data1->Timer & 2) != '\0')
	{
		return;
	}

	njSetTexture(mCO2->TextureList);

	SaveControl3D();
	SetMaterial(1, 1, 1, 1);

	njPushMatrix(0);
	vs.z = 0.0;
	vs.x = 0.0;
	vs.y = co2->PhysData.Height * 0.5;

	njPushMatrix(_nj_unit_matrix_);

	njRotateZ_(CURRENT_MATRIX, data1->Rotation.z);
	njRotateX_(CURRENT_MATRIX, data1->Rotation.x);
	njRotateY_(CURRENT_MATRIX, (unsigned __int16)-LOWORD(data1->Rotation.y));

	njCalcVector(&vs, &a2, CURRENT_MATRIX);
	njPopMatrix(1u);
	a2.x = a2.x + data1->Position.x;
	a2.y = a2.y + data1->Position.y;
	a2.z = a2.z + data1->Position.z;
	njTranslateV(0, &a2);
	data1->Collision->CollisionArray->center = a2;

	njRotateZ_(CURRENT_MATRIX, data1->Rotation.z);
	njRotateX_(CURRENT_MATRIX, data1->Rotation.x);

	if (data1->Rotation.y != 0x8000)
		njRotateY_(CURRENT_MATRIX, (unsigned __int16)(0x8000 - LOWORD(data1->Rotation.y)));

	if (curAnim2 == 11 && (data1->Status & (Status_OnObjectColli | Status_Ground)) != 0)
	{
		DoSpinDashModelStretch(a2); //unused but maybe one day if we add the spin dash to Tails.
	}

	AnimationIndex* charAnimR = getCharAnim_r();

	if (co2->AnimInfo.mtnmode == 2)
	{
		DrawMiles_Motion(mCO2, mCO2->base.AnimInfo.Motion, CharacterModels[mCO2->base.AnimInfo.Animations[curAnim].ModelNum].Model, mCO2->base.AnimInfo.nframe);
	}
	else
	{
		char curAnim3 = co2->AnimInfo.Current;
		// Draw body (opaque)
		DrawMiles_Motion(mCO2, charAnimR[mCO2->base.AnimInfo.Animations[curAnim2].AnimNum].Animation, CharacterModels[mCO2->base.AnimInfo.Animations[curAnim].ModelNum].Model, mCO2->base.AnimInfo.nframe);
	}

	//if Tails isn't an AI, do the cool "draw multiple tails" effect

	if (data1->field_2 != 3) {

		anim = co2->AnimInfo.Current;
		v23 = 0;
		if (anim >= 90 && anim <= 93 || ((SADXTimer) & 4) != 0)
		{
			rightTailRoot = CharacterModels[FlightrightTailRoot].Model; //MILES_OBJECTS[16]; 
			leftTailRoot = CharacterModels[FlightleftTailRoot].Model;//MILES_OBJECTS[17];
			if (TailsFlightTime < 0.40000001)
			{
				calcAngle = 0x2000;
				goto DRAW_TAILS_TAILS;
			}
			if (anim == 90)
			{
				v23 = 1;
			}
			v14 = (1.0 - TailsFlightTime) * 1.6666666;
		}
		else
		{

			if (SomeFrameNumberThing == 0.0)
			{
				calcAngle = 640;
				goto DRAW_TAILS_TAILS;
			}
			v14 = SomeFrameNumberThing;
		}
		calcAngle = (unsigned __int64)(v14 * 8192.0);

	DRAW_TAILS_TAILS:
		ang0 = rightTailRoot->ang[0];
		ang0_ = ang0;
		nbFramea = leftTailRoot->ang[0];

		vs.x = -0.33333334;
		v28 = nbFramea - ang0;
		count = 2;

		do
		{
			if (vs.x <= 1.0)
			{
				if (vs.x < 0.0)
				{
					vs.x = 0.0;
				}
			}
			else
			{
				vs.x = 1.0;
			}

			ang0 -= calcAngle;

			rightTailRoot->ang[0] = ang0;
			leftTailRoot->ang[0] = ang0 + v28;
			if (co2->AnimInfo.mtnmode == 2)
			{
				DrawTail_Motion(co2->AnimInfo.Motion, CharacterModels[mCO2->base.AnimInfo.Animations[curAnim].ModelNum].Model, co2->AnimInfo.nframe);
			}
			else
			{
				DrawTail_Motion(charAnimR[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation, CharacterModels[mCO2->base.AnimInfo.Animations[curAnim].ModelNum].Model, mCO2->base.AnimInfo.nframe);
			}
			v16 = count == 1;
			vs.x = vs.x - 0.33333334;
			--count;
		} while (!v16);

		if (v23)
		{
			co2->AnimInfo.Current = 90;
			co2->AnimInfo.mtnmode = 2;
		}

		rightTailRoot->ang[0] = ang0_;
		leftTailRoot->ang[0] = nbFramea;
		rightTailRoot->ang[2] = 63488;
		leftTailRoot->ang[2] = 63488;
	}


	if (GameState != GameStates_Pause) {

		if (curAnim >= 90 && curAnim <= 93 //is tails flying
			|| (v18 = (SADXTimer), (v18 & 4) != 0))
		{
			MilesRotateTailsLikeAPropeller(mCO2, data1);// used when flying
		}
		else if ((unsigned __int16)curAnim >= Spin1 && (unsigned __int16)curAnim <= Spin10 || (v18 & 16) != 0)
		{
			//reset tail angle for spin attack
			CharacterModels[FlightrightTailRoot].Model->ang[0] = 0;
			CharacterModels[FlightleftTailRoot].Model->ang[0] = 0;
		}
		else
		{
			MilesReformTailDependOnX();
			MoveTail(curAnim);
		}
	}

	njPopMatrix(1u);
	ResetMaterial();
	LoadControl3D();
	return;

}

void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	EntityData1* data1 = obj->Data1.Entity;
	CharObj2Base* co2 = obj->Data2.Character;
	TailsCharObj2* mCo2 = (TailsCharObj2*)obj->Data2.Undefined;


	if (data1->Status & Status_Ball)
	{
		spinTimer++;
	}

}


static inline signed int Tails_JumpStart_Origin(CharObj2Base* co2, EntityData1* data)
{
	const auto target = Tails_JumpStart_t->Target();
	signed int result;

	__asm
	{
		mov ecx, [data]
		mov eax, [co2]
		call target
		mov result, eax
	}

	return result;
}

int Tails_JumpStart_r(CharObj2Base* co2, EntityData1* data)
{
	signed int result = Tails_JumpStart_Origin(co2, data);

	if (result == 1 && data->Action == Action_Jump)
	{
		data->Status |= Status_Ball;
	}

	return result;
}

static void __declspec(naked) Tails_JumpStartASM()
{
	__asm
	{
		push ecx
		push eax
		call Tails_JumpStart_r
		add esp, 4
		pop ecx
		retn
	}
}


void Miles_Init() {

	Miles_SA1Voices_Init();
	WriteJump((void*)0x750320, Miles_Callback_r);

	//	WriteJump((void*)0x751090, MilesRotateTailsLikeAPropeller);
	//WriteCall((void*)0x74D35E, Miles_ManageTails_r);

	WriteJump(Tails_Display, Miles_Display_r);

	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);
	/**WriteData<5>((int*)0x751968, 0x90);
	WriteData<5>((int*)0x751973, 0x90);*/

	if (!isBMiles())
		Tails_JumpStart_t = new Trampoline((int)0x751B80, (int)0x751B85, Tails_JumpStartASM);
}