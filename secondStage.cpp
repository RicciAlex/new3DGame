//=============================================================================
//
// secondStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "secondStage.h"
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
#include "stalkingBot.h"
#include "sound.h"

#include "boss.h"
#include "twister.h"
#include "iceBoulder.h"

//コンストラクタ
CSecondStage::CSecondStage()
{

}

//デストラクタ
CSecondStage::~CSecondStage()
{

}

//初期化処理
HRESULT CSecondStage::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), 0);
	//CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(6000.0f, -200.0f, 1100.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(10000.0f, 10000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_ICE);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(10.0f);

	LoadMap("data\\STAGESET\\MapData\\SecondStage.txt", CObject::TEXTURE_SNOW);

	//CBoss::Create();

	return S_OK;
}

//終了処理
void CSecondStage::Uninit(void)
{
	//基本クラスの終了処理
	CGame::Uninit();
}

//更新処理
void CSecondStage::Update(void)
{
	//基本クラスの更新処理
	CGame::Update();

#ifdef _DEBUG

	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		CApplication::SetFade(CApplication::MODE_RESULTS);
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_T))
	{
		CTwister::Create(D3DXVECTOR3(0.0f, -200.0f, 200.0f));
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_G))
	{
		CIceBoulder::Create(D3DXVECTOR3(0.0f, -150.0f, 2000.0f));
	}

#endif // DEBUG

}




//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CSecondStage* CSecondStage::Create(void)
{
	CSecondStage* pStage = new CSecondStage;		//インスタンスを生成する

	if (FAILED(pStage->Init()))
	{//初期化処理
		return nullptr;
	}

	return pStage;								//生成したインスタンスを返す
}