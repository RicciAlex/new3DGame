//=============================================================================
//
// timer.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "timer.h"
#include "UIString.h"
#include <string>


//コンストラクタ
CTimer::CTimer()
{
	//メンバー変数をクリアする
	m_fCurrentTime = 0.0f;
	m_fStartTime = 0.0f;
	m_fAddedTime = 0.0f;

	m_pString = nullptr;
}

//デストラクタ
CTimer::~CTimer()
{

}

//初期化処理
HRESULT CTimer::Init(void)
{
	//メンバー変数を初期化する
	m_fStartTime = (float)timeGetTime();
	m_fCurrentTime = (float)timeGetTime();
	m_fAddedTime = 0.0f;

	m_pString = nullptr;

	return S_OK;
}

//終了処理
void CTimer::Uninit(void)
{
	//UIの破棄処理
	if (m_pString)
	{//nullチェック

		m_pString->Release();		//メモリを解放する
		m_pString = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CTimer::Update(void)
{
	m_fCurrentTime = (float)timeGetTime();

	int min = 0, sec = 0;

	float fTime = DEFAULT_MAX_TIME - ((float)(m_fCurrentTime - m_fStartTime) + m_fAddedTime);

	if (fTime < 0.0f)
	{
		fTime = 0.0f;
	}

	sec = (int)(fTime / 1000.0f) % 60;
	min = (int)(fTime / (60.0f * 1000.0f));

	if (m_pString)
	{
		std::string M = std::to_string(min);
		std::string S = std::to_string(sec);

		if (M.size() == 1)
		{
			M = "000" + std::to_string(min);
		}
		else if (M.size() == 2)
		{
			M = "00" + std::to_string(min);
		}
		else if (M.size() == 3)
		{
			M = "0" + std::to_string(min);
		}

		if (S.size() == 1)
		{
			S = "0" + std::to_string(sec);
		}

		std::string str = M + ":" + S;

		m_pString->ChangeString(str.c_str());
	}
}

//描画処理
void CTimer::Draw(void)
{

}

//位置の設定処理
void CTimer::SetPos(const D3DXVECTOR3 pos)
{

}

//時間の追加処理
void CTimer::AddTime(const float fMilliseconds)
{
	m_fAddedTime += fMilliseconds;
}

//位置の取得処理
const D3DXVECTOR3 CTimer::GetPos(void)
{
	return Vec3Null;
}

//時間の取得処理
const float CTimer::GetTime(void)
{
	return (m_fCurrentTime - m_fStartTime) + m_fAddedTime;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================




//生成処理
CTimer * CTimer::Create(void)
{
	CTimer* pTimer = new CTimer;			//インスタンスを生成する

	if (FAILED(pTimer->Init()))
	{//初期化処理

		return nullptr;
	}

	pTimer->m_pString = CUIString::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f), D3DXVECTOR2(210.0f, 30.0f), ColorGreen, "0000:00");

	return pTimer;
}
