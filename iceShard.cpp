//=============================================================================
//
// iceShard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "iceShard.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CIceShard::DEFAULT_GRAVITY_ACCELERATION = -0.8f;		//重力


//コンストラクタ
CIceShard::CIceShard()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
}

//デストラクタ
CIceShard::~CIceShard()
{

}

//初期化処理
HRESULT CIceShard::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}	

	m_nCntLife = DEFAULT_LIFE;				//ライフの設定
	SetModel(CModel::MODEL_ICE_SHARD);		//モデルの設定
	StartRotation(D3DXVECTOR3(D3DX_PI * 0.00025f * (float)random(-500, 500), D3DX_PI * 0.00025f * (float)random(-500, 500), 0.0f));

	return S_OK;
}

//終了処理
void CIceShard::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CIceShard::Update(void)
{
	//ライフの更新処理
	m_nCntLife--;

	if (m_nCntLife <= 0)
	{
		Release();
		return;
	}

	m_move.y += DEFAULT_GRAVITY_ACCELERATION;
	SetPos(GetPos() + m_move);

	//基本クラスの更新処理
	CModel::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CIceShard* CIceShard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CIceShard* pShard = new CIceShard;		//インスタンスを生成する

	if (FAILED(pShard->Init()))
	{//初期化処理
		return nullptr;
	}

	pShard->SetPos(pos);			//位置の設定
	pShard->m_move = move;			//速度の設定
	pShard->SetShadowDraw(false);	//影を描画しないように設定する

	return pShard;					//生成したインスタンスを返す
}
