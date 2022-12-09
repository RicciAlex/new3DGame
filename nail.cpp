//=============================================================================
//
// nail.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "nail.h"
#include "BoxHitbox.h"

//コンストラクタ
CNail::CNail()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;				//ヒットボックス
}

//デストラクタ
CNail::~CNail()
{

}

//初期化処理
HRESULT CNail::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CModel::Init()))
	{//親クラスの初期化処理
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CNail::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//更新処理
void CNail::Update(void)
{

}



//=============================================================================
//
// 
//
//=============================================================================




//生成処理
CNail* CNail::Create(const D3DXVECTOR3 pos)
{
	CNail* pNail = new CNail;			//インスタンスを生成する

	if (FAILED(pNail->Init()))
	{//初期化処理
		return nullptr;
	}

	pNail->SetModel(CModel::MODEL_NAILS);		//モデルの設定
	pNail->SetPos(pos);							//位置を設定する
	pNail->SetScale(0.75f);						//スケールを設定する
	pNail->SetShadowDraw(false);				//影を描画しないように設定する

	float fRot = (float)CObject::random(-31415, 31415) * 0.0001f;
	pNail->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));

	pNail->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(37.0f, 10.0f, 37.0f), CHitbox::TYPE_OBSTACLE, pNail, -1, CHitbox::EFFECT_BOUNCE);		//ヒットボックスの生成

	return pNail;
}