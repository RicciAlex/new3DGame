//=============================================================================
//
// game.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"
#include "player.h"
#include "timer.h"

//コンストラクタ
CGame::CGame() : CMode(true)
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
}

//デストラクタ
CGame::~CGame()
{

}

//初期化処理
HRESULT CGame::Init(void)
{
	m_pPlayer = nullptr;
	m_pTimer = CTimer::Create();

	return S_OK;
}

//終了処理
void CGame::Uninit(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pTimer)
	{
		m_pTimer->Release();
		m_pTimer = nullptr;
	}
}

//更新処理
void CGame::Update(void)
{
	
}

//時間の追加処理
void CGame::AddTime(const float fMilliseconds)
{
	if (m_pTimer)
	{
		m_pTimer->AddTime(fMilliseconds);
	}
}


//プレイヤーの設定処理
void CGame::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

//プレイヤーの取得処理
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}