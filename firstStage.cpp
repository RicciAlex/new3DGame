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

	CMeshCube::Create(D3DXVECTOR3(-400.0f, -125.0f, 100.0f), Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f));
	CBoxHitbox::Create(D3DXVECTOR3(-400.0f, -135.0f, 100.0f), Vec3Null, D3DXVECTOR3(50.0f, 20.0f, 50.0f), CHitbox::TYPE_NEUTRAL, nullptr);
	
	CButton::Create(D3DXVECTOR3(-100.0f, -200.0f, 100.0f));
	CButton::Create(D3DXVECTOR3(100.0f, -200.0f, 100.0f), ColorCyan, ColorYellow);

	pModel = CModel::Create(CModel::MODEL_TRAP_PILLAR, D3DXVECTOR3(-250.0f, -200.0f, 100.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pModel->SetScale(1.5f);

	CShurikenTrap::Create(D3DXVECTOR3(0.0f, -200.0f, 500.0f), -D3DX_PI * 0.75f, 200.0f);

	CGoldStar* pStar = CGoldStar::Create(D3DXVECTOR3(100.0f, -130.0f, 0.0f));
	pStar->SetShadowHeight(-199.9f);

	return S_OK;
}

//終了処理
void CFirstStage::Uninit(void)
{
	CGame::Uninit();
}

//更新処理
void CFirstStage::Update(void)
{
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
	CFirstStage* pStage = new CFirstStage;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}