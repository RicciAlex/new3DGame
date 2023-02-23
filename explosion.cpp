//=============================================================================
//
// explosion.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "explosion.h"
#include "fireEffect.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const int CExplosion::DEFAULT_LIFE = 30;	//ディフォルトのライフ
const int CExplosion::EFFECT_NUMBER = 35;	//毎フレーム生成されるエフェクト数


//コンストラクタ
CExplosion::CExplosion()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
}

//デストラクタ
CExplosion::~CExplosion()
{

}


//初期化処理
HRESULT CExplosion::Init(void)
{
	m_nLife = DEFAULT_LIFE;

	return S_OK;
}

//終了処理
void CExplosion::Uninit(void)
{

}

//更新処理
void CExplosion::Update(void)
{
	m_nLife--;			//ライフの更新

	if (m_nLife <= 0)
	{
		Release();
		return;
	}

	for (int nCnt = 0; nCnt < EFFECT_NUMBER; nCnt++)
	{
		D3DXVECTOR3 pos = m_pos + D3DXVECTOR3((float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f);
		D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000) * 0.005f, (float)random(-1000, 1000) * 0.005f, (float)random(-1000, 1000) * 0.005f);

		CFireEffect::Create(pos, move);
	}
}

//描画処理
void CExplosion::Draw(void)
{

}

//位置の設定処理
void CExplosion::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CExplosion::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CExplosion* CExplosion::Create(const D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion;		//インスタンスを生成する

	if (FAILED(pExplosion->Init()))
	{//初期化処理

		return nullptr;
	}

	pExplosion->m_pos = pos;	//位置の設定

	return pExplosion;			//生成したインスタンスを返す
}