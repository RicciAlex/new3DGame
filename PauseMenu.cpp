//=============================================================================
//
// PauseMenu.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "PauseMenu.h"
#include "menuButton.h"
#include "application.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CPauseMenu::DEFAULT_MENU_POS = { (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f };		//ディフォルトのメニューの位置
const D3DXVECTOR2 CPauseMenu::DEFAULT_MENU_SIZE = { 200.0f, 200.0f };				//ディフォルトのメニューのサイズ
const D3DXVECTOR2 CPauseMenu::DEFAULT_BUTTON_SIZE = { 300.0f, 100.0f};			//ディフォルトのボタンのサイズ
const float		  CPauseMenu::DEFAULT_BUTTON_DISTANCE = 100.0f;		//ボタンの間の距離
const char		  CPauseMenu::BUTTON_STRING[CPauseMenu::TYPE_MAX][48] = 
{
	"CONTINUE",
	"QUIT"
};		//ボタンの文字列


//コンストラクタ
CPauseMenu::CPauseMenu()
{
	m_bActive = false;

	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		m_buttonRelativePos[nCnt] = Vec3Null;

		m_pButton[nCnt] = nullptr;
	}
}

//デストラクタ
CPauseMenu::~CPauseMenu()
{

}

//初期化処理
HRESULT CPauseMenu::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CMenu::Init()))
	{
		return -1;
	}

	CreateBg(DEFAULT_MENU_POS, DEFAULT_MENU_SIZE, CObject::TEXTURE_BLOCK);

	return S_OK;
}

//終了処理
void CPauseMenu::Uninit(void)
{
	//ボタンの破棄処理
	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->Release();		//メモリを解放する
			m_pButton[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//基本クラスの終了処理
	CMenu::Uninit();
}

//更新処理
void CPauseMenu::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->Update();

			if (m_pButton[nCnt]->GetTriggerState())
			{
				SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 5000.0f, 0.0f));			//画面外に移動する
				m_bActive = false;
				CApplication::SetPause(false);

				switch (nCnt)
				{
				case CPauseMenu::TYPE_CONTINUE:

				{

				}

				break;

				case CPauseMenu::TYPE_QUIT:

				{
					CApplication::SetFade(CApplication::MODE_TITLE);
				}

				break;

				default:
					break;
				}
			}
		}

		//基本クラスの更新処理
		CMenu::Update();
	}
}

//描画処理
void CPauseMenu::Draw(void)
{
	//基本クラスの描画処理
	CMenu::Draw();
}

//位置の設定処理
void CPauseMenu::SetPos(const D3DXVECTOR3 pos)
{
	//基本クラスの位置の設定処理
	CMenu::SetPos(pos);

	//ボタンの位置の設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->SetPos(pos + m_buttonRelativePos[nCnt]);
		}
	}
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CPauseMenu * CPauseMenu::Create(void)
{
	CPauseMenu* pMenu = new CPauseMenu;			//インスタンスを生成する

	//初期化処理
	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	pMenu->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 5000.0f, 0.0f));		//位置の設定
	pMenu->CreateButton();					//ボタンの生成処理

	return pMenu;					//生成したインスタンスを返す
}

//ボタンの生成処理
void CPauseMenu::CreateButton(void)
{
	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		D3DXVECTOR3 pos = GetPos();
		pos.y += (-DEFAULT_BUTTON_DISTANCE * (TYPE_MAX * 0.5f)) + (DEFAULT_BUTTON_DISTANCE * nCnt * 2.0f);

		m_buttonRelativePos[nCnt] = pos - GetPos();

		m_pButton[nCnt] = CMenuButton::Create(pos, DEFAULT_BUTTON_SIZE, BUTTON_STRING[nCnt]);
	}
}
