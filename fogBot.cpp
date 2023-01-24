//=============================================================================
//
// fogbot.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fogBot.h"
#include "fogParticle.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "rendering.h"
#include "BoxHitbox.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CFogbot::DEFAULT_VIEW_RANGE = 300.0f;	//ディフォルトの見える範囲の半径
D3DXVECTOR3 CFogbot::DEFAULT_PARTICLE_RELATIVE_POS = {0.0f, 66.0f, 0.0f};		//パーティクルのディフォルトの相対位置
const float CFogbot::DEFAULT_FRAME_ANGLE = D3DX_PI * 0.01f;	//アニメーション用の角度
const float CFogbot::DEFAULT_ANIM_AMPLITUDE = 0.35f;
const D3DXVECTOR3 CFogbot::DEFAULT_HITBOX_SIZE = { 25.0f, 70.0f, 25.0f };		//ヒットボックスのディフォルトサイズ


//コンストラクタ
CFogbot::CFogbot()
{
	//メンバー変数を初期化する
	m_fAnimAngle = 0.0f;
	m_fRange = 0.0f;
	m_bActive = false;
	m_pParticle = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CFogbot::~CFogbot()
{

}

//初期化処理
HRESULT CFogbot::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_fAnimAngle = 0.0f;
	m_fRange = DEFAULT_VIEW_RANGE;
	m_bActive = false;
	m_pParticle = nullptr;
	m_pHitbox = nullptr;

	SetModel(CModel::MODEL_ENEMY_FOGBOT);		//モデルの設定

	return S_OK;
}

//終了処理
void CFogbot::Uninit(void)
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

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CFogbot::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	UpdateParticle();

	m_fAnimAngle += DEFAULT_FRAME_ANGLE;

	pos.y += DEFAULT_ANIM_AMPLITUDE * sinf(m_fAnimAngle);

	SetPos(pos);

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(pos);
	}
}

//ディフォルトのボットの生成処理
void CFogbot::CreateDefaultBot(void)
{
	SetModelColor(2, ColorGreen);

	if (!m_pParticle)
	{
		m_pParticle = CFogParticle::Create(GetPos() + DEFAULT_PARTICLE_RELATIVE_POS);		//パーティクルの生成
	}

	if (!m_pHitbox)
	{
		m_pHitbox = CBoxHitbox::Create(GetPos(), Vec3Null, DEFAULT_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, this);		//ヒットボックスの生成
	}
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CFogbot * CFogbot::Create(const D3DXVECTOR3 pos, const float shadowPos)
{
	CFogbot* pEnemy = new CFogbot;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);					//位置の設定
	pEnemy->SetShadowHeight(shadowPos);		//影の位置のY座標の設定


	pEnemy->SetModelColor(2, ColorGreen);

	pEnemy->m_pParticle = CFogParticle::Create(pos + DEFAULT_PARTICLE_RELATIVE_POS);		//パーティクルの生成

	pEnemy->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, DEFAULT_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pEnemy);		//ヒットボックスの生成

	return pEnemy;							//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//パーティクルの更新処理
void CFogbot::UpdateParticle(void)
{
	D3DXVECTOR3 pos = GetPos(), playerPos = CApplication::GetGame()->GetPlayer()->GetPos();			//位置の取得
	D3DXVECTOR3 distance = playerPos - pos;		//プレイヤーまでの距離を計算する

	if (D3DXVec3Length(&distance) <= m_fRange)
	{//プレイヤーが見える範囲の中にいたら

		if (!m_bActive)
		{//まだアクティブではなかったら

			m_bActive = true;			//アクティブ状態にする

										//パーティクルを有効にする
			if (m_pParticle)
			{//nullチェック

				m_pParticle->SetActiveState(true);

				SetModelColor(2, ColorRed);

				CRenderer* pRenderer = CApplication::GetRenderer();

				if (pRenderer)
				{
					pRenderer->ChangeFog();
				}
			}
		}
	}
	else
	{
		if (m_bActive)
		{//まだアクティブだったら

			m_bActive = false;			//アクティブではない状態にする

										//パーティクルを無効にする
			if (m_pParticle)
			{//nullチェック
				m_pParticle->SetActiveState(false);

				SetModelColor(2, ColorGreen);

				CRenderer* pRenderer = CApplication::GetRenderer();

				if (pRenderer)
				{
					pRenderer->ChangeFog();
				}
			}
		}
	}
}
