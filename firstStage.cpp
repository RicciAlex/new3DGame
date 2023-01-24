//=============================================================================
//
// firstStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "firstStage.h"
#include "player.h"
#include "meshfield.h"
#include "inputKeyboard.h"
#include "application.h"
#include "goal.h"
#include "bg.h"
#include "nail.h"
#include "BoxHitbox.h"
#include "meshCube.h"
#include "button.h"
#include "ShurikenTrap.h"
#include "star.h"
#include "movingCube.h"
#include "triggerablePlatform.h"
#include "billboard.h"
#include "spikeTrap.h"
#include "object3D.h"
#include "accelerationFloor.h"
#include "cameraSetter.h"
#include "checkpoint.h"
#include "fallBoard.h"


#include "firePipe.h"
#include "fireEffect.h"
#include "fogBot.h"
#include "timer.h"
#include "PendulumClock.h"
#include "spawnTrigger.h"

//コンストラクタ
CFirstStage::CFirstStage()
{

}

//デストラクタ
CFirstStage::~CFirstStage()
{

}

//初期化処理
HRESULT CFirstStage::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(10000.0f, 10000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_GEAR_BG);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(10.0f);

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-375.0f, -200.0f, 2200.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field1.txt", 3);
	pField->SetTexture(CObject::TEXTURE_IRON);
	/*= CMeshfield::Create(D3DXVECTOR3(-500.0f, -200.0f, 3750.0f), Vec3Null, D3DXVECTOR2(50.0f, 100.0f), 20, 60)*/

	CBoxHitbox::Create(D3DXVECTOR3(0.0f, -200.0f, 1355.0f), Vec3Null, D3DXVECTOR3(375.0f, 299.0f, 30.0f), CHitbox::TYPE_NEUTRAL, nullptr);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(700.0f, 120.0f, 250.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field2.txt", 3);
	
	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-1800.0f, -200.0f, 800.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field3.txt", 3);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-1400.0f, -200.0f, 1200.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field4.txt", 3);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-1600.0f, -200.0f, 400.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field5.txt", 3);

	if (!pField)
	{
		return -1;
	}


	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-3700.0f, -200.0f, -3550.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field6.txt", 3);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-4825.0f, -200.0f, -3875.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field4.txt", 3);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_IRON);

	CBoxHitbox::Create(D3DXVECTOR3(755.0f, 120.0f - 405.0f, 0.0f), Vec3Null, D3DXVECTOR3(10.0f, 404.0f, 200.0f), CHitbox::TYPE_NEUTRAL, nullptr);
	CBoxHitbox::Create(D3DXVECTOR3(2150.0f, 120.0f, 0.0f), Vec3Null, D3DXVECTOR3(10.0f, 512.0f, 200.0f), CHitbox::TYPE_NEUTRAL, nullptr);
	CBoxHitbox::Create(D3DXVECTOR3(1500.0f, -230.0f, 0.0f), Vec3Null, D3DXVECTOR3(150.0f, 180.0f, 200.0f), CHitbox::TYPE_FALL, nullptr, -1, CHitbox::EFFECT_FALL);

	CGoal* pGoal = CGoal::Create(D3DXVECTOR3(0.0f, 100.0f, 2000.0f));

	if (!pGoal)
	{
		return -1;
	}

	CBg* pBg = CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), 3500.0f);

	if (pBg)
	{
		pBg->SetBg(Vec3Null, D3DXCOLOR(0.2f, 0.4f, 0.5f, 1.0f));
	}

	CModel* pModel = nullptr;
	CNail* pNail = nullptr;
	
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		pNail = CNail::Create(D3DXVECTOR3(-100.0f + (75.0f * nCnt), -199.0f, 400.0f));
	}

	pNail = CNail::Create(D3DXVECTOR3(-1360.0f, -199.0f, 1150.0f));
	pNail = CNail::Create(D3DXVECTOR3(-1200.0f, -199.0f, 1050.0f));
	pNail = CNail::Create(D3DXVECTOR3(-1275.0f, -199.0f, 1050.0f));

	CSpikeTrap::Create(D3DXVECTOR3(-1360.0f, -200.0f, 1050.0f), 5.0f, 120);

	CGoldStar* pStar = CGoldStar::Create(D3DXVECTOR3(-1225.0f, -130.0f, 1150.0f));
	pStar->SetShadowHeight(-199.9f);
	pStar = CGoldStar::Create(D3DXVECTOR3(-1600.0f, -130.0f, 500.0f));
	pStar->SetShadowHeight(-199.9f);

	/*pModel = CModel::Create(CModel::MODEL_GEAR, D3DXVECTOR3(-250.0f, -100.0f, 400.0f));
	pModel->SetShadowHeight(-199.9f);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));
	pModel->StartRotation(D3DXVECTOR3(-D3DX_PI * 0.01f, 0.0f, 0.0f));*/

	/*CMeshCube* pCube = CMeshCube::Create(D3DXVECTOR3(-600.0f, -125.0f, 100.0f), Vec3Null, 
		D3DXVECTOR3(50.0f, 10.0f, 50.0f), D3DXVECTOR3(1.0f, 0.0f, 2.0f), 200.0f);*/


	CShurikenTrap::Create(D3DXVECTOR3(200.0f, -200.0f, 600.0f), D3DX_PI, 200.0f, ColorBlue, ColorYellow);

	pStar = CGoldStar::Create(D3DXVECTOR3(100.0f, -130.0f, 0.0f));
	pStar->SetShadowHeight(-199.9f);

	CTriggerablePlatform::Create(D3DXVECTOR3(550.0f, -100.0f, 0.0f),
		D3DXVECTOR3(-200.0f, -200.0f, 600.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 150.0f);

	CTriggerablePlatform* pTrigger = CTriggerablePlatform::Create(D3DXVECTOR3(2050.0f, 350.0f, 0.0f),
		D3DXVECTOR3(-4700.0f, -200.0f, -4000.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 150.0f);

	CTriggerablePlatform* pPlatform = CTriggerablePlatform::Create(D3DXVECTOR3(0.0f, -175.0f, 1300.0f),
		D3DXVECTOR3(2325.0f, 634.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 100.0f);

	if (pPlatform)
	{
		pPlatform->SetOriginalPos(D3DXVECTOR3(0.0f, -75.0f, 1300.0f));
	}

	CMovingCube* pMCube = CMovingCube::Create(D3DXVECTOR3(-650.0f, -200.0f, 500.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 200.0f);

	/*CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 200.0f), 2.0f, 120);
	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 200.0f), 2.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 200.0f), 2.0f, 30);

	CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 300.0f), 2.0f, 120, 40);
	CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 400.0f), 2.0f, 120, 80);

	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 300.0f), 2.0f, 60, -20);
	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 400.0f), 2.0f, 60, -40);

	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 300.0f), 2.0f, 30, 10);
	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 400.0f), 2.0f, 30, 20);*/

	CSpikeTrap::Create(D3DXVECTOR3(-1700.0f, -200.0f, 600.0f), 3.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-1600.0f, -200.0f, 600.0f), 3.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -200.0f, 600.0f), 3.0f, 60);

	CSpikeTrap::Create(D3DXVECTOR3(-1700.0f, -200.0f, 500.0f), 3.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -200.0f, 500.0f), 3.0f, 60);

	CSpikeTrap::Create(D3DXVECTOR3(-1700.0f, -200.0f, 400.0f), 3.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-1600.0f, -200.0f, 400.0f), 3.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -200.0f, 400.0f), 3.0f, 60);

	/*CObject_3D* pObj3D = CObject_3D::Create();
	pObj3D->SetPos(D3DXVECTOR3(0.0f, -199.9f, 1000.0f));
	pObj3D->SetSize(D3DXVECTOR2(400.0f, 100.0f));
	pObj3D->SetTexture(CObject::TEXTURE_BLOCK);
	pObj3D->MoveTexCoordinates(D3DXVECTOR2(-0.005f, 0.0f));
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));

	CBoxHitbox* pH = CBoxHitbox::Create(D3DXVECTOR3(0.0f, -200.0f, 1000.0f), Vec3Null, D3DXVECTOR3(400.0f, 20.0f, 100.0f), CHitbox::TYPE_OBSTACLE, nullptr);
	pH->SetAcceleration(D3DXVECTOR3(1.0f, 0.0f, 0.0f));*/

	CAccelerationFloor* pFloor = CAccelerationFloor::Create(D3DXVECTOR3(0.0f, -199.0f, 1000.0f), D3DXVECTOR2(350.0f, 200.0f), D3DXVECTOR2(1.0f, 0.0f));
	pFloor->SetTextureTiling(2.0f, 2.0f);

	/*CModel::Create(CModel::MODEL_LEVER_BASE, D3DXVECTOR3(200.0f, -200.0f, 100.0f));
	pModel = CModel::Create(CModel::MODEL_LEVER, D3DXVECTOR3(200.0f, -195.0f, 100.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.25f));*/

	/*pField = CMeshfield::Create(D3DXVECTOR3(-600.0f, -150.0f, 600.0f), Vec3Null, D3DXVECTOR2(20.0f, 20.0f), 50, 50, 3, 0.5);
	pField->SetFieldPriority(-1);
	pField->SetSinusoidalHeight(0.1f, 0.0000001f);
	pField->SetAnimation(true, 0.05f, 4.0f);
	pField->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f));*/

	CCameraSetter::Create(D3DXVECTOR3(-1250.0f, -151.0f, -1900.0f), D3DXVECTOR3(500.0f, 100.0f, 5150.0f), CPlayer::CAMERA_POS_BACK);

	CCheckpoint::Create(D3DXVECTOR3(-300.0f, -200.1f, 150.0f), 100.0f);
	CCheckpoint::Create(D3DXVECTOR3( 300.0f, -200.1f, 150.0f), 100.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
	CCheckpoint::Create(D3DXVECTOR3(-3200.0f, -200.1f, -4000.0f), 100.0f);

	CFallBoard::Create(D3DXVECTOR3(0.0f, -200.0f, -200.0f), 220);

	CFirePipe::Create(D3DXVECTOR3(-300.0f, -200.0f, -200.0f));

	CFogbot::Create(D3DXVECTOR3(-300.0f, -175.0f, 600.0f), -199.9f);

	CPendulumClock::Create(D3DXVECTOR3(200.0f, -200.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -199.9f);

	CFirePipe::Create(D3DXVECTOR3(-3700.0f, -200.0f, -4000.0f));

	CFallBoard::Create(D3DXVECTOR3(-4000.0f, -200.0f, -4000.0f), 360);

	CFirePipe::Create(D3DXVECTOR3(-4300.0f, -200.0f, -4000.0f));

	CSpawnTrigger* pSpwnTrigger = CSpawnTrigger::Create();

	pNail = CNail::Create(D3DXVECTOR3(-1300.0f, -199.9f, -3000.0f));
	CSpikeTrap* pSpike = nullptr;


	pSpwnTrigger->AddTriggerPlatform(pTrigger);
	pSpwnTrigger->AddObject(pNail, -199.9f);

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -4200.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
		
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -4000.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
		
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -3800.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2700.0f + (200.0f * nCnt), -199.9f, -4100.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2700.0f + (200.0f * nCnt), -199.9f, -3900.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
	}



	/*pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1800.0f, -199.9f, -4100.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1800.0f, -199.9f, -4000.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1800.0f, -199.9f, -3900.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1800.0f, -199.9f, -3800.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);

	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2200.0f, -199.9f, -4200.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2200.0f, -199.9f, -4100.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2200.0f, -199.9f, -4000.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2200.0f, -199.9f, -3900.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2200.0f, -199.9f, -3800.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);

	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -199.9f, -4200.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -199.9f, -4100.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -199.9f, -4000.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -199.9f, -3900.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);
	pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1500.0f, -199.9f, -3800.0f), 2.0f, 60, 0);
	pSpwnTrigger->AddObject(pSpike, -199.9f);*/

	return S_OK;
}

//終了処理
void CFirstStage::Uninit(void)
{
	//基本クラスの終了処理
	CGame::Uninit();
}

//更新処理
void CFirstStage::Update(void)
{
	//基本クラスの更新処理
	CGame::Update();

#ifdef _DEBUG

	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		CApplication::SetFade(CApplication::MODE_RESULTS);
	}

#endif // DEBUG

}




//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CFirstStage* CFirstStage::Create(void)
{
	CFirstStage* pStage = new CFirstStage;		//インスタンスを生成する

	if (FAILED(pStage->Init()))
	{//初期化処理
		return nullptr;
	}

	return pStage;								//生成したインスタンスを返す
}