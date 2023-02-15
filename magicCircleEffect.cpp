//=============================================================================
//
// magicCircleEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "magicCircleEffect.h"

//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR2 CMagicCircleEffect::DEFAULT_SIZE = {100.0f, 100.0f};			//ディフォルトのサイズ


//コンストラクタ
CMagicCircleEffect::CMagicCircleEffect()
{

}

//デストラクタ
CMagicCircleEffect::~CMagicCircleEffect()
{

}

//初期化処理
HRESULT CMagicCircleEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_MAGIC_CIRCLE_EFFECT);				//テクスチャの設定
	SetSize(DEFAULT_SIZE);											//サイズの設定
	SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.0025f, 0.0f));		//回転の設定
	SetStartingRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));		//初期時の回転の設定

	return S_OK;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CMagicCircleEffect* CMagicCircleEffect::Create(const D3DXVECTOR3 pos)
{
	CMagicCircleEffect* pEffect = new CMagicCircleEffect;				//インスタンスを生成する

	if (FAILED(pEffect->Init()))
	{//初期化処理
		return nullptr;
	}

	pEffect->SetPos(pos);			//位置の設定

	return pEffect;					//生成したインスタンスを返す
}