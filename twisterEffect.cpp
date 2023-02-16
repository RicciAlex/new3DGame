//=============================================================================
//
// twisterEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "twisterEffect.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const int		  CTwisterEffect::DEFAULT_LIFE = 300;			//ディフォルトのライフ
const D3DXCOLOR	  CTwisterEffect::DEFAULT_COLOR = { 0.0f, 0.5f, 0.6f, 0.5f };			//ディフォルトの色
const D3DXVECTOR2 CTwisterEffect::DEFAULT_SIZE = {10.0f, 10.0f};			//ディフォルトのサイズ


//コンストラクタ
CTwisterEffect::CTwisterEffect()
{

}

//デストラクタ
CTwisterEffect::~CTwisterEffect()
{

}

//初期化処理
HRESULT CTwisterEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_CIRCLE_EFFECT);				//テクスチャの設定
	SetLife(DEFAULT_LIFE);									//ライフの設定
	SetColor(DEFAULT_COLOR);								//色の設定
	SetSize(DEFAULT_SIZE);

	return S_OK;
}

//終了処理
void CTwisterEffect::Uninit(void)
{
	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CTwisterEffect::Update(void)
{
	//基本クラスの更新処理
	CEffect::Update();
}




//生成処理
CTwisterEffect* CTwisterEffect::Create(const D3DXVECTOR3 pos)
{
	CTwisterEffect* pEffect = new CTwisterEffect;		//インスタンスを生成する

	if (FAILED(pEffect->Init()))
	{//初期化処理
		return nullptr;
	}

	pEffect->SetPos(pos);		//位置の設定

	return pEffect;				//生成したインスタンスを返す
}