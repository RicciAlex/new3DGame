//=============================================================================
//
// fireParticle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fireParticle.h"
#include "fireEffect.h"
#include "application.h"
#include "camera.h"


//コンストラクタ
CFireParticle::CFireParticle()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_bActive = false;
}

//デストラクタ
CFireParticle::~CFireParticle()
{

}


//初期化処理
HRESULT CFireParticle::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;
	m_bActive = true;

	return S_OK;
}

//終了処理
void CFireParticle::Uninit(void)
{

}

//更新処理
void CFireParticle::Update(void)
{
	if (m_bActive)
	{
		D3DXVECTOR3 dist = CApplication::GetCamera()->GetPos() - GetPos();

		if (D3DXVec3Length(&dist) <= 2500.0f)
		{
			CFireEffect* pEffect = nullptr;

			for (int nCnt = 0; nCnt < DEFAULT_EFFECT_NUMBER; nCnt++)
			{
				CFireEffect::Create(m_pos + D3DXVECTOR3((nCnt * 5.0f) - 15, 0.0f, 0.0f), D3DXVECTOR3((float)CObject::random(-50, 50) * 0.01f, (float)CObject::random(10, 100) * 0.025f, (float)CObject::random(-50, 50) * 0.01f));
			}
		}
	}
}

//描画処理
void CFireParticle::Draw(void)
{

}

//位置の設定処理
void CFireParticle::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//エフェクトをスポーンするかどうかの設定処理
void CFireParticle::SetActiveState(const bool bActive)
{
	m_bActive = bActive;
}

//位置の取得処理
const D3DXVECTOR3 CFireParticle::GetPos(void)
{
	return m_pos;
}

//エフェクトをスポーンするかどうかの取得処理
const bool CFireParticle::GetActiveState(void)
{
	return m_bActive;
}




//=============================================================================
//
//									静的関数
//
//=============================================================================





//生成処理
CFireParticle * CFireParticle::Create(const D3DXVECTOR3 pos)
{
	CFireParticle* pParticle = new CFireParticle;		//インスタンスを生成する

	if (FAILED(pParticle->Init()))
	{//初期化処理
		return nullptr;
	}

	pParticle->m_pos = pos;				//位置の設定

	return pParticle;					//生成したインスタンスを返す
}


