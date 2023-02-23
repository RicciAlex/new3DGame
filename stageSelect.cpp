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
#include "camera.h"
#include "object3D.h"
#include "object.h"
#include "stageSelectCursor.h"
#include "AnimateUI.h"

#include "model.h"
#include "meshfield.h"


//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CStageSelect::DEFAULT_STRING_POS = D3DXVECTOR3(390.0f, 125.0f, 0.0f);			//ディフォルトの文字列の位置
const D3DXVECTOR2 CStageSelect::DEFAULT_STRING_SIZE = D3DXVECTOR2(500.0f, 50.0f);			//ディフォルトの文字列のサイズ
const D3DXVECTOR3 CStageSelect::CURSOR_POS[2] = { 
												{ -380.0f, -150.0f, -125.0f }, 
												{  380.0f, -150.0f, -125.0f } };	//カーソルの位置


CAnimateUI* pUI = nullptr;

//コンストラクタ
CStageSelect::CStageSelect()
{
	m_nSelectedStage = (STAGE)0;

	m_pCursor = nullptr;

	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{
		m_pLogo[nCnt] = nullptr;
	}
}

//デストラクタ
CStageSelect::~CStageSelect()
{

}

//初期化処理
HRESULT CStageSelect::Init(void)
{
	/*CObject_2D::Create(4, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f), CObject::TEXTURE_BLOCK);*/

	CUIString::Create(DEFAULT_STRING_POS, DEFAULT_STRING_SIZE, ColorYellow, "STAGE SELECTION");

	CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 1000.0f, -200.0f), D3DXVECTOR3(0.0f, -200.0f, 0.0f));

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-1000.0f, -500.0f, 400.0f), Vec3Null, "data\\STAGESET\\FieldsData\\StageSelect\\StageSelectMeshfield1.txt", 3);
	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(0.0f, -500.0f, 400.0f), Vec3Null, "data\\STAGESET\\FieldsData\\StageSelect\\StageSelectMeshfield1.txt", 3);
	pField->SetTexture(CObject::TEXTURE_ICE);

	CModel* pModel = nullptr;

	D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -200.0f, 0.0f) - D3DXVECTOR3(0.0f, 1000.0f, -200.0f);
	D3DXVec3Normalize(&dir, &dir);
	dir.x *= 3500.0f;
	dir.y *= 3500.0f;
	dir.z *= 3500.0f;

	CObject_3D* pBg = CObject_3D::Create();
	pBg->SetPos(D3DXVECTOR3(0.0f, -200.0f, -3500.0f) + dir);
	pBg->SetSize(D3DXVECTOR2(8000.0f, 8000.0f));
	pBg->SetColor(D3DXCOLOR(0.2f, 0.9f, 0.8f, 1.0f));
	pBg->SetStartingRot(D3DXVECTOR3(D3DX_PI * 0.35f, 0.0f, 0.0f));

	m_pCursor = CStageSelectCursor::Create(CURSOR_POS[FIRST_STAGE]);

	m_nSelectedStage = FIRST_STAGE;

	CAnimateUI::UIAnimation animInfo;
	animInfo.deltaSize = D3DXVECTOR2(0.75f, 0.5f);
	animInfo.nChangeFrame = 30;
	m_pLogo[0] = CAnimateUI::Create(CObject::TEXTURE_STAGE_LOGO, D3DXVECTOR3(340.0f, 470.0f, 0.0f), D3DXVECTOR2(150.0f, 100.0f), ColorWhite, animInfo);
	m_pLogo[0]->SetTextureParameter(1, 1, 2, INT_MAX);
	m_pLogo[0]->SetAnimPattern(1);

	m_pLogo[1] = CAnimateUI::Create(CObject::TEXTURE_STAGE_LOGO, D3DXVECTOR3(930.0f, 470.0f, 0.0f), D3DXVECTOR2(150.0f, 100.0f), ColorWhite, animInfo);
	m_pLogo[1]->SetTextureParameter(1, 1, 2, INT_MAX);
	m_pLogo[1]->StopAnimation();

	CObject_2D* pObj = CObject_2D::Create(3, D3DXVECTOR3(200.0f, 125.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), CObject::TEXTURE_PRESS_KEY);
	pObj->SetTextureParameter(2, 2, 5, 30);
	pObj->SetAnimationBase(6);
	pObj->SetAnimPattern(6);

	pObj = CObject_2D::Create(3, D3DXVECTOR3(1000.0f, 125.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), CObject::TEXTURE_PRESS_KEY);
	pObj->SetTextureParameter(2, 2, 5, 30);

	pObj = CObject_2D::Create(3, D3DXVECTOR3(1150.0f, 125.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), CObject::TEXTURE_PRESS_KEY);
	pObj->SetTextureParameter(2, 2, 5, 30);
	pObj->SetAnimationBase(2);
	pObj->SetAnimPattern(2);

	return S_OK;
}

//終了処理
void CStageSelect::Uninit(void)
{
	//カーソルの破棄処理
	if (m_pCursor)
	{//nullチェック
		m_pCursor->Release();		//メモリを解放する
		m_pCursor = nullptr;		//ポインタをnullにする
	}

	//ロゴの破棄処理
	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{//nullチェック
		if (m_pLogo[nCnt])
		{//nullチェック
			m_pLogo[nCnt]->Release();		//メモリを解放する
			m_pLogo[nCnt] = nullptr;		//ポインタをnullにする
		}
	}
}

//更新処理
void CStageSelect::Update(void)
{
	if (!CApplication::GetFade())
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT) || CInputKeyboard::GetKeyboardTrigger(DIK_D))
		{
			m_nSelectedStage = SECOND_STAGE;

			if (m_pCursor)
			{
				m_pCursor->SetPos(CURSOR_POS[SECOND_STAGE]);
			}

			if (m_pLogo[FIRST_STAGE])
			{
				m_pLogo[FIRST_STAGE]->StopAnimation();
			}
			if (m_pLogo[SECOND_STAGE])
			{
				m_pLogo[SECOND_STAGE]->StartAnimation();
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHOOSH);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_LEFT) || CInputKeyboard::GetKeyboardTrigger(DIK_A))
		{
			m_nSelectedStage = FIRST_STAGE;

			if (m_pCursor)
			{
				m_pCursor->SetPos(CURSOR_POS[FIRST_STAGE]);
			}

			if (m_pLogo[FIRST_STAGE])
			{
				m_pLogo[FIRST_STAGE]->StartAnimation();
			}
			if (m_pLogo[SECOND_STAGE])
			{
				m_pLogo[SECOND_STAGE]->StopAnimation();
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHOOSH);
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{
			switch (m_nSelectedStage)
			{
			case FIRST_STAGE:

			{
				CApplication::SetFade(CApplication::MODE_FIRST_STAGE);
			}

			break;

			case SECOND_STAGE:

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
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
		{
			CApplication::SetFade(CApplication::MODE_TUTORIAL);
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