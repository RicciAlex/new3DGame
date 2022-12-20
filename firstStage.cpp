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

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-500.0f, -200.0f, 3750.0f), Vec3Null, D3DXVECTOR2(50.0f, 100.0f), 20, 40);

	if (!pField)
	{
		return -1;
	}

	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(D3DXVECTOR2(0.3f, 0.35f));

	CGoal* pGoal = CGoal::Create(D3DXVECTOR3(0.0f, -200.0f, 3600.0f));

	if (!pGoal)
	{
		return -1;
	}

	CBg* pBg = CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), 3500.0f);

	if (pBg)
	{
		pBg->SetBg(Vec3Null, ColorCyan);
	}

	CModel* pModel = nullptr;
	CNail* pNail = nullptr;
	
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		pNail = CNail::Create(D3DXVECTOR3(-100.0f + (75.0f * nCnt), -199.0f, 400.0f));
	}

	pModel = CModel::Create(CModel::MODEL_GEAR, D3DXVECTOR3(-250.0f, -100.0f, 400.0f));
	pModel->SetShadowHeight(-199.9f);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));
	pModel->StartRotation(D3DXVECTOR3(-D3DX_PI * 0.01f, 0.0f, 0.0f));

	CMeshCube* pCube = CMeshCube::Create(D3DXVECTOR3(-600.0f, -125.0f, 100.0f), Vec3Null, 
		D3DXVECTOR3(50.0f, 10.0f, 50.0f), D3DXVECTOR3(1.0f, 0.0f, 2.0f), 200.0f);

	CButton::Create(D3DXVECTOR3(-100.0f, -200.0f, 100.0f));
	CButton* pButton = CButton::Create(D3DXVECTOR3(100.0f, -200.0f, 100.0f), ColorCyan, ColorYellow);
	pButton->SetTriggerableOnce(true);

	CShurikenTrap::Create(D3DXVECTOR3(0.0f, -200.0f, 500.0f), -D3DX_PI * 0.75f, 200.0f);

	CGoldStar* pStar = CGoldStar::Create(D3DXVECTOR3(100.0f, -130.0f, 0.0f));
	pStar->SetShadowHeight(-199.9f);

	CTriggerablePlatform::Create(D3DXVECTOR3(600.0f, -100.0f, 0.0f), 
		D3DXVECTOR3(-350.0f, -200.0f, 650.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 100.0f);

	pField = CMeshfield::Create(D3DXVECTOR3(700.0f, 120.0f, 100.0f), Vec3Null, D3DXVECTOR2(100.0f, 100.0f), 20, 3);

	/*CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(0.0f, -150.0f, 250.0f), D3DXVECTOR2(50.0f, 50.0f));
	pBillboard->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
	pBillboard->SetTexture(CObject::TEXTURE_GREEN);
	pBillboard = CBillboard::Create(D3DXVECTOR3(25.0f, -150.0f, 200.0f), D3DXVECTOR2(50.0f, 50.0f));
	pBillboard->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f));
	pBillboard->SetTexture(CObject::TEXTURE_BLUE);*/

	CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 200.0f), 2.0f, 120);
	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 200.0f), 2.0f, 60);
	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 200.0f), 2.0f, 30);

	CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 300.0f), 2.0f, 120, 40);
	CSpikeTrap::Create(D3DXVECTOR3(-400.0f, -200.0f, 400.0f), 2.0f, 120, 80);

	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 300.0f), 2.0f, 60, -20);
	CSpikeTrap::Create(D3DXVECTOR3(-300.0f, -200.0f, 400.0f), 2.0f, 60, -40);

	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 300.0f), 2.0f, 30, 10);
	CSpikeTrap::Create(D3DXVECTOR3(-200.0f, -200.0f, 400.0f), 2.0f, 30, 20);

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