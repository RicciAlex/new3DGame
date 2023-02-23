//=============================================================================
//
// bossStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bossStage.h"
#include "player.h"
#include "boss.h"
#include "application.h"
#include "rendering.h"

#include "inputKeyboard.h"
#include "cannon.h"



//コンストラクタ
CBossStage::CBossStage()
{

}

//デストラクタ
CBossStage::~CBossStage()
{
	
}


//初期化処理
HRESULT CBossStage::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(100.0f, -200.0f, 550.0f), 0);
	//CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(6000.0f, -200.0f, 1100.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(15000.0f, 15000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_ICE);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(15.0f);

	LoadMap("data\\STAGESET\\MapData\\BossStage.txt", CObject::TEXTURE_SNOW);

	CBoss* pBoss = CBoss::Create();
	
	CCannon::Create(D3DXVECTOR3(-4575.0f, -200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(-4325.0f, -200.0f, 0.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(4825.0f, -200.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(4575.0f, -200.0f, 0.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(-1125.0f, -200.0f, 2875.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(-1125.0f, -200.0f, 2625.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(1325.0f, -200.0f, 3975.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(1325.0f, -200.0f, 3725.0f), pBoss);

	return S_OK;
}

//終了処理
void CBossStage::Uninit(void)
{
	//基本クラスの終了処理
	CGame::Uninit();
}

//更新処理
void CBossStage::Update(void)
{
	//基本クラスの更新処理
	CGame::Update();
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBossStage* CBossStage::Create(void)
{
	CBossStage* pStage = new CBossStage;		//インスタンスを生成する

	if (FAILED(pStage->Init()))
	{//初期化処理

		return nullptr;
	}

	return pStage;		//生成したインスタンスを返す
}