//=============================================================================
//
// twister.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "twister.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "CylinderHitbox.h"
#include "sound.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CTwister::EFFECT_DISTANCE = 10.0f;					//エフェクトの距離
const float CTwister::START_RANGE = 10.0f;						//はじめての半径
const float CTwister::DEFAULT_SPEED = 2.0f;					//ディフォルトの速度
const D3DXVECTOR3 CTwister::HITBOX_SIZE = { 25.0f, 150.0f, 25.0f };				//ヒットボックスのサイズ


//コンストラクタ
CTwister::CTwister()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_move = Vec3Null;
	m_nLife = 0;
	m_fCurrentAngle = 0.0f;

	int nEffectNum = LAYER_NUMBER * EFFECT_PER_LAYER;

	for (int nCnt = 0; nCnt < LAYER_NUMBER; nCnt++)
	{
		m_fStartingAngle[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < nEffectNum; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}

	m_pHitbox = nullptr;
}

//デストラクタ
CTwister::~CTwister()
{

}


//初期化処理
HRESULT CTwister::Init(void)
{
	//メンバー変数を初期化する
	m_nLife = CTwisterEffect::DEFAULT_LIFE;

	float fMaxAngle = (2.0f * D3DX_PI) * 1000.0f / EFFECT_PER_LAYER;

	for (int nCnt = 0; nCnt < LAYER_NUMBER; nCnt++)
	{
		m_fStartingAngle[nCnt] = random(0, (int)fMaxAngle) * 0.0001f;
	}

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_TWISTER);

	return S_OK;
}

//終了処理
void CTwister::Uninit(void)
{
	int nEffectNum = LAYER_NUMBER * EFFECT_PER_LAYER;

	for (int nCnt = 0; nCnt < nEffectNum; nCnt++)
	{
		if (m_pEffect[nCnt])
		{
			m_pEffect[nCnt] = nullptr;		
		}
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CTwister::Update(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		CApplication::GetSound()->Stop(CSound::SOUND_LABEL_SE_TWISTER);

		Release();
		return;
	}

	UpdatePos();

	UpdateEffectPos();

	UpdateHitbox();

}

//描画処理
void CTwister::Draw(void)
{

}

//位置の設定処理
void CTwister::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CTwister::GetPos(void)
{
	return m_pos;
}




//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CTwister * CTwister::Create(const D3DXVECTOR3 pos)
{
	CTwister* pTwister = new CTwister;			//インスタンスを生成する

	if (FAILED(pTwister->Init()))
	{
		return nullptr;
	}

	pTwister->m_pos = pos;

	int nEffectNum = LAYER_NUMBER * EFFECT_PER_LAYER;

	for (int nCntLayer = 0; nCntLayer < LAYER_NUMBER; nCntLayer++)
	{
		for(int nCntEffect = 0; nCntEffect < EFFECT_PER_LAYER; nCntEffect++)
		{
			D3DXVECTOR3 p = Vec3Null;
			float fAmplitude = 25.0f + 0.0025f * (START_RANGE * nCntLayer) * (START_RANGE * nCntLayer);
			float fAngle = (2.0f * D3DX_PI) / EFFECT_PER_LAYER;

			p.x = pos.x + fAmplitude * cosf(pTwister->m_fStartingAngle[nCntLayer] + (fAngle * nCntEffect));
			p.y = pos.y + (EFFECT_DISTANCE * (nCntLayer + 1));
			p.z = pos.z + fAmplitude * sinf(pTwister->m_fStartingAngle[nCntLayer] + (fAngle * nCntEffect));

			pTwister->m_pEffect[(nCntLayer * EFFECT_PER_LAYER) + nCntEffect] = CTwisterEffect::Create(p);
		}
	}

	pTwister->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_OVERLAPPABLE, -1, pTwister, CHitbox::EFFECT_BOUNCE);

	return pTwister;			//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート的関数
//
//=============================================================================



//位置の更新処理
void CTwister::UpdatePos(void)
{
	CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();

	if (!pPlayer)
	{
		return;
	}

	D3DXVECTOR3 playerPos = pPlayer->GetPos();		//プレイヤーの位置の取得
	D3DXVECTOR3 move = playerPos - m_pos;
	D3DXVec3Normalize(&move, &move);

	//pPlayer->SetPos(pPlayer->GetPos() + D3DXVECTOR3(-move.x, 0.0f, -move.z));

	move.x *= DEFAULT_SPEED;
	move.y = 0;
	move.z *= DEFAULT_SPEED;

	m_pos += move;
}

//エフェクトの位置の更新処理
void CTwister::UpdateEffectPos(void)
{
	int nEffectNum = LAYER_NUMBER * EFFECT_PER_LAYER;

	for (int nCntLayer = 0; nCntLayer < LAYER_NUMBER; nCntLayer++)
	{
		m_fStartingAngle[nCntLayer] += -D3DX_PI * 2.0f * 0.01f;

		for (int nCntEffect = 0; nCntEffect < EFFECT_PER_LAYER; nCntEffect++)
		{
			if (m_pEffect[nCntEffect + (nCntLayer * EFFECT_PER_LAYER)])
			{
				D3DXVECTOR3 p = Vec3Null;
				float fAmplitude = 25.0f + 0.0025f * (START_RANGE * nCntLayer) * (START_RANGE * nCntLayer);
				float fAngle = (2.0f * D3DX_PI) / EFFECT_PER_LAYER;

				p.x = m_pos.x + fAmplitude * cosf(m_fStartingAngle[nCntLayer] + (fAngle * nCntEffect));
				p.y = m_pos.y + (EFFECT_DISTANCE * (nCntLayer + 1));
				p.z = m_pos.z + fAmplitude * sinf(m_fStartingAngle[nCntLayer] + (fAngle * nCntEffect));

				p += D3DXVECTOR3((float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f);

				m_pEffect[nCntEffect + (nCntLayer * EFFECT_PER_LAYER)]->SetPos(p);
			}
		}
	}
}

//ヒットボックスの更新処理
void CTwister::UpdateHitbox(void)
{
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->SetPos(m_pos);		//位置の設定
	}
}


