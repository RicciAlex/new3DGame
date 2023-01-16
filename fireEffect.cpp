//=============================================================================
//
// fireEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fireEffect.h"

//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR2 CFireEffect::DEFAULT_SIZE = {10.0f, 10.0f};
const D3DXVECTOR2 CFireEffect::DEFAULT_DELTA_SIZE = {0.01f, 0.01f};
const int		  CFireEffect::DEFAULT_LIFE = 60;
const D3DXCOLOR   CFireEffect::DEFAULT_COLOR = { 0.9f, 0.25f, 0.05f, 0.25f };
const D3DXCOLOR	  CFireEffect::DEFAULT_DELTA_COLOR = { 0.01f, 0.002f, 0.0f, 0.0f };


//コンストラクタ
CFireEffect::CFireEffect()
{

}

//デストラクタ
CFireEffect::~CFireEffect()
{

}

//初期化処理
HRESULT CFireEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_CIRCLE_EFFECT);				//テクスチャの設定
	SetSize(DEFAULT_SIZE);									//サイズの設定
	SetLife(DEFAULT_LIFE);									//ライフの設定
	SetColor(DEFAULT_COLOR);								//色の設定

	return S_OK;
}

//終了処理
void CFireEffect::Uninit(void)
{
	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CFireEffect::Update(void)
{
	D3DXVECTOR2 size = GetSize();

	if (size.x > DEFAULT_DELTA_SIZE.x)
	{
		size.x -= DEFAULT_DELTA_SIZE.x;
	}
	if (size.y > DEFAULT_DELTA_SIZE.y)
	{
		size.y -= DEFAULT_DELTA_SIZE.y;
	}

	SetSize(size);

	D3DXCOLOR col = GetColor();

	if (col.r > DEFAULT_DELTA_COLOR.r)
	{
		col.r -= DEFAULT_DELTA_COLOR.r;
	}
	if (col.g > DEFAULT_DELTA_COLOR.g)
	{
		col.g -= DEFAULT_DELTA_COLOR.g;
	}
	if (col.b > DEFAULT_DELTA_COLOR.b)
	{
		col.b -= DEFAULT_DELTA_COLOR.b;
	}
	if (col.a > DEFAULT_DELTA_COLOR.a)
	{
		col.a -= DEFAULT_DELTA_COLOR.a;
	}

	SetColor(col);

	//基本クラスの更新処理
	CEffect::Update();
}





//=============================================================================
//
//									静的関数
//
//=============================================================================




//生成処理
CFireEffect* CFireEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CFireEffect* pEffect = new CFireEffect;				//インスタンスを生成する

	if (FAILED(pEffect->Init()))
	{//初期化処理
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetMove(move);				//速度の設定

	return pEffect;						//生成したインスタンスを返す
}