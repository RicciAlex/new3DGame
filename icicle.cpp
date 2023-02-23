//=============================================================================
//
// icicle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "icicle.h"
#include "CylinderHitbox.h"


//=============================================================================
//								静的変数の初期化	
//=============================================================================
const D3DXVECTOR3 CIcicle::DEFAULT_DAMAGE_HITBOX_SIZE = {25.0f, 50.0f, 25.0f };			//ディフォルトのダメージを与えるヒットボックスのサイズ
const D3DXVECTOR3 CIcicle::DEFAULT_BODY_HITBOX_SIZE = {25.0f, 125.0f, 25.0f};			//ディフォルトのダメージを与えないヒットボックスのサイズ
const float		  CIcicle::DEFAULT_STARTING_SCALE = 0.1f;								//ディフォルトの初めのスケール
const float		  CIcicle::DEFAULT_MAX_SCALE = 2.5f;									//ディフォルトの最大のスケール
const float		  CIcicle::DEFAULT_SCALE_INCREMENT = 0.1f;								//加算されているスケールの値
const float		  CIcicle::DEFAULT_APLHA_INCREMENT = 0.02f;								//加算されているα値の値
const int		  CIcicle::DEFAULT_DELAY = 120;											//ディフォルトのディレイ


//コンストラクタ
CIcicle::CIcicle()
{
	//基本クラスをクリアする
	m_nDelay = 0;
	m_nCntDelay = 0;
	m_fAlpha = 0.0f;

	m_pDamageHitbox = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CIcicle::~CIcicle()
{

}

//初期化処理
HRESULT CIcicle::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_nDelay = DEFAULT_DELAY;
	m_fAlpha = 1.0f;
	SetPriority(5);

	return S_OK;
}

//終了処理
void CIcicle::Uninit(void)
{
	//ヒットボックスの終了処理
	if (m_pDamageHitbox)
	{//nullチェック

		m_pDamageHitbox->Release();			//メモリを解放する
		m_pDamageHitbox = nullptr;			//ポインタをnullにする
	}
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->Release();				//メモリを解放する
		m_pHitbox = nullptr;				//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CIcicle::Update(void)
{
	float fScale = GetScale();		//スケールの取得

	if (fScale < DEFAULT_MAX_SCALE)
	{
		fScale += DEFAULT_SCALE_INCREMENT;

		SetScale(fScale);
	}
	else
	{
		m_nCntDelay++;

		if (m_nCntDelay >= DEFAULT_DELAY)
		{
			if (m_fAlpha > 0.0f)
			{
				m_fAlpha -= DEFAULT_APLHA_INCREMENT;

				SetModelColor(0, D3DXCOLOR(0.8f, 0.8f, 0.8f, m_fAlpha));
			}
			else
			{
				Release();
				return;
			}
		}
	}

	//基本クラスの更新処理
	CModel::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CIcicle* CIcicle::Create(const D3DXVECTOR3 pos)
{
	CIcicle* pIcicle = new CIcicle;				//インスタンスを生成する

	//初期化処理
	if (FAILED(pIcicle->Init()))
	{
		return nullptr;
	}

	pIcicle->SetPos(pos);							//位置の設定
	pIcicle->SetModel(CModel::MODEL_ICICLE);		//モデルの設定
	pIcicle->SetScale(DEFAULT_STARTING_SCALE);		//スケールの設定
	pIcicle->SetShadowDraw(false);					//影を描画しないように設定する

	//ヒットボックスの生成処理
	pIcicle->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, DEFAULT_BODY_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pIcicle);
	pIcicle->m_pDamageHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, DEFAULT_BODY_HITBOX_SIZE.y, 0.0f), Vec3Null, 
									DEFAULT_DAMAGE_HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pIcicle, CHitbox::EFFECT_BOUNCE);

	return pIcicle;
}