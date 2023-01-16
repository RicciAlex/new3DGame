//=============================================================================
//
// fofParticle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fogParticle.h"
#include "fogEffect.h"


//コンストラクタ
CFogParticle::CFogParticle()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_bActive = false;
}

//デストラクタ
CFogParticle::~CFogParticle()
{

}


//初期化処理
HRESULT CFogParticle::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;
	m_bActive = false;

	return S_OK;
}

//終了処理
void CFogParticle::Uninit(void)
{

}

//更新処理
void CFogParticle::Update(void)
{
	if (m_bActive)
	{
		for (int nCnt = 0; nCnt < DEFAULT_EFFECT_NUMBER; nCnt++)
		{
			CFogEffect::Create(m_pos, D3DXVECTOR3(0.0f, (float)CObject::random(500, 800) * 0.005f, 0.0f));
		}
	}
}

//描画処理
void CFogParticle::Draw(void)
{

}

//位置の設定処理
void CFogParticle::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//エフェクトをスポーンするかどうかの設定処理
void CFogParticle::SetActiveState(const bool bActive)
{
	m_bActive = bActive;
}

//位置の取得処理
const D3DXVECTOR3 CFogParticle::GetPos(void)
{
	return m_pos;
}

//エフェクトをスポーンするかどうかの取得処理
const bool CFogParticle::GetActiveState(void)
{
	return m_bActive;
}




//=============================================================================
//
//									静的関数
//
//=============================================================================





//生成処理
CFogParticle * CFogParticle::Create(const D3DXVECTOR3 pos)
{
	CFogParticle* pParticle = new CFogParticle;		//インスタンスを生成する

	if (FAILED(pParticle->Init()))
	{//初期化処理
		return nullptr;
	}

	pParticle->m_pos = pos;				//位置の設定

	return pParticle;					//生成したインスタンスを返す
}


