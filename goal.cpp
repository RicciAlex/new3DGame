//=============================================================================
//
// goal.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "goal.h"
#include "application.h"
#include "game.h"
#include "player.h"

//コンストラクタ
CGoal::CGoal()
{

}

//デストラクタ
CGoal::~CGoal()
{

}

//初期化処理
HRESULT CGoal::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CGoal::Uninit(void)
{
	CModel::Uninit();
}

//更新処理
void CGoal::Update(void)
{
	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

		float fDistance = D3DXVec3Length(&distance);

		if (fDistance <= 80.0f)
		{
			CApplication::SetFade(CApplication::MODE_RESULTS);
		}
	}
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = new CGoal;

	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	pGoal->SetPos(pos);
	pGoal->SetModel(CModel::MODEL_FLAG);
	pGoal->SetShadowHeight(pos.y);

	return pGoal;
}