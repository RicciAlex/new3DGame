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
#include "score.h"
#include "game.h"
#include "player.h"
#include "magicCircleEffect.h"
#include "object2D.h"
#include <string>


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CGoal::DEFAULT_RADIUS = 80.0f;				//ディフォルトの半径


//コンストラクタ
CGoal::CGoal()
{
	//メンバー変数をクリアする
	m_nPresentGem = 0;
	m_bCreate = false;

	m_pGemNeeded = nullptr;
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
	//UIの破棄処理
	if (m_pGemNeeded)
	{//nullチェック
		m_pGemNeeded->Release();		//メモリを解放する
		m_pGemNeeded = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CGoal::Update(void)
{
	if (!m_bCreate && CApplication::GetModeInstance()->IsGame())
	{
		m_bCreate = true;

		CObject_2D* pObj = CObject_2D::Create(5, D3DXVECTOR3(600.0f, 40.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), CObject::TEXTURE_GEM_ICON);

		if (pObj)
		{
			pObj->SetTextureParameter(1, 3, 2, INT_MAX);
		}

		if (!m_pGemNeeded)
		{
			m_pGemNeeded = CUIString::Create(D3DXVECTOR3(640.0f, 40.0f, 0.0f), D3DXVECTOR2(75.0f, 40.0f), ColorYellow, "0/3");
		}
	}

	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		if (m_nPresentGem <= 0)
		{
			D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

			float fDistance = D3DXVec3Length(&distance);

			if (fDistance <= DEFAULT_RADIUS)
			{
				if (CApplication::GetMode() != CApplication::MODE_TUTORIAL)
				{
					CScore* pScore = CApplication::GetScore();
					CMode* pMode = CApplication::GetModeInstance();

					if (pScore && pMode)
					{
						if (pMode->IsGame())
						{
							pScore->SetTime(CApplication::GetGame()->GetTime());
						}
					}

					if (CApplication::GetMode() == CApplication::MODE_FIRST_STAGE)
					{
						CApplication::SetFade(CApplication::MODE_RESULTS);
					}
					else if (CApplication::GetMode() == CApplication::MODE_SECOND_STAGE)
					{
						CApplication::SetFade(CApplication::MODE_BOSS_STAGE);
					}
				}
				else
				{
					CApplication::SetFade(CApplication::MODE_STAGE_SELECT);
				}
			}
		}
	}
}

//宝石の加算処理
void CGoal::AddGem(void)
{
	m_nPresentGem++;

	if (m_pGemNeeded)
	{
		std::string str = std::to_string(3 - m_nPresentGem) + "/3";

		m_pGemNeeded->ChangeString(str.c_str());
	}
}

//宝石の減算処理
void CGoal::SubtractGem(void)
{
	m_nPresentGem--;

	if (m_pGemNeeded)
	{
		std::string str = std::to_string(3 - m_nPresentGem) + "/3";

		m_pGemNeeded->ChangeString(str.c_str());
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