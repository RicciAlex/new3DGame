//=============================================================================
//
// fogEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fogEffect.h"

//=============================================================================
//									静的変数の初期化
//=============================================================================
const D3DXVECTOR2 CFogEffect::DEFAULT_SIZE = D3DXVECTOR2(10.0f, 10.0f);
const int		  CFogEffect::DEFAULT_LIFE = 90;
const D3DXCOLOR   CFogEffect::DEFAULT_COLOR = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);


//コンストラクタ
CFogEffect::CFogEffect()
{

}

//デストラクタ
CFogEffect::~CFogEffect()
{

}

//初期化処理
HRESULT CFogEffect::Init(void)
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

	m_fAcceleration = (float)random(-100, 100) * 0.00075f;

	return S_OK;
}

//終了処理
void CFogEffect::Uninit(void)
{
	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CFogEffect::Update(void)
{
	D3DXVECTOR3 move = GetMove();

	move.x += m_fAcceleration;

	SetMove(move);

	//基本クラスの更新処理
	CEffect::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CFogEffect* CFogEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CFogEffect* pEffect = new CFogEffect;				//インスタンスを生成する

	if (FAILED(pEffect->Init()))
	{//初期化処理
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetMove(move);				//速度の設定

	return pEffect;						//生成したインスタンスを返す
}