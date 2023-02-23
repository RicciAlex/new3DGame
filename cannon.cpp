//=============================================================================
//
// cannon.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "cannon.h"
#include "button.h"
#include "BoxHitbox.h"
#include "cannonBullet.h"
#include "boss.h"
#include "application.h"
#include "sound.h"


//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CCannon::HITBOX_SIZE = { 90.0f, 125.0f, 125.0f };			//ヒットボックスのサイズ


//コンストラクタ
CCannon::CCannon()
{
	//メンバー変数をクリアする
	m_bFired = false;

	m_pButton = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CCannon::~CCannon()
{

}

//初期化処理
HRESULT CCannon::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_CANNON);

	return S_OK;
}

//終了処理
void CCannon::Uninit(void)
{
	//ボタンの破棄処理
	if(m_pButton)
	{//nullチェック
		m_pButton->Release();		//メモリを解放する
		m_pButton = nullptr;		//ポインタをnullにする
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	if (m_pBoss)
	{//nullチェック
		m_pBoss = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CCannon::Update(void)
{
	if (m_pButton && m_pBoss)
	{
		if (!m_bFired)
		{
			if (m_pButton->GetTrigger())
			{
				CCannonBullet::Create(GetPos(), m_pBoss);			//弾の生成
				m_bFired = true;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);
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
CCannon* CCannon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 buttonPos, CBoss* pBoss)
{
	CCannon* pCannon = new CCannon;			//インスタンスを生成する

	if (FAILED(pCannon->Init()))
	{//初期化処理

		return nullptr;
	}

	pCannon->SetPos(pos);		//位置の設定
	pCannon->SetRot(rot);		//向きの設定
	pCannon->SetShadowHeight(pos.y + 0.1f);		//影の位置の設定
	pCannon->m_pBoss = pBoss;	//ボスへのポインタの設定

	pCannon->m_pButton = CButton::Create(buttonPos, true);			//ボタンを生成する

	pCannon->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pCannon);		//ヒットボックスの生成

	return pCannon;				//生成したインスタンスを返す
}