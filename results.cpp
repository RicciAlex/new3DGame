//=============================================================================
//
// results.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "results.h"
#include "object2D.h"
#include "inputKeyboard.h"
#include "application.h"
#include "score.h"
#include "UIString.h"

#include <string>

//=============================================================================
//								静的変数の初期化
//=============================================================================
const int CResults::START_DELAY = 120;			//アニメーションの開始前のディレイ
const int CResults::ANIM_DELAY = 60;			//アニメーションする時のディレイ
const D3DXVECTOR3 CResults::UI_STARTING_POS = { 250.0f, 280.0f, 0.0f };	//最初のUIの位置
const float CResults::UI_DISTANCE = 100.0f;		//UIの距離
const D3DXVECTOR2 CResults::UI_SIZE = {800.0f, 50.0f};	//UIのサイズ

//コンストラクタ
CResults::CResults()
{
	//メンバー変数をクリアする
	m_nCntAnim = 0;
	m_nPhase = 0;

	for (int nCnt = 0; nCnt < UI_NUMBER; nCnt++)
	{
		m_pRanking[nCnt] = nullptr;
	}
}

//デストラクタ
CResults::~CResults()
{

}

//初期化処理
HRESULT CResults::Init(void)
{
	CObject_2D* pObj = CObject_2D::Create();

	if (!pObj)
	{
		return -1;
	}

	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f));
	pObj->SetPriority(4);

	CUIString* pString = CUIString::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.35f, (float)SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR2(350.0f, 50.0f), ColorYellow, "RESULTS", 5);

	CScore* pScore = CApplication::GetScore();

	std::string str[UI_NUMBER] = {};
	CObject::TextType type = CObject::TEXTURE_IRON;

	if (pScore)
	{
		int nScore = pScore->GetScore();
		int nStar = pScore->GetStarNumber();
		int nTime = pScore->GetTimeScore();
		int nPerfect = pScore->GetPerfectBonus();
		CScore::STAGE stage = pScore->GetStage();

		if (stage == CScore::FIRST_STAGE)
		{
			pObj->SetTexture(CObject::TEXTURE_GEAR_BG);
		}
		else if (stage == CScore::SECOND_STAGE)
		{
			pObj->SetTexture(CObject::TEXTURE_SNOW);
		}

		str[0] = "Star Score: " + std::to_string(nStar * CScore::DEFAULT_STAR_SCORE);
		str[1] = "Time Bonus : " + std::to_string(nTime);
		str[2] = "Perfect Bonus : " + std::to_string(nPerfect);
		str[3] = "Final Score : " + std::to_string(nScore);

		if (stage == CScore::SECOND_STAGE)
		{
			type = CObject::TEXTURE_ICE;
		}
	}

	pObj = CObject_2D::Create(4, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f, 0.0f), D3DXVECTOR2((float)SCREEN_WIDTH * 0.35f, (float)SCREEN_HEIGHT), type);
	
	for (int nCnt = 0; nCnt < UI_NUMBER; nCnt++)
	{
		m_pRanking[nCnt] = CUIString::Create(UI_STARTING_POS + D3DXVECTOR3(0.0f, UI_DISTANCE * nCnt, 0.0f), UI_SIZE,
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f), str[nCnt].c_str());
	}

	return S_OK;
}

//終了処理
void CResults::Uninit(void)
{
	//UIの破棄処理
	for (int nCnt = 0; nCnt < UI_NUMBER; nCnt++)
	{
		if (m_pRanking[nCnt])
		{//nullチェック
			m_pRanking[nCnt]->Release();	//メモリを解放する
			m_pRanking[nCnt] = nullptr;		//ポインタをnullにする
		}
	}
}

//更新処理
void CResults::Update(void)
{
	m_nCntAnim++;

	if (m_nCntAnim > START_DELAY && m_nCntAnim % ANIM_DELAY == 0)
	{
		if (m_nPhase < UI_NUMBER)
		{
			D3DXCOLOR col = ColorYellow;

			if (m_nPhase == UI_NUMBER - 1)
			{
				col = ColorRed;
			}

			m_pRanking[m_nPhase]->ChangeColor(col);

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_TAP);
		}

		m_nPhase++;
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && m_nPhase >= UI_NUMBER)
	{
		CApplication::SetFade(CApplication::MODE_RANKING);
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CResults* CResults::Create(void)
{
	CResults* pResults = new CResults;			//インスタンスを生成する

	if (FAILED(pResults->Init()))
	{//初期化処理
		return nullptr;
	}

	return pResults;				//生成したインスタンスを返す
}
