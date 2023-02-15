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
#include "magicCircleEffect.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CGoal::DEFAULT_RADIUS = 80.0f;				//ディフォルトの半径


//コンストラクタ
CGoal::CGoal()
{
	//メンバー変数をクリアする
	m_nPresentGem = 0;
}

//デストラクタ
CGoal::~CGoal()
{

}

//初期化処理
HRESULT CGoal::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CGoal::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CGoal::Update(void)
{
	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		if (m_nPresentGem <= 0)
		{
			D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

			float fDistance = D3DXVec3Length(&distance);

			if (fDistance <= DEFAULT_RADIUS)
			{
				CApplication::SetFade(CApplication::MODE_RESULTS);
			}
		}
	}
}

//宝石の加算処理
void CGoal::AddGem(void)
{
	m_nPresentGem++;
}

//宝石の減算処理
void CGoal::SubtractGem(void)
{
	m_nPresentGem--;
}




//=============================================================================
//
//								静的関数
//
//=============================================================================




//生成処理
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = new CGoal;		//インスタンスを生成する

	if (FAILED(pGoal->Init()))
	{//初期化処理
		return nullptr;
	}

	pGoal->SetPos(pos);						//位置の設定
	pGoal->SetModel(CModel::MODEL_FLAG);	//モデルの設定
	pGoal->SetShadowHeight(pos.y);			//影のY座標の設定

	CMagicCircleEffect::Create(D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));		//エフェクトの生成

	return pGoal;					//生成したインスタンスを返す
}