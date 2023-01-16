//=============================================================================
//
// FirePipe.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "FirePipe.h"
#include "fireParticle.h"
#include "CylinderHitbox.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CFirePipe::FIRE_HITBOX_SIZE = {72.0f, 100.0f, 72.0f};		//火のヒットボックスのサイズ
const D3DXVECTOR3 CFirePipe::HITBOX_SIZE =		{72.0f, 1000.0f, 72.0f};		//ヒットボックスのサイズ

//コンストラクタ
CFirePipe::CFirePipe()
{
	//メンバー変数をクリアする
	m_nCntTime = 0;
	m_nFireTime = 0;

	m_pParticle = nullptr;
	m_pHitbox = nullptr;
	m_pFireHitbox = nullptr;
}

//デストラクタ
CFirePipe::~CFirePipe()
{

}

//初期化処理
HRESULT CFirePipe::Init(void)
{
	//メンバー変数を初期化する
	m_nCntTime = 0;
	m_nFireTime = DEFAULT_FIRE_TIME;

	m_pParticle = nullptr;
	m_pHitbox = nullptr;
	m_pFireHitbox = nullptr;

	return S_OK;
}

//終了処理
void CFirePipe::Uninit(void)
{
	//パーティクルの破棄処理
	if (m_pParticle)
	{//nullチェック
		m_pParticle->Release();		//メモリを解放する
		m_pParticle = nullptr;		//ポインタをnullにする
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//火ヒットボックスの破棄処理
	if (m_pFireHitbox)
	{//nullチェック
		m_pFireHitbox->Release();		//メモリを解放する
		m_pFireHitbox = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CFirePipe::Update(void)
{
	m_nCntTime++;			//カウンターをインクリメントする

	if (m_nCntTime >= m_nFireTime)
	{//設定した時間が経ったら

		m_nCntTime = 0;		//カウンターを元に戻す

		if (m_pParticle)
		{//パーティクルのnullチェック

			//アクティブ状態を逆にする
			if (m_pParticle->GetActiveState())
			{
				m_pParticle->SetActiveState(false);

				//ヒットボックスを移動する
				if (m_pFireHitbox)
				{//nullチェック
					m_pFireHitbox->SetPos(GetPos() + D3DXVECTOR3(0.0f, -5000.0f, 0.0f));
				}
			}
			else
			{
				m_pParticle->SetActiveState(true);

				//ヒットボックスを移動する
				if (m_pFireHitbox)
				{//nullチェック
					m_pFireHitbox->SetPos(GetPos());
				}
			}
		}
	}
}



//=============================================================================
//
// FirePipe.cpp
// Author : Ricci Alex
//
//=============================================================================



//生成処理
CFirePipe* CFirePipe::Create(const D3DXVECTOR3 pos)
{
	CFirePipe* pPipe = new CFirePipe;			//インスタンスを生成する

	if (FAILED(pPipe->Init()))
	{//初期化処理
		return nullptr;
	}

	pPipe->SetModel(CModel::MODEL_PIPE);	//モデルの設定
	pPipe->SetPos(pos);						//位置の設定
	pPipe->SetShadowDraw(false);			//影を描画しないように設定する

	pPipe->m_pParticle = CFireParticle::Create(pos);			//パーティクルを生成する

	//ヒットボックスの生成
	pPipe->m_pHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, -1000.0f, 0.0f), Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pPipe);
	pPipe->m_pFireHitbox = CCylinderHitbox::Create(pos, Vec3Null, FIRE_HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pPipe, CHitbox::EFFECT_BOUNCE);

	return pPipe;				//生成したインスタンスを返す
}

//生成処理
CFirePipe* CFirePipe::Create(const D3DXVECTOR3 pos, const int nFireTime)
{
	CFirePipe* pPipe = new CFirePipe;			//インスタンスを生成する

	if (FAILED(pPipe->Init()))
	{//初期化処理
		return nullptr;
	}

	pPipe->SetModel(CModel::MODEL_PIPE);	//モデルの設定
	pPipe->SetPos(pos);						//位置の設定
	pPipe->SetShadowDraw(false);			//影を描画しないように設定する

	if (nFireTime >= MIN_FIRE_TIME)
	{
		pPipe->m_nFireTime = nFireTime;			//火を消す/付けるまでのフレーム数の設定
	}
	else
	{
		pPipe->m_nFireTime = MIN_FIRE_TIME;		//火を消す/付けるまでのフレーム数の設定
	}

	pPipe->m_pParticle = CFireParticle::Create(pos);			//パーティクルを生成する

	//ヒットボックスの生成
	pPipe->m_pHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, -1000.0f, 0.0f), Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pPipe);
	pPipe->m_pFireHitbox = CCylinderHitbox::Create(pos, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pPipe, CHitbox::EFFECT_BOUNCE);

	return pPipe;				//生成したインスタンスを返す
}