//=============================================================================
//
// iceBoulder.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "iceBoulder.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "CylinderHitbox.h"
#include "meshfield.h"
#include "iceShard.h"
#include "sound.h"

//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CIceBoulder::DEFAULT_GRAVITY_ACCELERATION = -0.8f;			//重力
const int   CIceBoulder::ATTACK_FRAME = 90;								//攻撃のフレーム数
const int   CIceBoulder::SHARD_NUMBER = 5;								//破片の数
const D3DXVECTOR3 CIceBoulder::HITBOX_RELATIVE_POS = { 0.0f, 49.5f, 0.0f };			//ヒットボックスの相対位置
const D3DXVECTOR3 CIceBoulder::HITBOX_SIZE = { 50.0f, 100.0f, 50.0f };				//ヒットボックスのサイズ


//コンストラクタ
CIceBoulder::CIceBoulder()
{
	//メンバー変数をクリアする
	m_target = Vec3Null;
	m_move = Vec3Null;

	m_pHitbox = nullptr;
}

//デストラクタ
CIceBoulder::~CIceBoulder()
{

}

//初期化処理
HRESULT CIceBoulder::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_ICE_BOULDER);		//モデルの設定
	StartRotation(D3DXVECTOR3(D3DX_PI * 0.0025f * (float)random(-500, 500), D3DX_PI * 0.0025f * (float)random(-500, 500), 0.0f));	//回転の開始処理
	SetDrawDistance(4000.0f);

	return S_OK;
}

//終了処理
void CIceBoulder::Uninit(void)
{
	//ヒットボックスの破棄処理
	if(m_pHitbox)
	{//nullチェック

		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CIceBoulder::Update(void)
{
	//基本クラスの更新処理
	CModel::Update();

	m_move.y += DEFAULT_GRAVITY_ACCELERATION;
	SetPos(GetPos() + m_move);			//位置の更新

	if (GetPos().y <= -5000.0f)
	{
		Release();
		return;
	}

	UpdateHitbox();			//ヒットボックスの更新処理
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CIceBoulder* CIceBoulder::Create(const D3DXVECTOR3 pos)
{
	CIceBoulder* pBoulder = new CIceBoulder;		//インスタンスを生成する

	if (FAILED(pBoulder->Init()))
	{//初期化処理
		return nullptr;
	}

	pBoulder->SetPos(pos);			//位置の設定
	pBoulder->SetSpeed();			//速度の設定処理

	pBoulder->m_pHitbox = CCylinderHitbox::Create(pos + HITBOX_RELATIVE_POS, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pBoulder, CHitbox::EFFECT_BOUNCE);

	return pBoulder;				//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//速度の設定処理
void CIceBoulder::SetSpeed(void)
{
	m_target = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得

	m_move = m_target - GetPos();			//向きの計算
	m_move.x /= (float)(ATTACK_FRAME);		//速度のX座標の設定
	m_move.z /= (float)(ATTACK_FRAME);		//速度のZ座標の設定

	m_move.y = -DEFAULT_GRAVITY_ACCELERATION * (ATTACK_FRAME) * 0.5f;		//速度のY座標の設定
}

//ヒットボックスの更新処理
void CIceBoulder::UpdateHitbox(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos() + HITBOX_RELATIVE_POS);

		if (m_pHitbox->GetCollisionState())
		{
			CreateShard();		//破片の生成処理

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ICE_BOULDER);

			Release();
			return;
		}
	}

	if (CMeshfield::FieldInteraction(this))
	{
		CreateShard();			//破片の生成処理

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ICE_BOULDER);

		Release();
		return;
	}
}

//破片の生成処理
void CIceBoulder::CreateShard(void)
{
	for (int nCnt = 0; nCnt < SHARD_NUMBER; nCnt++)
	{
		D3DXVECTOR3 translation = D3DXVECTOR3((float)random(-500, 500) * 0.01f * 20.0f, (float)random(-500, 500) * 0.01f * 20.0f, (float)random(-500, 500) * 0.01f * 20.0f);
		D3DXVECTOR3 move = Vec3Null;
		D3DXVec3Normalize(&move, &translation);
		move.y = (float)random(250, 500) * 0.01f * 5.0f;

		CIceShard::Create(GetPos() + translation, move);
	}
}
