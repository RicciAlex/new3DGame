//=============================================================================
//
// stageSelect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stageSelect.h"
#include "object2D.h"
#include "application.h"
#include "inputKeyboard.h"
#include "UIString.h"


//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CStageSelect::DEFAULT_STRING_POS = D3DXVECTOR3(390.0f, 150.0f, 0.0f);			//ディフォルトの文字列の位置
const D3DXVECTOR2 CStageSelect::DEFAULT_STRING_SIZE = D3DXVECTOR2(500.0f, 50.0f);			//ディフォルトの文字列のサイズ


//コンストラクタ
CStageSelect::CStageSelect()
{
	m_nSelectedStage = (STAGE)0;
}

//デストラクタ
CStageSelect::~CStageSelect()
{

}

//初期化処理
HRESULT CStageSelect::Init(void)
{
	CObject_2D::Create(4, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f), CObject::TEXTURE_BLOCK);

	CUIString::Create(DEFAULT_STRING_POS, DEFAULT_STRING_SIZE, ColorGreen, "STAGE SELECTION");

	m_nSelectedStage = FIRST_STAGE;

	return S_OK;
}

//終了処理
void CStageSelect::Uninit(void)
{
	
}

//更新処理
void CStageSelect::Update(void)
{
	if (!CApplication::GetFade())
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{
			switch (m_nSelectedStage)
			{
			case FIRST_STAGE:

			{
				CApplication::SetFade(CApplication::MODE_SECOND_STAGE);
			}

			break;

			default:
				break;
			}
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_BACKSPACE))
		{
			CApplication::SetFade(CApplication::MODE_TITLE);
		}
	}
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CStageSelect* CStageSelect::Create(void)
{
	CStageSelect* pMode = new CStageSelect;			//インスタンスを生成する

	//初期化処理
	if (FAILED(pMode->Init()))
	{
		return nullptr;
	}

	return pMode;
}