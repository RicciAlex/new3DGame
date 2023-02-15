//=============================================================================
//
// menuButton.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "menuButton.h"
#include "UIString.h"
#include "object2D.h"

#include "application.h"
#include "inputMouse.h"
#include "inputKeyboard.h"

//コンストラクタ
CMenuButton::CMenuButton()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_size = Vec2Null;
	m_type = (BUTTON_TYPE)0;
	m_normalCol = ColorNull;
	m_TriggeredCol = ColorNull;
	m_bOverlap = false;
	m_bTriggered = false;

	m_pString = nullptr;
}

//デストラクタ
CMenuButton::~CMenuButton()
{

}

//初期化処理
HRESULT CMenuButton::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;
	m_size = Vec2Null;
	m_type = (BUTTON_TYPE)0;
	m_normalCol = ColorRed;
	m_TriggeredCol = ColorYellow;
	m_bOverlap = false;
	m_bTriggered = false;

	m_pString = nullptr;

	return S_OK;
}

//終了処理
void CMenuButton::Uninit(void)
{
	//UIの配列の破棄処理
	if (m_pString)
	{//nullチェック

		m_pString->Release();		//メモリを解放する
		m_pString = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CMenuButton::Update(void)
{
	m_bTriggered = false;

	m_bOverlap = MouseOnButton();

	if (m_bOverlap && CApplication::GetMouse()->GetMouseLeftClick())
	{
		m_bTriggered = true;
	}
}

//描画処理
void CMenuButton::Draw(void)
{

}

//位置の設定処理
void CMenuButton::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	//文字列の位置の設定
	if (m_pString)
	{
		m_pString->SetPos(pos);
	}
}

void CMenuButton::SetOverlap(const bool bOverlap)
{
	m_bOverlap = bOverlap;
}

//位置の取得処理
const D3DXVECTOR3 CMenuButton::GetPos(void)
{
	return m_pos;
}

//押されているかどうかの取得処理
const bool CMenuButton::GetTriggerState(void)
{
	return m_bTriggered;
}

//マウスと重なっているかどうかの取得処理
const bool CMenuButton::GetOverlap(void)
{
	return m_bOverlap;
}


//=============================================================================
//
//								静的関数
//
//=============================================================================

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;				//位置の設定
	pButton->m_size = size;				//サイズの設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, pButton->m_normalCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;				//位置の設定
	pButton->m_size = size;				//サイズの設定

	pButton->m_normalCol = stringCol;	//普通の色の設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;						//位置の設定
	pButton->m_size = size;						//サイズの設定

	pButton->m_normalCol = stringCol;			//普通の色の設定
	pButton->m_TriggeredCol = triggeredCol;		//マウスカーソルと重なった時のの色の設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;				//位置の設定
	pButton->m_size = size;				//サイズの設定
	pButton->m_type = type;				//種類の設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, pButton->m_normalCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;				//位置の設定
	pButton->m_size = size;				//サイズの設定
	pButton->m_type = type;				//種類の設定

	pButton->m_normalCol = stringCol;	//普通の色の設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}

//生成処理
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->m_pos = pos;						//位置の設定
	pButton->m_size = size;						//サイズの設定
	pButton->m_type = type;						//種類の設定

	pButton->m_normalCol = stringCol;			//普通の色の設定
	pButton->m_TriggeredCol = triggeredCol;		//マウスカーソルと重なった時のの色の設定

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UIの配列を生成する

	return pButton;					//生成したインスタンスを返す
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//マウスカーソルがボタンを重なっているかどうかを判断する関数
bool CMenuButton::MouseOnButton(void)
{
	//マウスカーソルの位置の取得と変換
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);
	D3DXVECTOR3 MousePos;
	MousePos.x = (float)pt.x;
	MousePos.y = (float)pt.y;
	MousePos.z = 0.0f;

	if (MousePos.x >= m_pos.x - m_size.x * 0.5f && MousePos.x <= m_pos.x + m_size.x * 0.5f &&
		MousePos.y >= m_pos.y - m_size.y && MousePos.y <= m_pos.y + m_size.y)
	{
		if (!m_bOverlap)
		{
			if (m_pString)
			{
				m_pString->ChangeColor(m_TriggeredCol);
			}
		}

		return true;
	}
	else
	{
		if (m_bOverlap)
		{
			if (m_pString)
			{
				m_pString->ChangeColor(m_normalCol);
			}
		}
	}

	return false;
}
